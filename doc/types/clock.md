# Clock / std::Clock

A clock tracks the time since its creation. It's created by std::chrono::clock() and be casted to a floating point value representing the elapsed seconds.

```js
function main() {
	var clock = std::chrono::clock();
	var seconds = std::float(clock);
	std::println(std::string(seconds) + "s");
}
```

## Static Functions

### . new() : Clock

Creates a new clock.

### . is(value : Any) : Bool

Checks whether value is a clock

### . cast(value : Any) : Clock

Returns value if value is a clock. Otherwise null is returned.