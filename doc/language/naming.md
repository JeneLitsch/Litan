# Naming Rules and Conventions

## Allowed Characters

Identifiers may contain

1. lower case latin letters `[a-z]`
2. upper case latin letters `[A-Z]`
3. underscores `_`
4. numbers `[0-9]`

Additionally an indentifier must NOT start with a number. 

## Reserved Keywords

Reserved keywords cannot be used outside their specified use case. 

- `function`
- `lambda`
- `while`
- `for`
- `return`
- `var`
- `if`
- `else`
- `return`
- `true`
- `false`
- `namespace`
- `except`
- `throw`
- `null`
- `iife`
- `build_in`
- `dynamic`
- `enum`
- `def`
- `switch`
- `case`
- `reflect`
- `yield`
- `conditional`
- `_`

## Reserved indentifiers

Reserved keywords can be used outside their specified use case but doing so is strongly advised against.

- `__add__`
- `__sub__`
- `__mlt__`
- `__div__`
- `__mod__`
- `__pow__`
- `__cmp__`
- `__str__`
- `__bool__`
- any other identifier starting with double underscore `__` is reserved for implementation purpose.

Using any of these might result in name collsions and unexpected behavior.


## Variables

Variables are conventionally named in `snake_case`.

```js
var foo;
var bar;
var baz;
```

## Functions

Functions are conventionally named in `snake_case`.

```js
function foo() {
	// Code goes here
}
```

## Namespaces

Namespaces are conventionally named in `snake_case`.

```c++
namespace foo {

}
```

## Types

Types are conventionally named in `PascalCase`.

```
std::Array
```

## Enum Members

Types are conventionally named in `UPPER_CASE`.
