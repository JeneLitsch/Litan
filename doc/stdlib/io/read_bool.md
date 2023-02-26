# std::read_bool

## std::read_bool()
**Parameters:**  

**Return value:**  
optional&lt;bool&gt;   

**Description:**  
Reads a single boolean from stdin.
0 and false evaluate to false.
1 and true evaluate to true.
Null is returned if an error occurs.

---

## std::read_bool(stream : istream)
**Parameters:**  
- stream: an input stream  

**Return value:**  
optional&lt;bool&gt;  

**Description:**  
Reads a single bool from stream.
0 and false evaluate to false.
1 and true evaluate to true.
Null is returned if an error occurs.

