---
title: Liberías en Siemens IoT2040
sidebar_position: 1
---

# S7 comm y OPCua en Siemens IoT 2040
Lo primero de todo, es que es necesario tener **Python** instalado en el equipo, en este caso se comprueba su disponibilidad una vez se accede por **SSH** al dispositivo de Siemens.

```bash
python3 --version
```
Se comrpueba positivamente que Python viene instalado de serie en la imagen y es la versión **3.18.13**, no viene instalado **pip/pip3** y sumado a que la versión de Yocto generada para el despliegue no dispone de gestor de dependencias toca descargar en otro equipo las librerías necesarias.

## Descarga de librerías necesarias
En este caso toca recurrir a la búsqueda de las mismas en el dominio siguiente.

```bash
https://pypi.org
```
A continuación se va a buscar las librerías *.whl precompiladas para la arquitectura requerida según el hardware del dispositivo.

Las librerías descargadas se obtienen como un tarball y son necesarias para ser compatibles con Python 3.8.13 y no tener problemas las siguientes versiones:
- python-snap7 1.0
- opcua 0.98.12

Una vez descargadas hace falta compilarlas acorde a la arquitectura del Siemenes IoT 2040, para ello hace falta preparar el host donde se van a compilar de la siguiente manera.

```bash
sudo apt update
sudo apt install -y build-essential python3-dev python3-pip python3-wheel libssl-dev
```

## Compilación para i386/i586
### Generación de un .whl compatible
#### Snap7
Se específica la arquitectura accediendo al directorio descomprimido y ejecutando, dentro de python-snap7-1.0.

:::tip[Cross-compilation]
```bash
CFLAGS="-march=i586" python3 setup.py bdist_wheel --plat-name=linux_i586
```
:::

Se obtiene en /dist un fichero whl para exportar al siemens IoT.

#### OPCua
En este caso se genera directamente una vez se está dentro del directorio descomprimido con el comando.
```bash
pithon3 setup.py bdist_wheel
```
Y dentro del directorio /dist se genera la libería whl.


### Copia de las librerías descargadas
```bash
scp *.whl root@192.168.200.1:/home/root
```

### Instalar las librerías descargadas
#### Python3-snap7
Instalación de la librería para S7.
```bash
python3 -m pip install --user --no-index --find-links=/home/root python3_snap7-1.0-pyp3-none-linux_i586.whl
```

#### OPCUA
Para opcua hacen falta dependencias como pytz o python-dateutil, que se han de descargar de la siguiente forma y luego pasarlas por ssh con scp al dispositivo IoT de Siemens.
```bash
pip download pytz --platform manylinux1_i586 --python-version 38 --only-binary=:all:
scp pytz-*.whl root@192.168.200.1:/home/root
pip download python-dateutil --platform any --python-version 38 --no-deps
scp python_dateutil*.whl root@192.168.200.1:/home/root
```
Como son varias lo mejor es buscar todas las dependencias que necesita la librería, para ello se ejecuta el siguiente comando.
```bash
unzip -p opcua-0.98.12-py3-none-any.whl opcua-0.98.12.dist-info/METADATA | grep Requires-Dist
```
Y se obtiene el listado de las dependencias necesarias.
```bash
lxml >=3.0
python-dateutil >= 2.1
pytz >= 2011k
cryptography; extra == 'encryption' >=1.3
```
A continuación se van a compilar las librerías de lxml y de cryptography, para ello hay que actualizar e instalar los siguientes paquetes
```bash
sudo apt update
sudo apt install -y python3-dev libxml2-dev libxslt-dev libssl-dev
sudo apt install -y libxslt1-dev gcc-multilib  
```
Las descargas de las librerias y su posterior compilación, una vez se descargaron, se descomprimieron y se accedieron a sus correspondientes directorios descomprimidos.
```bash
pip download lxml --no-binary=lxml
CFLAGS="-march=i586 -mtune=generic" python3 setup.py bdist_wheel --plat-name=linux_i586
```
Como da varios problemas, al final toca llevar a cabo una cross-compilation total mediante el uso de docker.

:::warning[Acceso al cross-compilation]
<a href="cross-compilation.md">Guía de cross-compilation en Docker</a>
:::



#### Comando de instalación
```bash
```

## Verificación de la instalación
```bash
python3 -c "import snap7; import opcua; print('El estado de las librerías en el sistema es el correcto')"
```
