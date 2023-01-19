# for

## Syntax

```js
for (/*loop_variable*/ : /*start_value*/ -> /*end value*/ : /*step size*/) /*single statement*/
```

## Examples

```js
for (i : 0 -> 42) {
	std::println(i);
}
```
```js
for (i : 0 -> 42 : 2) {
	std::println(i);
}
```

## Note

"i" can be named anything. A new variable with the specified name is created in the scope of the loop. The type of the index variable is always int.
