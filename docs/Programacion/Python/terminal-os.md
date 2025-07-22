---
title: Módulo OS
---
# Módulo OS
Uso del módulo **OS** diseñado para la interacción entre el sistema operativo y Python.

## 0.- Librería para interactuar con el OS
```python
import os
``` 

## 1.- Función para listar el contenido del raíz
```python
################################################################
def checkDir():
	contenido = os.listdir("/") # Método listdir()
	print(contenido)
	
# checkDir()
```

# 2.- Función para comprobar si existe directorio
```python
################################################################
def checkFile():
	path = "os.py"
	if os.path.exists(path): # Método path.exists
		print("Existe el fichero buscado")
	else:
		print("No existe el fichero buscado")
		
# checkFile()
```

# 3.- Crear un directorio
```python
################################################################
def createDir():
	path = "new/new_subdir"
	os.makedirs(path, exist_ok=True) # Método makedirs
	print("Carpeta creada")
	
#createDir()
```

# 4.- Rename
```python
################################################################
def renameDir():
	currentDir = "new"
	newDir = "renombrado"
	os.rename(currentDir, newDir) # Método rename
	print(f"{currentDir} renombrado a {newDir}")

#renameDir()	
```

# 5.- Ejecutar comandos del OS
```python
################################################################
# Con OS
def commandOS():
	command01 = os.system("ls -l") # Método System
	print(f"Salida {command01}")

## commandOS()
# Con la librería subprocess
import subprocess
def subprocessMod():
	rs = subprocess.run(["ls","-l"], capture_output=True, text=True) # Método run o call, hacen lo mismo
	print(rs.stdout)
	print(rs.stderr)

# subprocessMod()
```

# 6.- Variables de entorno
```python
################################################################
# Todas las variables
def variables():
	for key, value in os.environ.items():
		print('clave: ',key,'value:', value)
		# Una específica
		home = os.environ.get("HOME")
		print(home)
# variables()
```

# 7.- Existencia fichero/directorio
```python
################################################################
def checkFileOrDir():
	path = '/home'
	if os.path.isfile(path):
		print("Es un fichero")
	elif os.path.isdir(path):
		print("Es un directorio")
	else:
		print("No es ni una cosa, ni la otra, que será, será")

# checkFileOrDir()
```

# 8.- Borrar ficheros y directorios
```python
import shutil # Una ampliación del módulo OS : copy, copytree, move, rmtree, make_archive, disk_usage
def delFileOrDir():
	path = "bas"
	# Comprobar si es fichero y en tal caso borrar
	if (os.path.isfile(path)):
		os.remove(path) # Método remove de librería os
		print("Fichero borrado: ", path)
	#elif (os.path.isdir(path)):
	#	os.rmdir(path) # Método rmdir de librería os
	#	print("Directorio vacio borrado: ", path)
	elif (os.path.isdir(path)):
		shutil.rmtree(path) # Método rmtree de librería shutil
		print("Contenido eliminado")
		
	else:
		print("Nada que borrar")		

# delFileOrDir()
```

# 9. Usos de Shutil
```python
import shutil
def copyMoveZip():
	shutil.copy("original.txt", "copia.txt")
	shutil.move("copia.txt", "backup/copia.txt")
	shutil.make_archive("backup", "zip", "backup")
	
copyMoveZip()
```	
	













	
