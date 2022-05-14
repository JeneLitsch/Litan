# Operator a?:b

Evaluates to a if a is truthy or to b if not.

## Syntax
```js
/*a*/ ?: /*b*/
```

## Examples
### 1)
```js
function main() {
	std::println(true ?: 42);
	std::println(false ?: 42);
}
```
Output:
```
true
42
```