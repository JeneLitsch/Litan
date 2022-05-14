# std::bits::set

## std::bits::set(number, index, value)
**Parameters:**
- number: a single integral value
- index: an integer index
- value: boolean value

**Return value**
single int with bit set to value

**Description:**
The function takes an integer (or other integral value) and sets the bit at position _index_ to _value_. If number is smaller than int it get converted to int. The bit is set to 0 if value is false or to 1 if value is true.
