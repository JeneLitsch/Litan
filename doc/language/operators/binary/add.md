# Operator + and +=

The + operator performs an addition or concatination depending on the operands.

| L        | R        | Result | Operation     |
| -------- | -------- | ------ | ------------- |
| Integral | Integral | Int    | Addition      |
| Float    | Integral | Float  | Addition      |
| Integral | Float    | Float  | Addition      |
| Float    | Float    | Float  | Addition      |
| String   | String   | String | Concatination |
| Array    | Array    | Array  | Concatination |

## Examples
### 1)
```js
function main() {
	std::println(20 + 22);
}
```
Output:
```
42
```

### 2)
```js
function main() {
	std::println("Hello" + " " + "World");
}
```
Output:
```
Hello World
```

### 3)
```js
function main() {
	std::println([1,2,3] + [4,5,6]);
}
```
Output:
```
[1, 2, 3, 4, 5, 6]
```