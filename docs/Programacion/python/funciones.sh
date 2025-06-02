# 1. Con return
def saludar(nombre):
	saludo = "Hola..."
	return saludo+nombre
# print(saludar("Borja"))

# 2. Con print
def saludar2(nombre):
	print("Hola...", nombre)
# saludar2("Borja")

# 3. Lambda (tipo arrow)
suma = lambda a,b: a+b
print (suma(3,4))

# 4. Con número argumentos indefinido (**) empaquetados y con nombre, diccionario
# Con 2 asteriscos es un diccionario
# Con 1 asterisco es una tupla
def datos(**args):
	for key, value in args.items():
		print(f"{key}:{value}")

datos(nombre="Máquina", edad=25, Casado= False)

