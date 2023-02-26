# std::lerp

## std::lerp(a : float, b : float, t : float)
**Parameters:**
- a: minimum value
- b: maximum value
- t: sample point between 0 and 1

**Return value:**  
float

**Description:**  
Calculates a+t*(b-a).  
When t is 0 the the return value is a.  
When t is 1 the the return value is b.  