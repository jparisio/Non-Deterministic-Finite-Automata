all code written by Justin Parisio

to compile:
1. make
2. ./a1 'filename'

Example file inputs:

Example 1: A sample file for a simple NFA:
2   0 1               -two strings in alphabet, the strings are 0 and 1
2   q1 q2            -two states, the states are q1 and q2
q1                      -the starting state is q1
q2                      -the accept state is q2
3 0 1 0               -there are three input elements, the strings 0, 1, and 0
4                        -number of transitions (arrows) in the NFA is 4
q1 0 q1              -transition 1, if state q1 is active and input 0, new state is q1
q1 1 q2              -transition 2, if state q1 is active and input 1, new state is q2
q2 0 q1              -transition 3, if state q2 is active and input 0, new state is q1
q2 1 q2              -transition 4, if state q2 is active and input 1, new state is q2


Example 2: A second sample input file:

2    0 1                 -two strings in the alphabet, the strings are 0 and 1
3    q1 q2 q3        -three states, the states are q1, q2, and q3
q1                        -starting state is q1
q3                         -accept state is q3
2 0 1                     -there are two input elements, strings 0 and 1
3                           -number of transitions (arrows) is 3
q1 1 q2                 -transition 1, if state q1 is active and input 1, new state is q2
q2 e q3                 -transition 2, an epsilon transition leading from q2 to q3
q1 0 q1                 -transition 3, if state q1 is active and input 0, new state is q1
