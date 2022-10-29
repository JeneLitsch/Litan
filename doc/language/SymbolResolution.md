# Symbol Resolution

If symbol is resolved in the usage of a variable or function call the following rules apply.

## Order

1. Variable in local scope
2. Variable in parent scopes
3. Function in current namespace
4. Function in parent namespace
5. Function in global namespace
6. Definition in current namespace
7. Definition in parent namespace
8. Definition in global namespace

## With explicit namespace

If an explicit namespace preceeds the symbol name 1 and 2 are skipped.