# std::chain

## std::chain(fx1, fx2)
**Parameters**
* fx1: A function pointer with 1 parameter
* fx2: A function pointer with 1 parameter

**Return value**  
A function pointer.

**Description**  
The function chains two functions and returns a callable object. If the returned object is called fx1 is evaluated first and it's return value is fed into fx2. The return value of fx2 is returned.