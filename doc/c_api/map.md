# C API - Map


Operations:

- `ltn_map_at`
- `ltn_map_put`
- `ltn_map_size`
- `ltn_map_has`


## ltn_map_at

`ltn_Value ltn_map_at(ltn_Map map, ltn_Value key)`


## ltn_map_put

`void ltn_map_put(ltn_Map map, ltn_Value key, ltn_Value value)`


## ltn_map_size

`ltn_Int ltn_map_size(ltn_Map map)`

Returns the size of the `map`.


## ltn_map_has

`ltn_Bool ltn_map_has(ltn_Map map, ltn_Value key)`

Check whether `map` contains the `key`.