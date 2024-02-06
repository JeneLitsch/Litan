# Expression

## Conditional [`expr.conditional`]

```js
conditional {
    case /*condition : expr*/ => /*body : expr*/
    ...
}
```

```js
conditional {
    case /*condition : expr*/ => /*body : expr*/
    ...
    else  => /*body : expr*/
}
```

The conditional expression checks the conditions in sequence.
The conditional expression evaluates to body of first the truthy case. 

If no condition matches the behavior depends on the existence of the else branch.
If the else brach exists, its body is evaluated.
Otherwise the conditional expression evaluates to `null`.