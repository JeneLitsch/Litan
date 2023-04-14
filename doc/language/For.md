# for

## Syntax

Index for loop

```js
for (/*loop_variable*/ : {/*start_value*/, /*end value*/} : /*step size*/) /*single statement*/
```

Ranged for loop:

```js
for (/*element*/ : /*array*/) /*single statement*/
```

## Examples

```js
for (i : {0, 42}) {
	std::println(i);
}
```
```js
for (i : {0, 42} : 2) {
	std::println(i);
}
```

```js
var array = [1,2,3,4,5];
for (elem : array) {
	std::println(elem);
}
```

## Note

"i" can be named anything. A new variable with the specified name is created in the scope of the loop. The type of the index variable is always int.
