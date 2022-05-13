### std::char(x)
**Parameters**
* x: value castable to Char

**Return value**  
Char  

**Description**  
Casts a numerical type to an 8-bit char  

---

### std::int(x)
**Parameters**
* x: value castable to Int

**Return value**  
Int  

**Description**  
An Int is returned unchanged.  
A Float is returned truncated.  
A String is parsed to Int.  

--- 

### std::float(x)
**Parameters**
* x: value castable to Float

**Return value**  
Float  

**Description**  
An Int is converted to a Float of the same value.  
A Float is returned unchanged.  
A String is parsed to Float.  

--- 

### std::string(x)
**Parameters**
* x: value castable to String

**Return value**  
String  

**Description**  
Returns string representation of x. Same as ``"" + x``. 

--- 

### std::bool(x)
**Parameters**
* x: value castable to Bool

**Return value**  
Bool  

**Description**  
Decides the truthiness.
A Bool is returned unchanged.  
An Int of value 0 is false and everything else is true.  
A Float of value 0 is false and everything else is true.  
Null is false.  

--- 

### std::array(x)
**Parameters**
* x: value castable to Array

**Return value**  
Array  

**Description**  
Extracts the Array from a Range.  
An array is returned unchanged.  
Creates a single element array otherwise.
