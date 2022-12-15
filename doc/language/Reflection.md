# Reflection

Reflections can be used to inspect properties of program itself.

## Syntax 

The reflection query is an expression.

```js
reflect(/* query goes here */);
```

## Namespace

A namespace querry returns the name of the namespace and inspects members of the said namespace.

```js
var result = reflect(namespace foo);
```

A struct with all the collected data is returned.

```
namespace
+---name
+---functions
    +---[function...]  
```

## Function

A function query returns information reagrding a function. For functions with parameters placeholders _ are used.

```js
var result = reflect(function f1());
var result = reflect(function f2(_,_));
```

A struct with all the collected data is returned.

```
function
+---name
+---full_name
+---fx_ptr
```
