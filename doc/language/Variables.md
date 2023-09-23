# Variables

Variables can be declared inside functions and in global space.

## Syntax

The following code listing shows a the structure of a variable declaration.

```js
var /*name*/ /*qualifiers... (optional, only for global)*/ = /*expression(optional)*/;  
```

The type and expression is optional.

## Examples

```js
function main() {
	var foo; 
	var bar = 42; 
	var baz = "Hello World"; 
	std::println(foo);
	std::println(bar);
	std::println(baz);
}
```

## Global variable qualifiers

Global variables can have qualifiers.

### private
* A private global variable cannot be used from an ouitside namespace  

### extern
* An extern global variable can be accessed from the outside of the vm.
