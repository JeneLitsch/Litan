# Function pointers

## Syntax 

```js
&/*function name*/(/*placeholders*/)
```

Underscores `_` are used as placeholders to distinguish overloaded functions. 

### Example

```javascript
function foo(a, b, c) {
	std::println("I have 3 parameters: " 
		+ std::string(a) + ", "
		+ std::string(b) + ", " 
		+ std::string(c));
}

function foo(a, b) {
	std::println("I have 2 parameters: " 
		+ std::string(a) + ", " 
		+ std::string(b));
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
