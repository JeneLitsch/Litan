# Global variable

Global variables share state across the whole program. They should be used with caution.

## Declaration

A global variable can be declared at namespace level with the following syntax.
```js 
global /* name */;
```

A start/default value can also be assigned to a global value.
```js 
global /* name */ = /*expression*/;
```

If no default is set. The global variable will be `null` until assigned otherwise. Inside the expression no other globals or can be can accessed. Defines can be used tough.

## Example

```js
global x;

namespace foo {
	global x;
	function get_x() => x
}

function get_x() => x

function set_globals() {
	x = 1;
	foo::x = 2;
}

function main(args) {
	set_globals();
	std::println(get_x());
	std::println(foo::get_x());
	std::println(x + foo::x);
}
```

Output
```
1
2
3
```