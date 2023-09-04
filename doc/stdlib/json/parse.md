# std::json::parse

## std::json::parse(string)
**Parameters:**
- string: json string

**Return value:**  
any

**Description:**  
Translates a JSON string into a Litan data structure. A misformed string causes a exception.

| JSON   | Litan            |
| ------ | ---------------- |
| null   | null             |
| bool   | bool             |
| number | float            |
| string | string           |
| array  | array(any)       |
| object | map(string, any) |
