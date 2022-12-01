# General Rules

## Bool

A cast for a bool evaluates its truthyness.
Null always returns false.
Any numeric type returns false for 0 and true for any other value
All other types are always evaluated to true. 

## Char 

Any numeric type casted to char is truncated or promoted and converted to the char with the same ASCII/UTF-8 code.

## Int

Any numeric type is truncated or promoted to int.

## Float

Any numeric type can be explicity promoted to float.

# Static cast

A static cast is check at compile type.

## Syntax

```c++
/*expr*/ : /*type*/
```

## Examples

```c++
1 : float // -> 1.0
```

```c++
null : bool // -> false
```

```c++
[] : bool // -> true
```

```c++
65 : char // -> 'A'
```