# Input Stream / std::IStream

Istreams are used to read 8-Bit characters from a varity of sources e.g. stdin or files.

## Sources

- Files: fin, fout
- Stdin/Stdout: cin, cout
- Stringbuffers: strin, strout
  

## Static Functions

### . is(value : Any) : Bool

Checks whether value is an input stream.

### . cast(value : Any) : IStream

Returns value if value is a input stream. Otherwise null is returned.