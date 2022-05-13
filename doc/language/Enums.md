# Enums

```js
enum my_enum {
	FOO;
	BAR : 5;
	BAZ;
}
```

```js
function main() {
	std::println(my_enum::FOO);
	std::println(my_enum::BAR);
	std::println(my_enum::BAZ);
}
```
All three values are plain integers.


The output is
```
0
5
6
```