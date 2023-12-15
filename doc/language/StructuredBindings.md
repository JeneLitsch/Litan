# Structured Bindings

Structured bindings allow easy unpacking of tuple elements.
The expression used to assign to the binding must be a tuple.

## New Variable

Single Level:

```js
var (a, b) = expression; 
```


Multi Level:

```js
var (a, (b, c)) = expression; 
```

## For Loop

```js
for((a,b) : expression) {}
```

## Ignore extra elements

If the expression provides extra elements not used in the binding, they will be ignored.
Example: Destructuring a 3-Tuple into a 2-Bind will fetch the first two elements and discard the third.

## Missing elements

If the expressions provides less elements than the binding requires, an exception is thrown.