# Iterar Listas (Array) o Tuplas
array = [0,1,2,3,4,5,6]
for i in array:
	print(i)

# Iterar Objetos
bandas = {
	"Metallica":"Master of puppets",
	"Korn":"Korn",
	"Faith No More":"Album Of The Year",
	"Refused":"The Shape of punk to come"
}
for i in bandas:
	print( i , ' => ', bandas[i])

# Iterar con enumerate
for key, value in enumerate(bandas):
	print(f"Key:{key}, Value:{value}")


# Iterar con range
for i in range(10):
	print(i)

print("Range de 3 en 3")
for i in range(0,12,3):
	print(i)
