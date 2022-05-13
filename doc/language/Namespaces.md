# Namespace

## Syntax

```C++
namespace /*name*/ {
	// Stuff goes here
}
```

### Example
```js
namespace foo {
    function fx() => 42
}

namespace bar {
    function fx() => 1337
}

function main() {
	std::println(foo::fx());
	std::println(bar::fx());
}
```

The output is
```
42
1337
```