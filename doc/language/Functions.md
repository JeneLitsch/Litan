# Functions

A Litan function can be declared in one of the following ways.

Statemement block as function body  
```javascript
function name(param1, ...) {  
    // Some code here  
}
```

Single expression as function body    
since 1.2
```javascript
function name(param1, ...) => // Expression goes here  
```

The function main() with zero or one parameter is the starting point of a Litan program.  

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

### init
* An init function can be called from the outside. It's address is added to fx table. Init functions can be used as alternative main functions. An init function must have either 0 or 1 paramter. 
