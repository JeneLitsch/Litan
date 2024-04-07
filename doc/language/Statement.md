# Statement



## Block [`stmt.block`]

```js
{
	`stmt`
	...
	`stmt`
}
```

A block statement is set of statements grouped together with curly braces.  
It provides its own scope. Any variable declared inside is only is only visible within the block itself.



## If/Else [`stmt.if_else`]

(1)

```js
if(`condition`) `stmt`
```

(2)

```js
if(`condition`) `stmt`
else `stmt`
```

If the condition evaluates to a truthy value the following statement is executed.  
Otherwise the statement is skipped (1) or the else block is executed (2).




## While [`stmt.while`]

```js
while(`condition`) `stmt`
```

The while-loop consists of a condition and a statement as a body.
As long as the condition is true the statement is repeated.
The body of the loop uses its own scope.



## For [`stmt.for`]

```js
for (`bind` : `expression`) `stmt`
```

Examples:

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



## Conditional [`stmt.conditional`]

```js
conditional {
    case `condition` => `stmt`;
    ...
}
```

```js
conditional {
    case `condition` => `stmt`;
    ...
    else             => `stmt`;
}
```

The conditional statement checks the conditions in sequence.  
The body belonging to the first matching condition is executed.  

If no condition matches the behavior depends on the existence of the else branch.  
If the else brach exists, its body is executed.  
Otherwise no code is executed.  