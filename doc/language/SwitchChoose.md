# Switch / Choose
There are two different switch statements. `switch` is used for statement and `choose` is used for expression. 

## Syntax

```js
switch(/*expression*/) {
	case /*constant*/: /*statement*/
	...
	default: /*statement*/
}
```

```js
choose(/*expression*/) {
	case /*constant*/: /*expression*/ 
	case /*constant*/: /*expression*/;
	// The comma is optional
	...
	default: /*expression*/
}
```

## Examples

```js
function fx(x) {
	switch(x) {
		case 42: std::println("The awnser");
		case 1337: std::println("Leet");
		default: std::println("Default");
	}
}

function main() {
	fx(42);
	fx(1337);
	fx("test");
	fx(null);
}
```

```js
function fx(x) => 
	std::println(choose(x) {
		case 42: "The awnser";
		case 1337: "Leet";
		default: "Default";
	})

function main() {
	fx(42);
	fx(1337);
	fx("test");
	fx(null);
}
```

```js
function fx(x) { 
	var y = choose(x) {
		case 42: "The awnser";
		case 1337: "Leet";
		default: "Default";
	};
	std::println(y);
}

function main() {
	fx(42);
	fx(1337);
	fx("test");
	fx(null);
}
```

The output of the 3 examples is

```
The awnser
Leet
Default
Default

```

## Note
If no case matches the default case is executed. The default case is optional.  
If a switch-statement has no matching case nor a default case then the switch-statement is simply skipped.
If a choose-expression has no matching case nor a default case then it evaluates to null.