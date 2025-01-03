# Ouput Stream / std::OStream

Ostreams are used to output 8-Bit characters to a varity of targets e.g. stdout or files. 

## Static Functions

### . is(value : Any) : Bool

Checks whether value is an output stream.

### . cast(value : Any) : OStream

Returns value if value is a output stream. Otherwise null is returned.