# Reflection

Reflections can be used to inspect properties of program itself.

## Syntax 

The reflection query is an expression.

```js
reflect(/* query goes here */);
```

## Line

```js
var line = reflect(line);
```

Returns the current line.

Note 1: If the expression is split over mutiple lines, the line containing the `reflect` keyword is used for the line number.


```js
var line = reflect(
	line
);
```

## File

```js
var file = reflect(file);
```

Returns info about the current file.

```
file
+---name
```

## Location

```js
var file = reflect(location);
```

Returns combined info about the file and the current line.

```
location
+---line
+---file
    +---name
```

Note 2: Note 1 (Line) applies to Location too.

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
+---const
+---private
+---extern
```
