# Condtional operators c?a:b a?:b a??b

### Operator c?a:b (Ternary operator)
`c?a:b` since (v1.1)  
Ternary operator  
Evaluates expression a if c is true. Otherwise b is evaluated.

### Operator a?:b (Elvis operator)
`a?:b` since (v1.1)  
Elvis operator  
Evaluates to a if a is truthy. If a is false then b is evaluated and returned.

### Operator a??b (Null coalescing operator)
`a??b` since (v1.1)  
Null coalescing operator  
Evaluates to a if a is not null. I case a is null the operator evaluates b as an alternative.

# Binary operators + - * / % << >> < > <= => == <=> != && ||
`a @ b`  
`a @= b`  

### Operator +
`a + b`  
`a += b`  
Addition, String concatenation, Array concatenation  

### Operator -
`a - b`  
`a -= b`  
Subtraction  

### Operator *
`a * b`  
`a *= b`  
Multiplication  

### Operator /
`a / b`  
`a /= b`  
Division  

### Operator %
`a % b`  
`a %= b`  
Modulo  

### Operator <<
`a << b`  
`a <<= b` (since 1.1)  
Bitshift  

### Operator >>
`a >> b`  
`a >>= b` (since 1.1)  
Bitshift  

### Operator < 
`a < b`   
Smaller  

### Operator <= 
`a <= b`   
Smaller or equal  

### Operator >
`a > b`   
Bigger  

### Operator >= 
`a >= b`   
Bigger or equal  

### Operator ==
`a == b`   
Equal  

### Operator != 
`a != b`   
Unequal  

### Operator <=> 
`a <=> b` (since 1.1)   
Three-way comparison operator
Returns an integer representing the order of the compared values
| Input  | Result |
| -      | -      |
| a < b  | -1     |
| a > b  | 1      |
| a == b | 0      |

### Operator && 
`a && b`   
Logical and  

### Operator || 
`a || b`   
Logical or  

### Conversion and type table

| Operators         | a         | b        | Result | Note      |
|-                  |-          |-         |-       |-          |
| << >>             | Int       | Int      | Int    |           |
| + - * / %         | Integral  | Integral | Int    |           |
| + - * / %         | Integral  | Float    | Float  |           |
| + - * / %         | Float     | Integral | Float  |           |
| + - * / %         | Float     | Float    | Float  |           |
| +                 | String    | String   | String | since 1.1 |
| +                 | Array     | Array    | Array  | since 1.1 |
| < > <= => == !=   | Any       | Any      | Bool   |           |
| <=>               | Any       | Any      | int    | since 1.1 |
| && \|\|           | Any       | Any      | Bool   |           |
| +                 | String    | Any      | String | until 1.1 |
| +                 | Array     | Any      | Array  | until 1.1 |
| +                 | Array     | String   | Array  | until 1.1 |
| +                 | Any       | String   | String | until 1.1 |

Integral: Bool, Char or Int

---

# Unary operators - ! ?
`@a`

### Operator -
`-a`  
Arithmetic Negation  

### Operator !
`!a`
Logical not

### Operator ?
`?a` (since 1.1)  
Null test operator  
Evaluates to true if the expression is not `null`.

### Conversion and type table

| Operators | a         | Result | Note      |
|-          |-          |-       |           |
| -         | Integral  | Int    |           |
| -         | Float     | Float  |           |
| !         | Any       | bool   |           |
| ?         | Any       | bool   | since 1.1 |

Integral: Bool, Char or Int

