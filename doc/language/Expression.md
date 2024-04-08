# Expression


## Call [`expr.call`]

(1)

```js
`function-id`(`argument-list`)
```

(2)

```js
`expr`(`argument-list`)
```

(3)

```js
`expr`->`member-id`(`argument-list`)
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
iife `stmt.block`
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
	[`capture-list`] // optional
	(`parameter-list`) // optional
	`stmt.block`
```

(2)

```js
lambda
	[`capture-list`] // optional
	(`parameter-list`) // optional
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



## Reflection [`expr.reflect`]

```js
reflect(`query`)
```

Reflections can be used to inspect properties of program itself.


### Line [`expr.reflect.line`]

```js
reflect(line)
```

Returns the current line as an int.  
If the expression is split over mutiple lines, the line containing the `reflect` keyword is used for the line number.

```
__line__ : int
```

### File Reflection [`expr.reflect.file`]

```js
reflect(file)
```

Returns info about the current file.

```
__file__
  .name : string
```

### Location Reflection [`expr.reflect.location`]

```js
reflect(location)
```

Returns combined info about the file and the current line.  
If the expression is split over mutiple lines, the line containing the `reflect` keyword is used for the line number.

```
__location__
  .line : int
  .file
    .name : string
```

### Namespace Reflection [`expr.reflect.namespace`]

```js
reflect(namespace `namespace-id`)
```

A namespace query returns the name of the namespace and inspects members of the said namespace.
A struct with all the collected data is returned.

```
__namespace__
  .name      : string
  .functions : array(__function___)
```

### Function Reflection [`expr.reflect.fucntion`]

```js
reflect(function `function-id`(`placeholder-list`))
```

A function query returns information reagrding a function. For functions with parameters placeholders _ are used.

```
__function__
  .name      : string
  .full_name : string
  .fx_ptr    : function
  .const     : bool
  .private   : bool
  .extern    : bool
```
