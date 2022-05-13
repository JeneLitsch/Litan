# Streams

### std::cin()
**Parameters**  

**Return value**  
IStream

**Description**  
Creates an input stream connected to stdin

---

### std::fin(path)
**Parameters**  
path: Path to file as a string

**Return value**  
IStream

**Description**  
Creates a filestream to the specified path

---

### std::strin(str)
since 1.2  
**Parameters**  
str: String to initialize string stream

**Return value**  
IStream

**Description**  
Creates a new input stringstream

---

### std::read(), std::read_str()
since 1.2  
**Parameters**  

**Return value**  
String  

**Description**  
Reads a single "word" from stdin. Reads until next white space.  

---

### std::read(stream), std::read_str(stream)
since 1.2  
**Parameters**  
* stream: an input stream

**Return value**  
String  

**Description**  
Reads a single "word" from passed stream. Reads until next white space.  

--- 

### std::readln()
**Parameters**  

**Return value**  
String  

**Description**  
Reads a single line from stdin.

---

### std::readln(stream)
**Parameters**  
* stream: an input stream

**Return value**  
String  

**Description**  
Reads a single line from stream.

---

### std::read_int()
**Parameters**  

**Return value**  
Int  

**Description**  
Reads a Int from stdin.

---

### std::read_int(stream)
**Parameters**  
* stream: an input stream

**Return value**  
Int  

**Description**  
Reads a Int from stream.

---

### std::read_float()
**Parameters**  

**Return value**  
Float  

**Description**  
Reads a single floating point number from stdin.

---

### std::read_float(stream)
**Parameters**  
* stream: an input stream

**Return value**  
Float  

**Description**  
Reads a single floating point number from stream.

---

### std::read_bool()
since 1.2  
**Parameters**  

**Return value**  
Bool  

**Description**  
Reads a single boolean from stdin.
0 and false evaluate to false
1 and true evaluate to true

---

### std::read_bool(stream)
since 1.2  
**Parameters**  
* stream: an input stream

**Return value**  
Bool  

**Description**  
Reads a single bool from stream.
0 and false evaluate to false
1 and true evaluate to true

---

### std::read_char()
since 1.2  
**Parameters**  

**Return value**  
Char  

**Description**  
Reads a single character from stdin.

---

### std::read_char(stream)
since 1.2  
**Parameters**  
* stream: an input stream

**Return value**  
Char  

**Description**  
Reads a single character from stream.

---

### std::read_all()
since 1.2  
**Parameters**  

**Return value**  
String  

**Description**  
Returns the entire stream buffer of stdin as a string 

---

### std::read_all(stream)
since 1.2  
**Parameters**  
* stream: an input stream

**Return value**  
String  

**Description**  
Returns the entire stream buffer as a string 