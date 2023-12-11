# Coroutines 

## Syntax

Coroutines use the normal function syntax. 
To the declare a coroutine the function requires the coroutine qualifier.

```js
function foo() coroutine {
	// Body
}
```

## Yield and Return

Inside a coroutine the `yield`-statement is available.
The `yield`-statement is used to pause the coroutine and return a value from the coroutine to the caller.
The caller receives a tuple with an new coroutine containing the state of the callee as the first and the returned value as the second element.
The new coroutine resumes the excution when called. 

```js
yield 42;
```

The behavior of the `return`-statement is altered inside coroutines.
When the excution encounters a `return`-statement the coroutine finishes the execution.
The caller receives a noroutine and the returned value.

```js
return 42;
```

## Noroutine

A noroutine is a special value indicating a terminated coroutine.
Calling it yields a noroutine and null. 


## Direct Usage

Couroutines can directly be called with the call operator.
The initial call creating the coroutine object can take any number of argument.

```js
function f(x) coroutine {
	yield 1;
	yield 2;
	return x;
}

function main() {
	var cor_0 = f(42);
	var (cor_1, val_1) = cor_0();
	var (cor_2, val_2) = cor_1();
	var (cor_3, val_3) = cor_2();
	var (cor_4, val_4) = cor_3(); // cor_4 is a noroutine
	std::println(val_1);
	std::println(val_2);
	std::println(val_3);
	std::println(val_4);
}
```

The resulting output:

```
1
2
42
null
```

## Iteration 

Coroutines can iterated and wrap into an iterator with std::iter.
The Iterator continues until return is encountered.

```js
function g() coroutine {
	yield 1;
	yield 2;
	yield 3;
	return 4;
}

function main() {
	for(x : g()) {
		std::println(x);
	}
}
```

The resulting output:

```
1
2
3
4
```