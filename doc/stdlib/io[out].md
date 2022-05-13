### std::cout()
**Parameters**  

**Return value**  
OStream  

**Description**  
Creates an output stream connected to stdout  

---

### std::fout(path, open_mode)
**Parameters**  
* path: path to file as a String
* open_mode: std::io::open_mode enum

**Return value**  
OStream  

**Description**  
Creates an output stream connected to a file  
If open_mode is set to OVERRIDE the file cleared before writing.  
If open_mode is set to APPEND new content appended to the end of the file.   

---

### std::fout(path)
**Parameters**  
* path: path to file as a String

**Return value**  
OStream  

**Description**  
Creates an output stream connected to a file 
Default open_mode is OVERRIDE. 

---

### std::strout()
since 1.2  
**Parameters**  

**Return value**  
OStream  

**Description**  
Creates an output string stream  

---

### std::print(stream, value)
**Parameters**  
* stream: stream to print to
* value: value to be printed

**Return value**  
null  

**Description**  
Formats and prints value to stream  

---

### std::print(value)
**Parameters**  
* value: value to be printed

**Return value**  
null  

**Description**  
Formats and print value to stdout

---

### std::println(stream, value)
**Parameters**  
* stream: stream to print to
* value: value to be printed
 
**Return value**  
null  

**Description**  
Formats and prints value to stream and adds newline ("\n") a the end  

---

### std::println(value)
**Parameters**  
* value: value to be printed
 
**Return value**  
null  

**Description**  
Formats and prints value to stdout and adds newline ("\n") a the end  