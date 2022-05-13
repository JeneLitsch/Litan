# Presets
since 2.0  
Presets are declared at a namespace level and can be used to create structs more easily.  

The following example describes a struct "my_struct" with two member variables "foo" and "bar".  

```
preset my_struct {
	var foo;
	var bar;
}
```

The compiler generates a constructor for every declared preset.  

```javascript
function main() {
	var x = my_struct(42, 1337);
}
```