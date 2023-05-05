# Litan

Litan is a gradual typed programming language with a C-like syntax.
The Compiler and Bytecode-VM can be used as standalones or C++-Library to add scripts to any application.

## Hello World

```js
function main() {
    std::println("Hello World");
}
```

## Lamdas and Higher-Order-Functions

Litan has fully-featured lambda expressions and supports higher-order-functions.

```js
function use_lambda(fx) {
    return fx(1, 2);
}

function make_lambda(c) 
    => lambda[c](a, b) => (a + b + c)

function main() {
    std::println(use_lambda(make_lambda(3))); // 6
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

Litan uses structs whose members can added or removed dynamically.

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

## Useful Libraries

- [Sphinx](https://github.com/JeneLitsch/Sphinx) (Unit test framework)
- [SFML](https://github.com/JeneLitsch/Litan-SFML)

## Build, Use and Install

### Requirements

- CMake 3.13 or newer
- A modern C++ compiler with C++20 support
  - Clang++-10 or newer
  - GCC-10 or newer
- stdxx library

### Use as Standalone

1. Clone the repository recursively.
2. Run `./build.sh` to compile the compiler, vm and everything needed. 
   - Note: Clang++ is choosen by default but this can be changed.
Just run `./build.sh COMPILER_GOES_HERE` in this case.
3. Run `./install.sh` to install ltn, ltnc, ltnvm and ltninfo into the /usr/local/bin/ directory.

### Use as library

1. Add litan as a submodule to your project.
2. Add stdxx as a submodule to your project.
3. Add the litan subdirectory to your project: e.g. `add_subdirectory(libs/litan)`
4. Link the library: e.g. `target_link_libraries(my_project litan)`
5. Include the main header: e.g. `#include "libs/litan/Litan.hxx"`
