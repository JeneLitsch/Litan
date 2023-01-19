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

# Static Copy

Static copies are checked at compile time. If the copy is invalid a compiler error is emitted. The copy returns a value of type T. A deep copy is performed.

## Syntax

```
expr :* Type
```

## Rules

Numerics
- `Numeric` -> `bool`: Evaluates expr != 0
- `Numeric` -> `char`: Created with UTF-8/ASCII code of expr
- `Numeric` -> `int`: Converts expr to int. Floats are truncated.
- `Numeric` -> `float`: Promotes value to float.  

Arrays
- `array<T1>` -> `array<T2>`: Valid if T1 and T2 are also statically copyable.
- `array` -> `array<T>` : Copies empty array as `array<T>`.

Strings
- `string` -> `string`: Copies string.

Array &lt;-&gt; Strings
- `string` -> `array<Numeric>`: Copies a string into an array of Unicode chars.
- `array<Numeric>` -> `string`: Copies an array of Unicode chars into a string.
- `array` -> `string`: Copies empty array into empty string.

Other
- `T` -> `bool`: Evaluated truthyness.

# Dynamic Copy

Dynamic copies are checked at run time. If the copy is invalid null is returned.
The copy returns a value of type `optional<T>`. A deep copy is performed.

## Syntax

```
expr ~* Type
```

## Rules

All rules from static copy.


# Force Copy

A force copy is checked at runtime. It returns the requested type T or throws.

## Syntax

```
expr !* Type
```

## Rules

All rules from static copy.

Equivalent to: `*(expr ~* Type)`