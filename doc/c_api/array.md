# C API - Array

Operations:

- `ltn_array_at`
- `ltn_array_put`
- `ltn_array_size`
- `ltn_array_push`
- `ltn_array_pop`
- `ltn_array_insert`
- `ltn_array_erase`

## ltn_array_at

`ltn_Value ltn_array_at(ltn_Array array, ltn_Int index)`


## ltn_array_put

`void ltn_array_put(ltn_Array, ltn_Int index, ltn_Value value)`


## ltn_array_size

`ltn_Int ltn_array_size(ltn_Array array)`

Returns the size of the `array`.


## ltn_array_push

`void ltn_array_push(ltn_Array array, ltn_Value value)`


## ltn_array_pop

`ltn_Value ltn_array_pop(ltn_Array)`


## ltn_array_insert

`void ltn_array_insert(ltn_Array array, ltn_Int index, ltn_Value value)`


## ltn_array_erase

`ltn_Value ltn_array_erase(ltn_Array array, ltn_Int index)`
