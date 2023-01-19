# Static Cast

A static cast is check at compile type.

## Syntax

```c++
expr : Type
```

## Rules

Numerics
- `Numeric` -> `bool`: Evaluates expr != 0
- `Numeric` -> `char`: Created with UTF-8/ASCII code of expr
- `Numeric` -> `int`: Converts expr to int. Floats are truncated.
- `Numeric` -> `float`: Promotes value to float.  

Arrays
- `array<T1>` -> `array<T1>`: Just pass through if T is the same.
- `array` -> `array<T>` : Specify type of empty array.

Other
- `T` -> `any`: Wrap value in any.
- `T` -> `bool`: Evaluated truthyness.

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

# Dynamic Cast

A dynamic cast is checked at runtime. An optional of the requested type is returned. If the cast is successful it produces a value. If the types don't match null is returned instead.

## Rules

All rules from static cast and:

- `T` -> `string`: Checks and returns string reference.
- `T1` -> `array<T2>`: Checks and returns array reference.

## Syntax

```c++
expr ~ Type
```

# Force Cast

A force cast is checked at runtime. It returns the requested type T or throws.

## Rules

All rules from static and dynamic cast apply.

Equivalent to: `*(expr ~ T)`

## Syntax

```c++
expr ! Type
```

# Guideslines and best practices

Prefer a static cast if possible. If not use a dynamic cast.
Use force cast only if you are sure that the types match or if you have robust error handling.