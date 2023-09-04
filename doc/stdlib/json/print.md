# std::json::print

## std::json::print(value)
**Parameters:**
- value: litan data structure

**Return value:**  
json formatted string

**Description:**  
Translates a Litan data structure into a JSON string. Unsupported datatypes throw exception.

| Litan      | JSON   |
| ---------- | ------ |
| null       | null   |
| bool       | bool   |
| char       | number |
| int        | number |
| float      | number |
| string     | string |
| array(any) | array  |
| map        | object |
