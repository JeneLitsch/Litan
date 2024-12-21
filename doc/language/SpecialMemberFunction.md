# Special Member Function

Special member functions can be used to overload operators or make custom objects compatible with certain build-in functions. 
For binary operators the function of the left operand is used. The right operand's member is always ignored.

| Member   | Arity    | Use case                                                                                                                                |
| -------- | -------- | --------------------------------------------------------------------------------------------------------------------------------------- |
| `__add__`  | self + 1 | Addition operator                                                                                                                       |
| `__sub__`  | self + 1 | Subtraction operator                                                                                                                    |
| `__mlt__`  | self + 1 | Multiplication operator                                                                                                                 |
| `__div__`  | self + 1 | Division operator                                                                                                                       |
| `__mod__`  | self + 1 | Modulo operator                                                                                                                         |
| `__pow__`  | self + 1 | Power operator                                                                                                                          |
| `__str__`  | self     | Makes object stringifiable. Must return a string                                                                                        |
| `__cmp__`  | self + 1 | All comparison operators and comparators. Must return an int. Implements threeway comparison. All other comparisons are derived         |
| `__bool__` | self     | Allows object to be evaluated for truthiness. E.g. the object can be used as a condition in `if` and `while` and can be casted to bool. |

