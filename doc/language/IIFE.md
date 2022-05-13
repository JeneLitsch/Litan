# Expression blocks / IIFE

### Syntax
```
iife {
	// some code
	return 42;
}
```

### Examples
```
var foo = {
	var a = 1;
	var b = 2;
	var c = 3;
	return a + b + c;
};
// foo is asigned to 6 in this example
```

```
var bar = 21;
var foo = {
	var factor = 2;
	return factor * bar;
};
// foo is asigned to 42 in this example
```

### Usage
An IIFE can be used anywhere where an expression is needed.