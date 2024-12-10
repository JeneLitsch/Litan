# StdLib - Strings

A collection of string related helper functions

Functions:
- std::left_pad
- std::right_pad
- std::str
- std::split
- std::join
- std::replace


## std::left_pad

`std::left_pad(string : String, min_size : String): String`

Returns a copy the string but adds spaces on the left to match the minimum size.  

## std::right_pad

`std::left_right(string: String, min_size : Int): String`

Returns a copy the string but adds spaces on the right to match the minimum size.  

## std::str

`std::str(value: Any) const : String`

Returns the stringified representation of a given value.

Edge Cases:
- A string is just copied.
- The contained string of an ouput string stream is extracted. 

## std::split

`std::str(string : String, deliminator : Int) const : Array[String]`

Splits the string at the delimiter and returns the separated parts in an array.  


## std::join

`std::join(strings : Array[String], joiner : String) const : String`
 
Joins all `strings` into a single string separated by the `joiner`.

## std::replace

`std::replace(string : String, search_for : String, replace_with: String) const : String`

Replaces all occurences of `search_for` in `string` with `replace_with`.


