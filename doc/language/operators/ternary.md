# Operator c?a:b

Evaluates to `a` if `c` is truthy or to `b` if `c` is false.


## Syntax
```js
/*condition*/ ? /*a*/ : /*b*/
```

## Examples
### 1)
```js
function main() {
	std::println(true ? 1 : 2);
	std::println(false ? 1 : 2);
}
```
Output:
```
1
2
```