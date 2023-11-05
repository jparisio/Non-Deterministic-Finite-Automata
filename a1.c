#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Transitions {

    char from[10];
    char input[10];
    char to[10];

} transitions;

typedef struct States{

    char name[10];
    int on_or_off;

} state_arrays;

void print_states(state_arrays *next_active_states, int num_states){

    for( int i = 0; i < num_states; i ++){
        printf("%d  ", next_active_states[i].on_or_off);
    }

    printf("\n");
}

void epsilon(state_arrays *next_active_states, state_arrays check_this_state, transitions *transition_table, int num_states, int num_transitions){
    //set the next on and recurse
    for(int i = 0; i < num_transitions; i++){
        if(strcmp(check_this_state.name, transition_table[i].from) == 0){
            if(strcmp(transition_table[i].input, "e") == 0){
                for(int j = 0; j < num_states; j++){
                    if(strcmp(next_active_states[j].name, transition_table[i].to) == 0){
                        next_active_states[j].on_or_off = 1;
                        epsilon(next_active_states, next_active_states[j], transition_table, num_states, num_transitions);
                    }
                }
            }
        }
    }
}

void determine_next_states(state_arrays *next_active_states, char curr_state[10], int num_states, transitions *transition_table, int num_transitions, char input[10]){
    //for each state
    for(int i = 0; i < num_transitions; i++){
        //if we found the current states transition on the table
        if(strcmp(curr_state, transition_table[i].from) == 0){
            //if the right input is met then take the trasnition
            if(strcmp(input , transition_table[i].input) == 0){
                //wherever in curr active states the state is turn it on
                for(int j = 0; j < num_states; j ++){
                    if(strcmp(transition_table[i].to, next_active_states[j].name) == 0){
                        next_active_states[j].on_or_off = 1;
                        //recursively check for epsilon
                        epsilon(next_active_states, next_active_states[j], transition_table, num_states, num_transitions);
                    }
                }
            }
        }
    }
}

int main(int argc, char* argv[]){

   if(argc == 1){
        perror("no file names entered\n");
        return(0);
    }

    //ARRAYS AND VARS

    //alphabet
    char alph_size[3] = {0};
    char alph[100][10];

    //states
    char num_states[4] = {0};
    char states[1000][10];

    //start and accept
    char start_state[10] = {0};
    char accept_state[10] = {0};

    //inputs
    char num_inputs[4] = {0};
    char input_elems[1000][10];

    //transitions
    char num_transitions[4] = {0};

    //file work
    FILE *ptr = fopen(argv[argc - 1], "r");
    if (ptr == NULL) {
        printf("file dne");
        return 0;
    }

    char word[10];
    char strings[1000][10];
    int temp = 0;
    while(fscanf(ptr, "%s", word) != EOF){
        strcpy(strings[temp], word);
        temp++;
    }
    fclose(ptr);

    //ALPHABET
    strcpy(alph_size, strings[0]);
    //start after the first number
    temp = 1;
    for(temp; temp <= atoi(alph_size); temp++){
        strcpy(alph[temp - 1], strings[temp]);
    }


    //STATES
    strcpy(num_states, strings[temp]);
    temp++;

    int num = temp + atoi(num_states);
    int j = 0;
    for(temp; temp < num; temp++){
        strcpy(states[j], strings[temp]);
        j++;
    }

    //START AND ACCEPT
    strcpy(start_state, strings[temp]);
    temp++;

    strcpy(accept_state, strings[temp]);
    temp++;

    //INPUTS
    
    strcpy(num_inputs, strings[temp]);
    temp++;

    j = 0;
    num = temp + atoi(num_inputs);
    for(temp; temp < num; temp++){
        strcpy(input_elems[j], strings[temp]);
        j++;
    }

    //TRANSITIONS
    strcpy(num_transitions, strings[temp]);
    temp++;

    //create a transiiton table array for the number of transitions
    transitions *transition_table = malloc(sizeof(transitions) * atoi(num_transitions));
    num = temp + atoi(num_transitions) * 3;
    j = 0;
    for(temp; temp < num; temp++){
        strcpy(transition_table[j].from , strings[temp]);
        temp++;
        strcpy(transition_table[j].input , strings[temp]);
        temp++;
        strcpy(transition_table[j].to , strings[temp]);
        j++;
    }

    //create an array for current active and next active 
    state_arrays *current_active_states = malloc(sizeof(state_arrays) *(atoi(num_states)));
    state_arrays *next_active_states = malloc(sizeof(state_arrays) *atoi(num_states));

    //initalize to 0

    for(int i = 0; i < atoi(num_states); i++){
        current_active_states[i].on_or_off = 0;
        strcpy(current_active_states[i].name, states[i]);
        next_active_states[i].on_or_off = 0;
        strcpy(next_active_states[i].name, states[i]);
    }

    //NFA loop

    for(int i = 0; i < atoi(num_inputs); i++){

        //print current input part
        printf("%s  ", input_elems[i]);

        //strart at start state if were on the first iteration
        if(i == 0){
            //set the start state to on 
            int start_index = 0;
            for(int j = 0; j < atoi(num_states); j++){
                if(strcmp(current_active_states[j].name, start_state) == 0){
                    current_active_states[j].on_or_off = 1;
                    start_index = j;
                }
            }
            //check epsilon on the start state
            epsilon(current_active_states, current_active_states[start_index], transition_table, atoi(num_states), atoi(num_transitions));
            //print_states(current_active_states, atoi(num_states));
        } 
        //compare the input to the current state were on
        for(int k = 0; k < atoi(num_states); k ++){
            if(current_active_states[k].on_or_off == 1){
                determine_next_states(next_active_states, current_active_states[k].name, atoi(num_states), transition_table, atoi(num_transitions), input_elems[i]);
            }
        }
        

        print_states(next_active_states, atoi(num_states));


        //set current active states to next active states
        for(int j = 0; j < atoi(num_states);  j++){
            current_active_states[j].on_or_off = next_active_states[j].on_or_off;
        }
        //reset next active states
        for(int i = 0; i < atoi(num_states); i++){
            next_active_states[i].on_or_off = 0;
        }

    }


    //check for accpet or reject
    for(int i = 0; i < atoi(num_states); i++){
        if(strcmp(accept_state, current_active_states[i].name) == 0){
            if(current_active_states[i].on_or_off == 0){
                printf("reject\n");
            } else {
                printf("accept\n");
            }
        }
    }


    free(transition_table);
    free(current_active_states);
    free(next_active_states);

    return 0;
}