# Lambdas

Besides normal functions lambdas can be declared.

## Syntax

A lambda functions is created by using the following syntax: 

```js
lambda [/*captures*/] (/*captures*/) { /*code*/ }
```

or

```js
lambda [/*captures*/] (/*captures*/) => /* expression */
```

Captures and parameters are optional.


## Examples

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