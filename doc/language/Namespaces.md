# Namespace

## Syntax

```C++
namespace /*name*/ {
	// Stuff goes here
}
```

Nested namespaces can also declared with this simplified syntax. Every namespace layer is separated by `::`.

```C++
namespace /*name*/::/*name*/... {
	// Stuff goes here
}
```

### Example
```js
namespace foo {
    function fx() => 42
	namespace bar {
	    function fx() => 1
	}
}

namespace bar {
    function fx() => 1337
}

namespace foo::bar::baz {
    function fx() => 2
}

function main() {
	std::println(foo::fx());
	std::println(bar::fx());
	std::println(foo::bar::fx());
	std::println(foo::bar::baz::fx());
}
```

The output is:
```
42
1337
1
2
```