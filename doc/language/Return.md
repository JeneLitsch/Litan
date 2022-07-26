# return

A Litan function can return a value with a return statement.  
`return <expression>;`

```js
function f() {
    return 42;
}
```

A return statement without expression `return;` is equivalent to `return null;`

If a function ends without an explicit return statement null is returned by default.

