# Structured Bindings

Structured Bindings allows easy unpacking of tuple elements.
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