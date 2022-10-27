# General Info

# Precedence

|     | Operators    | Description   |
| --- | ------------ | ------------- |
| 1   | [] .         | Postfix Unary |
| 1   | - ! ~ ?      | Prefix Unary  |
| 2   | **           | Power         |
| 3   | *  /  %      | Factor        |
| 4   | + -          | Term          |
| 5   | << >>        | Bitshift      |
| 6   | <=>          | Threeway      |
| 7   | < > <= >=    | Comapare      |
| 8   | == !=        | Equality      |
| 9   | &            | Bitwise and   |
| 9   | ^            | Bitwise xor   |
| 9   | &vert;       | Bitwise or    |
| 9   | &&           | Logic and     |
| 9   | &vert;&vert; | Logic or      |
| 9   | ?? ?: ? :    | Conditional   |

# Arithmetic + - * / % **

| L        | R        | Result | l + r         |
| -------- | -------- | ------ | ------------- |
| Integral | Integral | Int    | Addition      |
| Float    | Integral | Float  | Addition      |
| Integral | Float    | Float  | Addition      |
| Float    | Float    | Float  | Addition      |
| String   | String   | String | Concatination |
| Array    | Array    | Array  | Concatination |

| L        | R        | Result | l - r       |
| -------- | -------- | ------ | ----------- |
| Integral | Integral | Int    | Subtraction |
| Float    | Integral | Float  | Subtraction |
| Integral | Float    | Float  | Subtraction |
| Float    | Float    | Float  | Subtraction |

| L        | R        | Result | l * r          |
| -------- | -------- | ------ | -------------- |
| Integral | Integral | Int    | Multiplication |
| Float    | Integral | Float  | Multiplication |
| Integral | Float    | Float  | Multiplication |
| Float    | Float    | Float  | Multiplication |

| L        | R        | Result | l / r            |
| -------- | -------- | ------ | ---------------- |
| Integral | Integral | Int    | Integer Division |
| Float    | Integral | Float  | Division         |
| Integral | Float    | Float  | Division         |
| Float    | Float    | Float  | Division         |

| L        | R        | Result | l % r  |
| -------- | -------- | ------ | ------ |
| Integral | Integral | Int    | Modulo |
| Float    | Integral | Float  | fmod   |
| Integral | Float    | Float  | fmod   |
| Float    | Float    | Float  | fmod   |


| L       | R       | Result | l ** r |
| ------- | ------- | ------ | ------ |
| Numeric | Numeric | Float  | Power  |

```js
function main() {
	std::println(20 + 22); // 42
}
```

```js
function main() {
	std::println("Hello" + " " + "World"); // Hello World
}
```

```js
function main() {
	std::println([1,2,3] + [4,5,6]); // [1, 2, 3, 4, 5, 6]
}
```

```js
function main() {
	std::println(2**10); // 1024
}
```

# Arithmetic -

| X        | Result | -x                                   |
| -------- | ------ | ------------------------------------ |
| Integral | Int    | Negate / Multiply by -1 / Flips sign |
| Float    | Float  | Negate / Multiply by -1 / Flips sign |

# Bitwise & | ^

| L        | R        | Result | &           |
| -------- | -------- | ------ | ----------- |
| Integral | Integral | Int    | Bitwise and |

| L        | R        | Result | &vert;     |
| -------- | -------- | ------ | ---------- |
| Integral | Integral | Int    | Bitwise or |

| L        | R        | Result | ^           |
| -------- | -------- | ------ | ----------- |
| Integral | Integral | Int    | Bitwise xor |

```js
function main() {
	std::println(0b11 & 0b10); // 2
}
```

```js
function main() {
	std::println(0b01 | 0b10); // 3
}
```

```js
function main() {
	std::println(0b01 ^ 0b11); // 2
}
```

# Bitwise ~

| x        | Result | ~x                   |
| -------- | ------ | -------------------- |
| Integral | Int    | Bitwise not/Bit flip |

```js
function main() {
	std::println(~0b0); // -1
}
```

# Comparison <=> == != < > <= >= 

| L   | R   | Result | <=>                 |
| --- | --- | ------ | ------------------- |
| Any | Any | int    | Threeway comparison |

| L   | R   | Result | ==    |
| --- | --- | ------ | ----- |
| Any | Any | Bool   | Equal |

| L   | R   | Result | !=      |
| --- | --- | ------ | ------- |
| Any | Any | Bool   | Unequal |

| L   | R   | Result | <    |
| --- | --- | ------ | ---- |
| Any | Any | Bool   | Less |

| L   | R   | Result | >       |
| --- | --- | ------ | ------- |
| Any | Any | Bool   | Greater |

| L   | R   | Result | <=         |
| --- | --- | ------ | ---------- |
| Any | Any | Bool   | Less Equal |

| L   | R   | Result | >=            |
| --- | --- | ------ | ------------- |
| Any | Any | Bool   | Greater Equal |

# Bitshift << >>

| L        | R        | Result | l << r        |
| -------- | -------- | ------ | ------------- |
| Integral | Integral | Int    | Bitshift left |

| L        | R        | Result | l >> r         |
| -------- | -------- | ------ | -------------- |
| Integral | Integral | Int    | Bitshift right |

# Logic && || 

All logic operators implement a short circuit mechanism. If the first operand determines the final result the second one is not evaluated.

| L   | R   | Result | l && r      |
| --- | --- | ------ | ----------- |
| Any | Any | Int    | Logical and |

| L   | R   | Result | l  &vert;&vert; r |
| --- | --- | ------ | ----------------- |
| Any | Any | Int    | Logical or        |

# Logic !

| X   | Result | !x          |
| --- | ------ | ----------- |
| Any | Bool   | Logical not |

# Conditional operator ?: ??

| L   | R   | Result | l ?: r                    |
| --- | --- | ------ | ------------------------- |
| Any | Any | Int    | Binary condition operator |

| L   | R   | Result | l ?? r                   |
| --- | --- | ------ | ------------------------ |
| Any | Any | Int    | Null coalescing operator |

# Check ?

Return false if x is null and true otherwise.

| X   | Result | ?x        |
| --- | ------ | --------- |
| Any | Bool   | Null test |

# Ternary ?:

Returns l if c is truthy and to r if c is not.

| c   | l   | r   | Result | c ? l : r                 |
| --- | --- | --- | ------ | ------------------------- |
| Any | Any | Any | Int    | Binary condition operator |

# Operator .
 
TODO

# Operator []

TODO
