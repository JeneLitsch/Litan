# Invokation

## Syntax
```js
(/*callable expression*/)(/*parameters*/)
```

## Examples

### 1)
```js
function main() {
	var x = (lambda (a, b) => a + b)(1, 3);
	std::println(x);
}
```
Output:
```
4
```

### 2)
```js
function main() {
	var hello = lambda(name) => "Hello " + std::string(name); 
	std::println((hello)("World"));
}
```
Output:
```
Hello World
```

### 3)
```js
function make_greeting(name) 
	=> "Hello " + std::string(name)

function main() {
	var hello = &make_greeting(_); 
	std::println((hello)("World"));
}
```
Output:
```
Hello World
```

## Exceptions
- Calling an non callable object throws an exception.  
- Calling an callable object with the wrong number of parameters throws an exception.