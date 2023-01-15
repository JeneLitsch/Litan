# std::str(value) -&gt; string

Converts a given value into string form.

## Supported types

- bool: `"null"`
- true: `"true"`/`"false"`
- char: A string with one char
- int: Decimal representation of int
- float: Decimal representation of float 
- string: Just a copy of the string 
- array: `"[elements, ...]"`
- tuple: `"(elements, ...)"` 
- ostream: `"<ostream>"`
- istream: `"<istream>"`
- fx_ptr: `"<fx:address,arity>"`
- external: `"<external:id>"`
- clock: `"<clock:seconds>"`
- struct: `"<struct>"`
- queue: `"<elements, ...>"`
- stack: `"<elements, ...>"`
- map: `"{key : val, ...}"`
- rng: `"<RNG>"`