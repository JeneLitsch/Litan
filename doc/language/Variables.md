# Variables


## Syntax

The following code listing shows a the structure of a variable declaration.

```js
var /*name*/ : /*type*/ = /*expression*/;  
```

The type and expression is optional.

## Defaults

A new variable with neither a type nor initialition by an expression is declared as any and set to null.

If a new variable is initialized with an expression the type of the expression is used to declare the variable.

If a new variable is explicitly declared with a type but no expression is assigned. The compiler generates a default value. If a type has not default a compiler error is thrown. 

| type   | default value |
| ------ | ------------- |
| any    | null          |
| bool   | false         |
| int    | 0             |
| float  | 0.0           |
| string | ""            |
| array  | []            |

An explicitly annotated type is always prioritized over deduction.

## Examples

```js
function main() {
	var foo; // any null
	var bar : int = 42; // int 42
	var baz : string = "Hello World"; // string "Hello World"
	var qux = 42; // int 42
	std::println(foo);
	std::println(bar);
	std::println(baz);
}
```
