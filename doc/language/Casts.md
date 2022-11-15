# General Rules

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

Any numeric array can be casted to a string. The numeric subtype values are interpreted as ASCII codes.

## array

Differnt array types can be casted to each other, if the contained subtype is castable. For static casts to arrays a string is treated the same as an array&lt;char&gt;

# static_cast&lt;T&gt;

Static casts are checked at compile time. If the cast is invalid a compiler error is thrown. The cast returns a value of type T. static_cast returns a deep of the object.

# dynamic_cast&lt;T&gt;

Dynamic casts are checked at run time. If the cast is invalid null is returned.
The cast returns an value of type optional&lt;T&gt;. dynamic_cast returns a copy of the object.