# Define
Defines are used to declare global constants. Function calls are not allowed in defines.

```javascript
namespace my_namespace {
	define foo = "Hello World";
	define bar = 42;
}

function main() {
	std::println(my_namespace::foo);
	std::println(my_namespace::bar);
}
```

The output is
```
Hello World
42
```