# Types

## Null
The null type indicates a non-existing value.
A value of type null can be created by the `null` keyword.

**Example**
```js
function main() {
	var a = null;
}
```
---



## Bool
The bool type can be set two states `true` and `false`. 
A value of type bool can be created by the `true` or `false` keyword.
A boolean value can be implicitly converted or casted to every numeric type where false becomes 0 and true 1.

**Example**
```js
function main() {
	var a = true;
	var b = false;
}
```

---



## Char
The char type is an 8-Bit integral type used to represent a single character.
A value of type char can be created by a char literal e.g. `'a'`, `'\n'` or `';'` 

**Example**
```js
function main() {
	var a = 'a';
	var b = 'b';
	var newline = '\n';
	std::print(a);
	std::print(newline);
	std::print(b);
	std::print(newline);
}
```

---



## Int
The int type is used to store a 64-Bit singed integer value.
A value of type int can be created by a int literal e.g. `0`, `-1` or `42` 

**Example**
```js
function main() {
	var a = 42;
	var b = 1337;
	std::println(a);
	std::println(b);
}
```

**Binary literals**

Any integer literal prefixed with 0b is interpreted as binary notation e.g. `0b10`

**Example**
```js
function main() {
	var a = 0b101010;
	var b = 0b10100111001;
	std::println(a);
	std::println(b);
}
```

**Hexadecimal literals**

Any integer literal prefixed with 0x is interpreted as hex notation e.g. `0x2a`

**Example**
```js
function main() {
	var a = 0x2a;
	var b = 0x539;
	std::println(a);
	std::println(b);
}
```
---



## Float
The float type is used to store a 64-Bit IEEE-754 floating point number.
A value of type float can be created by a float literal e.g. `0.0`, `-1.0` or `42.0` 

**Example**
```js
function main() {
	var a = 42.0;
	var b = 1337.0;
	std::println(a);
	std::println(b);
}
```

---



## String
The string type is used to store an array of char values.
A new string can be created by using a string literal e.g. `"Hello World"` or `"Test"`.

**Example**
```js
function main() {
	var a = "Hello";
	var b = "World";

	// print HelloWorld
	std::print(a);
	std::println(b);
}
```

### Escape sequences
`\n` for newline  
`\t` for tab  
`\\` for \  
`\"` for "

---



## Array 
The array type is used store a dynamic array of elements of any type.
A new array can be create by writing a comma separated list between `[` and `]` e.g. `[1, 2, 3,]` or `[42, 42]`. 
A single trailing comma is allowed.

**Example**
```js
function main() {
	var array = [1, 2, 3,];
	std::println(array);
}
```

---



## Istream
Istreams are used to read 8-Bit character from a varity of sources e.g. stdin or files. 

---



## Ostream
Ostreams are used to output 8-Bit characters to a varity of targets e.g. stdin or files. 

--- 



## Function pointers
Function pointers are callable objects created by lambdas or taking the address of a normal function. A function pointer to normal function be create by prefixing the function with `&` and replacing all paramters with `_`. A function pointer can be invoked by wrapping it in () and putting a parameter list afterwards.

**Example**
```js
function main() {
	var str = "Hello World";
	var fx_ref    = &std::println(_);
	var fx_lambda = lambda(x) => std::println(x);
	(fx_ref)(str);
	(fx_lambda)(str);
}
```

---



## External
Like a function pointer but it is pointing to a externally registerd function

---



## Clock
A clock tracks the time since its creation. It's created by std::chrono::clock() and be casted to a floating point value representing the elapsed seconds.

```js
function main() {
	var clock = std::chrono::clock();
	var seconds = std::float(clock);
	std::println(std::string(seconds) + "s");
}
```

---



## Struct
_ToDo_

---



## Range
_ToDo_

---



## QUEUE
_ToDo_

---



## Stack
_ToDo_

---



## Map
_ToDo_

---



## RNG
_ToDo_

---
