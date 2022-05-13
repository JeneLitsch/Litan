# algorithm.ltn


## std::for_each(range, fx)
**Parameters**
* range: A range or an array
* fx: Callable type (e.g. FxPtr or External) which takes one parameter

**Return value**  
null  

**Description**  
Calls fx for every element in range.  

---



## std::sum(range, start)
**Parameters**
* range: A range or an array
* start: Start value to add to

**Return value**  
The calculated sum  

**Description**  
Adds all elements to start.  

---



## std::sum(range)
**Parameters**
* range: A range or an array

**Return value**  
The calculated sum  

**Description**  
Starts with 0 and sums all elements in range.  

---



## std::sort_ascn(range)
**Parameters**
* range: A range or an array

**Return value**  
null  

**Description**  
Sorts all elements in range in ascending order.  

---



## std::sort_desc(range)
**Parameters**
* range: A range or an array

**Return value**  
null  

**Description**  
Sorts all elements in range in descending order.  

---



## std::is_sorted_ascn(range)
**Parameters**
* range: A range or an array

**Return value**  
null

**Description**  
Checks if a range or an array is sorted in ascending order.

---



## std::is_sorted_desc(range)
**Parameters**
* range: A range or an array

**Return value**  
null

**Description**  
Checks if a range or an array is sorted in descending order.

---



## std::copy_front(range, target)
**Parameters**
* range: A range or an array
* target: An array

**Return value**  
null  

**Description**  
Copies all elements in range front of target.  

---



## std::copy_back(range, target)
**Parameters**
* range: A range or an array
* target: An array

**Return value**  
null  

**Description**  
Copies all elements in range to the back of target.  

---



## std::fill(range, value)
**Parameters**
* range: A range or an array
* value: An arbitrary value

**Return value**  
null  

**Description**  
Fills the range with value.

---



## std::reverse(range)
**Parameters**
* range: A range or an array

**Return value**  
null  

**Description**  
Reverses the order of all elements in range.
