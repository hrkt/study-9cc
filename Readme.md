
```
expr:   number
expr:   number "+" expr
expr:   number "-" expr
number: digit | digit number
digit:  "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
```

```
expr: mul
expr: mul "+" expr
expr: mul "-" expr
mul:  term
mul:  term "*" mul
mul:  term "/" mul
term: number
term: "(" expr ")"
```

add: number add'
add': "+" number add' | "-" number add' | ε

