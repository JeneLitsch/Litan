### std::invoke(fx, params)
**Parameters**
* fx: A callable type
* param: An array of parameters

**Return value**  
Return value of _fx_

**Description**  
Takes a callable function pointer and an array of parameters.
"std::invoke" calls the function and forwards the return value of the call.

**Example**
```c++
std::invoke(&foo(_,_,_), [1,2,3])
```

---

### std::invoke(fx)
TODO
