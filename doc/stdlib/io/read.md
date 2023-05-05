# std::read

## std::read(), std::read_str()
**Parameters:**  

**Return value:**  
optional&lt;string&gt;  

**Description:**  
Reads a single "word" from stdin.
Reads until next white space.
Null is returned if an error occurs or the stream reaches EOF.

---

## std::read(stream), std::read_str(stream)
**Parameters:**  
* stream: an input stream

**Return value:**  
optional&lt;string&gt;  

**Description:**  
Reads a single "word" from passed stream.
Reads until next white space.
Null is returned if an error occurs or the stream reaches EOF.
