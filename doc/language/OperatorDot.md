# Operator .

The dot operator accesses the member of a struct.

## Syntax
```js
/*struct expression*/ . /*member name*/
```

## Examples

### 1)
```js
function main() {
	var pair = std::pair(42, 0);
	pair.second = 1337;
	std::println(pair.first);
	std::println(pair.second);
}
```
Output:
```
42
1337
```