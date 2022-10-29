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
result
+---name
+---functions
    +---[]
        +---name
        +---fx_ptr 
        +---const 
        +---extern 
  
```