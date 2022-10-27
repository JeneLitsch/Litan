# Static Initialization
Functions, definitions and global variables are called staticly initialized.

# Order of initialization
Static language constructs are defined in the following order: defines, globals, functions.
This means definitions cannot access globals or functions. Globals can only access definitions. And functions can use all three.

| Construct   | Can use                         | 
| -           | -                               |
| Definitions |                                 |
| Globals     | Definitions                     |
| Functions   | Definitions, Globals, Functions |

All static constructs are in a valid state by time the main or any extern function is called for the first time.