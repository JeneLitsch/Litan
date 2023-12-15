# std::iter::iter

## std::iter::iter(iterable) const
**Parameters:**
- iterable: any iterable type

**Return value:**  
iterator&lt;any&gt;

**Description:**  
Creates an iterator from the passed argument.
Iterators are just forwarded unchanged.

Depending on the data type of `iterable` the iterator produces the following elements:

- string: Iterates over characters
- array: Iterates over elements
- tuple: Iterates over elements
- map: Iterates over key-value pair
- couroutine: Repeatedly calls coroutine. 
- nouroutine: Expired coroutine iterator. Returns iterator_stop