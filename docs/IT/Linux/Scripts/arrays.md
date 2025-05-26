---
sidebar_position: 1
title: Arrays
---

# Arrays
El manejo de arrays en Shell Script tiene sus peculiaridades con respecto al manejo de los mismos en la mayoría de lenguajes de programación


```bash
#!/bin/bash
discos[metallica]="Master Of Puppets"
discos[korn]="KoRn"
echo ${discos[metallica]}

for i in "${!discos[@]}"; do
    echo "$i => ${discos[$i]}"
done
for i in "${discos[@]}"; do
    echo "$i"
done
```

```bash
#!/bin/bash
declare -a numbers=(0 1 2 3 4 5)
echo "${numbers[@]}" #Length
echo "${numbers[2]}"
echo "${#numbers[@]}"
```