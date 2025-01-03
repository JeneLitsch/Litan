# C API - Value

Wrap values
- `ltn_value_bool`
- `ltn_value_int`
- `ltn_value_float`
- `ltn_value_array`
- `ltn_value_tuple`
- `ltn_value_map`
- `ltn_value_string`

Extract values
- `ltn_as_bool`
- `ltn_as_int`
- `ltn_as_float`
- `ltn_as_array`
- `ltn_as_tuple`
- `ltn_as_map`
- `ltn_as_string`

Check values
- `ltn_is_bool`
- `ltn_is_int`
- `ltn_is_float`
- `ltn_is_array`
- `ltn_is_tuple`
- `ltn_is_map`
- `ltn_is_string`


## ltn_value_null

`ltn_Value ltn_value_null()`

Creates a `ltn_Value` containing null.


## ltn_value_bool

`ltn_Value ltn_value_bool(ltn_Bool)`

Wraps a `ltn_Bool` into a `ltn_Value`.


## ltn_value_int

`ltn_Value ltn_value_int(ltn_Int)`

Wraps a `ltn_Int` into a `ltn_Value`.


## ltn_value_float

`ltn_Value ltn_value_float(ltn_Float)`

Wraps a `ltn_Float` into a `ltn_Value`.


## ltn_value_array

`ltn_Value ltn_value_array(ltn_Array)`

Wraps a `ltn_Array` into a `ltn_Value`.


## ltn_value_tuple

`ltn_Value ltn_value_tuple(ltn_Tuple)`

Wraps a `ltn_Tuple` into a `ltn_Value`.


## ltn_value_map

`ltn_Value ltn_value_map(ltn_Map)`

Wraps a `ltn_Map` into a `ltn_Value`.


## ltn_value_string

`ltn_Value ltn_value_string(ltn_String)`

Wraps a `ltn_String` into a `ltn_Value`.




## ltn_as_bool

`ltn_Bool ltn_as_bool(ltn_Value)`  
Extracts a `ltn_Bool` from a `ltn_Value`.  
If the value does not contain a `ltn_Bool` an error is raised. 


## ltn_as_int

`ltn_Int ltn_as_int(ltn_Value)`  
Extracts a `ltn_Int` from a `ltn_Value`.  
If the value does not contain a `ltn_Int` an error is raised. 


## ltn_as_float

`ltn_Float ltn_as_float(ltn_Value)`  
Extracts a `ltn_Float` from a `ltn_Value`.  
If the value does not contain a `ltn_Float` an error is raised. 


## ltn_as_array

`ltn_Array ltn_as_array(ltn_Value)`  
Extracts a `ltn_Array` from a `ltn_Value`.  
If the value does not contain a `ltn_Array` an error is raised. 


## ltn_as_tuple

`ltn_Tuple ltn_as_tuple(ltn_Value)`  
Extracts a `ltn_Tuple` from a `ltn_Value`.  
If the value does not contain a `ltn_Tuple` an error is raised. 


## ltn_as_map

`ltn_Map ltn_as_map(ltn_Value)`  
Extracts a `ltn_Map` from a `ltn_Value`.  
If the value does not contain a `ltn_Map` an error is raised. 


## ltn_as_string

`ltn_String ltn_as_string(ltn_Value)`  
Extracts a `ltn_String` from a `ltn_Value`.  
If the value does not contain a `ltn_String` an error is raised. 



## ltn_is_null

`bool ltn_is_null(ltn_Value value)`  
Checks whether `value` is null

## ltn_is_bool

`bool ltn_is_bool(ltn_Value value)`  
Checks whether `value` contains a `ltn_Bool`


## ltn_is_int

`bool ltn_is_int(ltn_Value value)`  
Checks whether `value` contains a `ltn_Int`


## ltn_is_float

`bool ltn_is_float(ltn_Value value)`  
Checks whether `value` contains a `ltn_Float`


## ltn_is_array

`bool ltn_is_array(ltn_Value value)`  
Checks whether `value` contains a `ltn_Array`


## ltn_is_tuple

`bool ltn_is_tuple(ltn_Value value)`  
Checks whether `value` contains a `ltn_Tuple`

## ltn_is_map

`bool ltn_is_map(ltn_Value value)`  
Checks whether `value` contains a `ltn_Map`


## ltn_is_string

`bool ltn_is_string(ltn_Value value)`  
Checks whether `value` contains a `ltn_String`
