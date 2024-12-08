# Map

A data structure consisting of key-value pairs.



## Member functions

### ->size(): Int

Return the number entries in the map.

### ->is_empty(): Bool

Returns whether the map is empty (size == 0).

### ->at(key : Any): Any

Returns the value associated with a given key.
If the key is not in the map null is returned instead.

### ->has(key : Any): Bool

Returns whether the map contains a given key.

### insert(key : Any, value: Any): Null

Writes the value for given key into the map.
If the key is unknown, a new entry created.

Same as `map[key] = value`

### erase(key : Any): Any

Removes the entry associated with a given key from the map.
The value of the pair is returned

If no entry matches, no entry is removed and null is returned

### keys(): Array

Returns all keys in an array;

### values(): Array

Returns all values in an array;


### merged(other : Map): Map

Merge two maps without altering the originals.
Duplicate keys are not copied over.


## Map Literals

Empty map

```
[:]
```

Filled map
```
[1:2]
[1:2, 3:4,]
```

A single trailing comma is allowed.