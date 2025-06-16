---
title: Expresiones Shell
---

# Expresiones Shell
Las expresiones shell se pueden evaluar de 3 formas diferentes

## Utilizando expr
```bash
$(expr 5 + 3)	# Para realizar operaciones aritméticas, método lento
```
## Utilizando $()
```bash
$(comando)	# Para realizar la captura de la salida de un comando
```

## Utilizando (( ))
```bash
((resultado = 5 + 3)) # Para realizar operaciones aritméticas, método rápido
```


