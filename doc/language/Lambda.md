Besides normal functions lambdas can be declared.

### Syntax

A lambda functions is created using the following syntax: 
```javascript
lambda [_captures..._] (_paramters..._) {
    // Some code here
}
```

### [] and () are optional

The capture block [] be omitted if the lambda does not capture any variables.
Likewise () can be omitted if the lambda does not take paramters

All 4 are are valid lambdas.

```javascript
lambda [] () {}
```

```javascript
lambda () {}
```

```javascript
lambda [] {}
```

```javascript
lambda {}
```

### Usage
Lambdas are normal expressions/literals.

Lambdas can be assigned to variables and returned like any other expression or literal.
```javascript
function make_lambda(a) {
    var fx = lambda [a] {
        std::println(a);
    };
    return fx;
}
```
or
```javascript
function make_lambda(a) {
    return lambda [a] {
        std::println(a);
    };
}
```

The type created by a lambda is a functions pointer.

Lambdas can be called with std::invoke.
