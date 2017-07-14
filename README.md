# AFD Language Finitness

This is a simple tool made for a homework at University that checks if the language accepted by an AFD is finite or not.

# Info
- States should be integers
- The initial state will exist and will be 0 
- The final states will have values greater than others
- The alphabet will contain a-z A-Z

# Input
- On the first line, a word with length greater than **0**
- On the second lines, 3 integers: **n** ( number of states ), **ns** ( number of final states ) and **s** ( number of simbols in the alphabet )
- On the next lines, values **st** ( current state ), **c** ( character ) and **end** ( next state ).

# Output
- **1** if finite
- **0** if not finite
