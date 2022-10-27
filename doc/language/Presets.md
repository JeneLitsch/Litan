# Presets

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