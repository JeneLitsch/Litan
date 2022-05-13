# if-else
The if-else statement works similar to most other programming languages.

```javascript
if(condition) {
    // some code
}
```
or

```javascript
if(condition) {
    // some code
}
else {
    // some other code
}
```

or

```javascript
if(condition) {
    // some code
}
else if(condition) {
    // some code
}
else {
    // even more code
}

```

The condition must be convertible to true or false e.g. a boolean.

---

# while

```javascript
while(condition) {
    // some code
}
```

---

# for
until 2.0
```javascript
for i (0, 42) {
    // some code
}
```
"i" can be named anything. A new variable with the specified name is created in the scope of the loop.

---

# for
since 1.0
```javascript
for (i : 0 -> 42) {
    // some code
}
```
```javascript
for (i : 0 -> 42 : 2) {
    // some code
}
```
"i" can be named anything. A new variable with the specified name is created in the scope of the loop.

---

# return

A Litan function can return a value with return statement.  
`return <expression>;`

```javascript
function f() {
    return 42;
}
```

If a function ends without an explicit return statement null is returned by default.

