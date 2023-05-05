# Functions

## Header

Every Litan function starts with its header. Every parameter can annotated with type by adding a colon `:` and a typename.

```js
function name(param1, param1, ...) /*Qualifiers*/
```


## Body

After the header follows the function body. There are two different types of bodies. Either a block statement can used as body or a single expression with an arrow `=>` in front. The later is equivalent to a block statement function only containing a single return statement.

```javascript
function name(param1, ...) {  
    // Some code here  
}
```
```javascript
function name(param1, ...) => // Expression goes here  
```

## Main-Function

The function main() with zero or one parameter is the default starting point of a Litan program. It's declared as extern automatically.

## Examples
```javascript
function hello() {  
    return "Hello World";
}
```

```javascript
function main() {  
    std::println("Hello World");
}
```

```javascript
function main(args) {  
    std::println(args);
}
```

```javascript
function add(a, b) const {
    return a + b;
}
```

```javascript
function add(a, b) const private => a + b
```
  
## Calls
`foo(42, "Hello World")` The function foo is called with the parameters `42` and `"Hello World"`
  

## Qualifiers
### const 
* No reassingments are allowed inside the function  
* A const function can only call other const functions  

### private
* A private function cannot be called from an ouitside namespace  

### extern
* An extern function can be called from the outside. It's address is added to fx table. Extern functions can be used as alternative main functions. An extern function must have either 0 or 1 paramter. `main()` and `main(args)` are declared extern by default. 
