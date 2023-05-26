# Special Member Function

Special member functions can be used to overload operators or make custom objects compatible with certain build-in functions. 
For binary operators the function of the left operand is used. The right operand's member is always ignored.

| Member   | Arity    | Use case                                                                                                                                |
| -------- | -------- | --------------------------------------------------------------------------------------------------------------------------------------- |
| `{add}`  | self + 1 | Addition operator                                                                                                                       |
| `{sub}`  | self + 1 | Subtraction operator                                                                                                                    |
| `{mlt}`  | self + 1 | Multiplication operator                                                                                                                 |
| `{div}`  | self + 1 | Division operator                                                                                                                       |
| `{mod}`  | self + 1 | Modulo operator                                                                                                                         |
| `{pow}`  | self + 1 | Power operator                                                                                                                          |
| `{str}`  | self     | Makes object stringifiable. Must return a string                                                                                        |
| `{cmp}`  | self + 1 | All comparison operators and comparators. Must return an int. Implements threeway comparison. All other comparisons are derived         |
| `{bool}` | self     | Allows object to be evaluated for truthiness. E.g. the object can be used as a condition in `if` and `while` and can be casted to bool. |

