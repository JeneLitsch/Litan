# Declaration

Declarations itself are evaluated at compile-time or load-time (static initialisation) and not at run-time. They may refer to run-time code e.g. in the case of functions.

# Statement

An statement does neither produce nor consume a temporary value on the stack.
An statement is allowed to allocate on the local call frame if necessary.

# Expression

An expression produces exactly one temporary value on the stack.
An expression is allowed to allocate on the local call frame if necessary.

# Binding

A binding consumes exactly one temporary value from the stack.
A binding is allowed to allocate on the local call frame if necessary.
