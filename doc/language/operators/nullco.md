# Operator ??

The null coalescing operator ?? returns the left side as long if it's not null.
If the left side is null the right side is returned instead.

## Syntax
```js
/*expression*/ ?? /*alternative*/
```

## Examples
### 1)
```js
function main() {
	std::println(null ?? 42);
	std::println(false ?? 42);
}
```
Output:
```
42
false
```