# Struct

## Non existing members

A non existing member behaves as a null value.

## Initialization

A struct is either created by a preset or by struct initialization as shown below.

```js
var obj = [
    .a = 1,
    .b = 2,
    .c = 3,
];
```

## Presets

Presets are declared at a namespace level and can be used to create structs more easily.  

The following example describes a struct "my_struct" with two member variables "foo" and "bar".  

```js
preset my_struct {
	var foo;
	var bar;
}
```

The compiler generates a constructor for every declared preset.  

```js
function main() {
	var x = my_struct(42, 1337);
	std::println(x.foo);
	std::println(x.bar);
}
```