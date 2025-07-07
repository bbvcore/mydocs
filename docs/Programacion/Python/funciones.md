---
title: Funciones en python
---
# Funciones en Python

## Con return
```python
def saludar(nombre):
	saludo = "Hola..."
	return saludo+nombre
# print(saludar("Borja"))
```

## Con print
```python
def saludar2(nombre):
	print("Hola...", nombre)
# saludar2("Borja")
```

## Lambda (tipo arrow)
```python
suma = lambda a,b: a+b
print (suma(3,4))
```

## Con número argumentos indefinido (**) 
:::tip
- Con 2 asteriscos es un diccionario
- Con 1 asterisco es una tupla
:::
```python
def datos(**args):
	for key, value in args.items():
		print(f"{key}:{value}")

datos(nombre="Máquina", edad=25, Casado= False)
```
