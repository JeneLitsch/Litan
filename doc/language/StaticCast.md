# static_cast<...>

## bool

Any type can be casted to bool to evaluate it's truthyness. It's the same as the bool conversion.
- A numeric type yields false if == 0 and true if != 0.
- A null type always evaluates to false.
- Any other type evaluates to true.

## char 

Any numeric can be casted to a char. The char created has the ASCII code of the (possible truncated) numeric input value.

## int

Any numeric type can be casted to int.
- A bool value evaluates to 0 and 1 for false and true respectively.
- A char is casted to it's ASCII code.
- A float is truncated.

## float 

Any numeric type can be casted to float. The casting rules for bool and char are the same as for integers.

## string

Any type can be casted to a string representation.

## array

Differnt array types can be casted to each other, if the contained subtype is castable. For static casts to arrays a string is treated the same as an array&lt;char&gt;