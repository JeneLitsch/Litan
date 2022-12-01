# General Rules

## bool

Any type can be copied to bool to evaluate it's truthyness. It's the same as the bool conversion.
- A numeric type yields false if == 0 and true if != 0.
- A null type always evaluates to false.
- Any other type evaluates to true.

## char 

Any numeric can be copied to a char. The char created has the ASCII code of the (possible truncated) numeric input value.

## int

Any numeric type can be copied to int.
- A bool value evaluates to 0 and 1 for false and true respectively.
- A char is copied to it's ASCII code.
- A float is truncated.

## float 

Any numeric type can be copied to float. The copying rules for bool and char are the same as for integers.

## string

Any numeric array can be copied to a string. The numeric subtype values are interpreted as ASCII codes.

## array

Differnt array types can be copied to each other, if the contained subtype is copyable. For static copies to arrays a string is treated the same as an array&lt;char&gt;

# static_copy&lt;T&gt;

Static copies are checked at compile time. If the copy is invalid a compiler error is thrown. The copy returns a value of type T. static_copy returns a deep of the object.

# dynamic_copy&lt;T&gt;

Dynamic copies are checked at run time. If the copy is invalid null is returned.
The copy returns an value of type optional&lt;T&gt;. dynamic_copy returns a deep copy of the object.