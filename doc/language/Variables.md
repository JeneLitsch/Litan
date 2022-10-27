# Variables


## Syntax

The following code listing shows a the structure of a variable declaration.

```js
var /*name*/ : /*type*/ = /*expression*/;  
```

The type and expression is optional.

## Defaults

A variable without type is of type any by default.
A variable without an initial value, is set to null until assigned otherwise.

## Examples

```js
function main() {
	var foo;
	var bar : int = 42;
	var baz : string = "Hello World";
	std::println(foo);
	std::println(bar);
	std::println(baz);
}
```
