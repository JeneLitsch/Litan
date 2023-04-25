# for

## Syntax

```js
for (/*element*/ : /*iterable*/) /*Body*/
```

## Examples

```js
for (i : std::range(0, 42)) {
	std::println(i);
}
```
```js
for (i : std::range(0, 42, 2)) {
	std::println(i);
}
```

```js
for (c : "ABC") {
	std::println(c);
}
```

```js
var array = [1,2,3,4,5];
for (elem : array) {
	std::println(elem);
}
```
