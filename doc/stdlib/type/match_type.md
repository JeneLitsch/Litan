# std::match_type

## std::match_type(value, cases, default_case)

**Parameters:**
* value: Any value
* cases: Iterable container of tuples (type, fx).
* default_case: Unary function.

**Return value:**  
any

**Description:**  
Iterates over all cases and checks `value` against the types. 
The matching function is called. 
If no case matches `default_case` is called. 
The return value of the called funtion is returned.

## std::match_type(value, cases)

**Parameters:**
* value: Any value
* cases: Iterable container of tuples (type, fx).

**Return value:**  
any

**Description:**  
Same as the 3 parameter overload but the `default_case` throws an exception. 

## Examples

```
function f(x) => std::match_type(x, [
	(<int>,   lambda(x) => std::println("This in an int")),
	(<float>, lambda(x) => std::println("This in a float")),
    ],        lambda(x) => std::println("Another type"))


function main() {
	f(42);
	f(13.37);	
	f("Hello World");	
}
```

Output:
```
This in an int
This in a float
Another type
```
