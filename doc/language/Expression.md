# Expression


## Call [`expr.call`]

(1)

```js
`function-id`(`parameters...`)
```

(2)

```js
`expr`(`parameters...`)
```

(3)

```js
`expr`->`member-id`(`parameters...`)
```

Examples:

```js
function main() {
	var x = (lambda (a, b) => a + b)(1, 3);
	std::println(x); // 4
}
```

```js
function main() {
	var hello = lambda(name) => "Hello " + std::string(name); 
	std::println((hello)("World")); // Hello World
}
```


## Expression blocks / IIFE [`expr.block`]

```js
iife { `stmt...stmt` }
```

An IIFE can be used anywhere where an expression is needed.  
If an IIFE does not return `null` is returned by default. 

Examples:

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



## Conditional [`expr.conditional`]

```js
conditional {
    case `condition` => `expr`
    ...
}
```

```js
conditional {
    case `condition` => `expr`
    ...
    else  => `expr`
}
```

The conditional expression checks the conditions in sequence.
The conditional expression evaluates to body of first the truthy case. 

If no condition matches the behavior depends on the existence of the else branch.
If the else brach exists, its body is evaluated.
Otherwise the conditional expression evaluates to `null`.



## Lambdas [`expr.lambda`]

(1)

```js
lambda
	[`captures`, ...] // optional
	(`parameters`, ...) // optional
	`stmt.block`
```

(2)

```js
lambda
	[`captures`, ...] // optional
	(`parameters`, ...) // optional
	=> `expr`
```

A lambda expression evaluates to a callable function pointer.  
Captures and parameters are optional and can be omitted.  

Examples:

```js
function main() {
	var fx = lambda(a, b) => a + b;
	std::println((fx)(20, 22));
}
```

```js
function main() {
	var x = 41;
	var fx = lambda[x] {
		return x + 1;
	};
	std::println((fx)());
}
```