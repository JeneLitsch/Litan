### Declare a namespace

```C++
namespace <name> {
...
}
```

### Use a namespace
```C++
namespace::function
```

### Example
```C++
namespace foo {
    namespace bar {
        function fx() {
            return 41;
        }
    }
    function fx() {
        return bar::fx() + 1;
    }
}

function main() {
    foo::bar::fx();
    return foo::fx();
}

```
main() returns 42
