# Global variable

Global variables share state across the whole program. They should be used with caution.

## Declaration

A global variable can be declared at namespace level with the following syntax.
```js 
global /* name */;
```

A start/default value can also be assigned to global value.
```js 
global /* name */ = /*expression*/;
```

If no default is set. The global variable will be `null` until assigned otherwise.

## Usage

To use a global variable inside a function it must preceded by the keyword global.

```js
... global /* name */ ...
```

## Example

```js
global x;

namespace foo {
	global x;
	function get_x() => global x
}

function get_x() => global x

function set_globals() {
	global x = 1;
	global foo::x = 2;
}

function main(args) {
	set_globals();
	std::println(get_x());
	std::println(foo::get_x());
	std::println(global x + global foo::x);
}
```

Output
```
1
2
3
```