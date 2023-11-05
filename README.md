# Enigma
![Enigma](https://github.com/theATM/Enigma/assets/48883111/c52555ba-b6ed-4bc8-b1b6-18725ae301de)

C++ implementation of the multi rotor Enigma machine.

This code implemements a generalized version of an Enigma cypher machine with multiple rotors and triggers.

The algorithm uses numbers (instead of letters) both in the input and the cypher (up to N digit alfabet).
The number of rotors, triggers (and trigger placement), reflectors and letters, have to be passed to the program first.

## Example Imput

4         // Numer of Letters in alfabet (0, 1, 2, 3)
4         // Numer of Rotors (4)
1 2 4 3   // Inside combination ( 1 is connected to 1, 2 to 2, 3 to 4 and 4 to 3) in 1st rotor
1 2       // Numer of triggers and position of triggers (1 trigger in the 2 position) in 1st rotor
3 2 1 4   // Inside combination of 2nd rotor
0         // No triggers in 2nd rotor
4 3 1 2   // etc ..
0
3 2 1 4
0         
3         // Number of Reflectors (3)
2 1 4 3   // 1st reflector configuration
4 3 2 1   // 2nd reflector configuration
1 2 4 3   // 3rd reflector configuration

6         // Number of tasks
1 0 4 2   // Rotor combination used for cypher
1 1 1 1 2 2 2 2 3 3 3 3 4 4 4 4 0   // code to cypher
1 0 4 0                             // rotor combination for the second task ...
1 1 1 1 2 2 2 2 3 3 3 3 4 4 4 4 0   // etc...
1 0 4 1
1 1 1 1 2 2 2 2 3 3 3 3 4 4 4 4 0 
1 2 4 0
1 1 1 1 2 2 2 2 3 3 3 3 4 4 4 4 0
1 3 4 0
1 1 1 1 2 2 2 2 3 3 3 3 4 4 4 4 0
2 0 4 0 1 0
1 1 1 1 2 2 2 2 3 3 3 3 4 4 4 4 1 1 1 1 2 2 2 2 3 3 3 3 4 4 4 4 0

## Example Output

1 1 1 3 2 4 2 2 4 3 4 1 3 2 3 4  // Enigma ciphertext (first batch)
2 3 2 3 1 4 1 4 4 1 4 1 3 2 3 2  // Enigma ciphertext (second batch)
3 4 3 4 4 3 4 3 1 2 1 2 2 1 2 1  // etc..
2 3 2 3 1 4 1 4 4 1 4 1 3 2 3 2 
4 4 4 4 3 3 3 3 2 2 2 2 1 1 1 1 
2 2 4 2 3 4 1 4 4 4 2 4 1 2 3 2 2 2 4 2 3 4 1 4 4 4 2 4 1 2 3 2 






