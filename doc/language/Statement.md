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



## Assignment [`stmt.assign`]

```js
`bind` = `expr`;
```

The Assigment-Statement assigns the value of the expression on the right to an assignable binding on the left. 



## New Variable [`stmt.new_var`]

(1)

```js
var `name`;
```

(2)

```js
var `name` = `expr`;
```

(3)

```js
var (`name`...) = `expr`;
var (`name`...(`name`...`name`)) = `expr`;
```

The New-Variable-Statement creates one or more new variables.  

(1) In its most basic form it creates a single variable and initializes it with null.  

(2) A custom initial value can be provided by assigning an expression.  

(3) The New-Variable-Statement allows easy unpacking of tuple elements by using structured bindings.  
The expression used to assign to the binding must be a tuple.  
If the expression provides extra elements not used in the binding, they will be ignored.  
Example: Destructuring a 3-Tuple into a 2-Bind will fetch the first two elements and discard the third.  
If the expressions provides less elements than the binding requires, an exception is thrown.  

Examples:

```js
var foo;
```

```js
var bar = "Hello, World!"; 
```

```js
var (a, b) = (1, 2); 
var (c, d) = (42, 1337, 666); 
```

```js
var (a, (b, c)) = (1, (2,3)); 
```



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

Example:
```js
while(true) {
	std::println("Hello, World!");
}
```



## For [`stmt.for`]

```js
for (`bind` : `expr`) `stmt`
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

```js
var array = [(11,"11"),(22,"22"),(33,"33")];
for ((num, str) : array) {
	std::println(std::str(num) + " : " + str);
}
```


## Return [`stmt.return`]

(1)

```js
return;
```
(2)

```js
return `expr`;
```

A function can return a value with a return statement.  
The expression after the return keyword is evaluated and the value is returned (2).  
A return statement without expression `return;` (1) is equivalent to `return null;`  
If a function ends without an explicit return statement null is returned by default.

Example:

```js
function f() {
    return 42;
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



## Switch [`stmt.switch`]

```js
switch(`expr`) {
	case `constant` => `stmt`
	...
	else:           => `stmt`
}
```