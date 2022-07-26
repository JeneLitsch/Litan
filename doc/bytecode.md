# Bytecode

The following document describes the bytecode format.

## Header

| Field         | Datatype         | Size in bytes | 
| -             | -                | -             |
| version       | Uint8            | 1             |
| fx_table size | Uint64           | 8             |
| fx_table      | map[string, int] | (see below)   |

The fx_table consists of an array of 3-tuples (name size, name, addr).

| Field         | Datatype         | Size in bytes | 
| -             | -                | -             |
| name size     | uint64           | 8             |
| name          | string           | name size     |
| addr          | uint64           | 8             |

## Program

## End
The file must end with an exit instructions