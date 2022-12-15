# Litan

Litan is a gradual typed programming language with a C-like syntax.

## Hello World

```js
function main() {
    std::println("Hello World");
}
```

## Type Annotations

Litan allows optional type annotations. The compiler can help you catch type related bugs.

```js
function main() {
    var a : int = 4; // Ok!
}
```

```js
function main() {
    var a : string = 4; // Compiler error
}
```

```js
function f(x : string) -> int 
	=> x // Compiler Error: Cannot return string as int

function main() {
	f(4); // Compiler Error: Cannot pass int as string
}
```

## Reflections

Reflections allow you to gather infos about your programm at compile-time.

```js
function main() {
    std::println("Line: " + std::str(reflect(line))); // Line 2
}
```

[Learn more](/doc/language/Reflection.md)

## Structs

Litan uses structs whose members can added or remove dynamically.

```js
function main() {
    var object = std::struct();
    object.foo = 42;
    object.bar = 1337;
    std::println(object.foo);
    std::println(object.bar);
}
```

## Presets

Presets are predefined structs. The compiler generates a constructor functions for each declared preset.

```js 
preset MyPreset {
    var foo;
    var bar;
}

function main() {
    var object = MyPreset(42, 1337);
    std::println(object.foo);
    std::println(object.bar);
}
```