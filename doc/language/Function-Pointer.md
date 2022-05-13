To create a function pointer to a function the name of function needs to be prefixed with "&" and every parameter needs to be replaced with the placeholder "_". The count of "_" determines the overload choosen for the functions pointer. A function pointer can be called with std::invoke.

### Explantion
`&foo(_,_,_)` creates a function pointer to the foo overload which takes 3 parameter.
`&foo(_,_)` creates a function pointer to the foo overload which takes 3 parameter.

### Example

```javascript
function foo(a, b, c) {
	std::println("I have 3 parameters: " + a + ", " + b + ", " + c);
}

function foo(a, b) {
	std::println("I have 2 parameters: " + a + ", " + b);
}

function main() {
	std::invoke(&foo(_,_,_), [1, 2, 3]);
	std::invoke(&foo(_,_), [42, 1337]);
}
```

Output:
```
I have 3 parameters: 1, 2, 3
I have 2 parameters: 42, 1337
```
