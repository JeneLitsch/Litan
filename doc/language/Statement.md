# Statement

## Conditional [`stmt.conditional`]

```js
conditional {
    case /*condition : expr*/ => /*body : stmt*/
    ...
};
```

```js
conditional {
    case /*condition : expr*/ => /*body : stmt*/
    ...
    else  => /*body : stmt*/
};
```

The conditional statement checks the conditions in sequence.
The body belonging to the first matching condition is executed.

If no condition matches the behavior depends on the existence of the else branch.
If the else brach exists, its body is executed.
Otherwise no code is executed.