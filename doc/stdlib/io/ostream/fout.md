# std::fout

## std::fout(path, open_mode)
**Parameters:**  
* path: path to file as a String
* open_mode: std::io::open_mode enum

**Return value:**  
OStream  

**Description:**  
Creates an output stream connected to a file  
If open_mode is set to OVERRIDE the file cleared before writing.  
If open_mode is set to APPEND new content appended to the end of the file.   

---

## std::fout(path)
**Parameters:**  
* path: path to file as a String

**Return value:**  
OStream  

**Description:**  
Creates an output stream connected to a file 
Default open_mode is OVERRIDE. 