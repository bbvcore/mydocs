---
title: Clases con Pyhton
---

# Clases con Python

```python
# Start Person Class
class person:
	# Propiedades
	nation = "Spain"

	# Constructor
	def __init__(self, name, edad):
		self.name = name
		self.edad = edad

	def data(self):
		print(f"Nombre: {self.name}, Edad: {self.edad} y nacionalidad: {self.nation}")

	def __str__(self):
		# Con este método, al imprimir la instancia de la clase sin métodos
		# o sin propiedades así no devuelve la dirección memoria del objeto
		# sino que devuelve lo que le indico
		return "Estas retornando una instancia de la clase"

# Se puede imprimir datos técnicos y condicionarlo con el método __str__ mágico
# estilo a .toString() en otros lenguajes, como PHP

# End Class
	
p1 = person("Borja", 43)
p2 = person("Bas",25)

print(p1) # Ejemplo para ver como el método __str__ hace su trabajo
p2.data()
```