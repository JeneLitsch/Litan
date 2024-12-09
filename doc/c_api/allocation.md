# C API - Allocations

Allocate an object

- `ltn_alloc_array`
- `ltn_alloc_map`
- `ltn_alloc_string`

## ltn_alloc_array

`ltn_Array ltn_alloc_array(ltn_Context *, const Value * data, uint64_t size)`

Allocates a new garbage collected array inside the VM and returns a handle to it.  
If either `data` or `size` is 0 an empty array is created.

## ltn_alloc_map

`ltn_Map ltn_alloc_map(ltn_Context *, const Value * keys, const Value * values, uint64_t size)`

Allocates a new garbage collected map inside the VM and returns a handle to it.  
The arrays `keys` and `values` must be of the same `size`.

## ltn_alloc_string

`ltn_String ltn_alloc_string(ltn_Context *, const char * data)`

Allocates a new garbage collected string inside the VM and returns a handle to it.  
`data` must be null terminated string.