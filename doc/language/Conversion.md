# Conversions

## To Any

All types can be used as a value of type any. 

## From Any

Values can be automatically converted back from any. The conversion is checked at runtime and throws an exception if invalid.

The following types are supported:
- bool
- char
- int
- float
- string
- array
- optional
- istream
- ostream

## Integral

Any integral type can be implicitly converted to an int.

- bool -> int
- char -> int
- int -> int

## Numeric

Any numeric type can be implicitly converted to an float.

- bool -> float
- char -> float
- int -> float
- float -> float

## Array

An empty type is convertible to any other array type. 