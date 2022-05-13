# Expression blocks / IIFE

## Syntax
```
iife {
	// some code here
}
```

## Examples
```js
function main() {
	var foo = iife {
		var a = 1;
		var b = 2;
		var c = 3;
		return a + b + c;
	};
	std::println(foo);
}
```
The output is
```
6
```


```js
function main() {
	var bar = 21;
	var foo = iife {
		var factor = 2;
		return factor * bar;
	};
	std::println(foo);
}
```
The output is
```
42
```


## Note
An IIFE can be used anywhere where an expression is needed.  
If an IIFE does not return `null` is returned by default. 