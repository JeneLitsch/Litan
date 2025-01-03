# Bool / std::Bool

The bool type can be set to two states `true` and `false`. 
A value of type bool can be created by the `true` or `false` keyword.
A boolean value can be implicitly converted or casted to every numeric type where false becomes 0 and true becomes 1.

**Example**
```js
function main() {
	var a = true;
	var b = false;
}
```


## Static Functions

### . new() : Bool

Returns false.

### . is(value : Any) : Bool

Checks whether value is a boolean.

### . cast(value : Any) : Bool

Casts value to boolean (evaluates truthyness).