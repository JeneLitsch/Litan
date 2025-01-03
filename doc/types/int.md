# Int / std::Int
The int type is used to store a 64-Bit singed integer value.
A value of type int can be created by a int literal e.g. `0`, `-1` or `42` 

## Decimal Literals
```js
function main() {
	var a = 42;
	var b = 1337;
	std::println(a);
	std::println(b);
}
```

## Binary Literals

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

## Hexadecimal Literals

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

## Character Literals

Creates an integer holding the unicode value of the character.

**Example**
```js
function main() {
	var a = 'A';
	var x = 'X';
	std::println(a); // 64
	std::println(x); // 88
}
```


## Static Functions

### . new() : Int

Returns `0`.

### . is(value : Any) : Bool

Checks whether value is an integer.

### . cast(value : Any) : Int

Casts value to an integer.