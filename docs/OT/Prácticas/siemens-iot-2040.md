---
title: Liberías en Siemens IoT2040
sidebar_position: 1
---

# &#128214; S7 comm y OPCua en Siemens IoT 2040
Lo primero de todo, es que es necesario tener **Python** instalado en el equipo, en este caso se comprueba su disponibilidad una vez se accede por **SSH** al dispositivo de Siemens.

```bash
python3 --version
```
Se comrpueba positivamente que Python viene instalado de serie en la imagen y es la versión **3.18.13**, no viene instalado **pip/pip3** y sumado a que la versión de Yocto generada para el despliegue no dispone de gestor de dependencias toca descargar en otro equipo las librerías necesarias.

## &#128206; Descarga de librerías necesarias
En este caso toca recurrir a la búsqueda de las mismas en el dominio siguiente.

```bash
https://pypi.org
```
A continuación se va a buscar las librerías *.whl precompiladas para la arquitectura requerida según el hardware del dispositivo.

Las librerías descargadas se obtienen como un tarball y son necesarias para ser compatibles con Python 3.8.13 y no tener problemas las siguientes versiones:
- python-snap7 1.3
- opcua 0.98.12

Una vez descargadas hace falta compilarlas acorde a la arquitectura del Siemenes IoT 2040, para ello hace falta preparar el host donde se van a compilar de la siguiente manera.

```bash
sudo apt update
sudo apt install -y build-essential python3-dev python3-pip python3-wheel libssl-dev
```

## &#128194; Compilación para i386/i586
### &#9881; Generación de un .whl compatible
#### &#8594; Snap7
Se específica la arquitectura accediendo al directorio descomprimido y ejecutando, dentro de python-snap7-1.0.

:::tip[Cross-compilation]
```bash
CFLAGS="-march=i586" python3 setup.py bdist_wheel --plat-name=linux_i586
```
:::

Se obtiene en **/dist** un fichero whl para exportar al siemens IoT.

#### &#8594; OPCua
En este caso se genera directamente una vez se está dentro del directorio descomprimido con el comando.
```bash
pithon3 setup.py bdist_wheel
```
Y dentro del directorio /dist se genera la libería whl.


### &#128195; Copia de las librerías descargadas
```bash
scp *.whl root@192.168.200.1:/home/root
```

### &#128202; Instalar las librerías descargadas
#### &#9654; Python3-snap7 (v. 1.3)
Instalación de la librería para S7.
```bash
python3 -m pip install --user --no-index --find-links=/home/root python3_snap7-1.3-pyp3-none-linux_i586.whl
```
#### Librería lib
cd ~/cross-compilation/libsnap/snap7-full-1.4.2/

Compilación
```bash
g++ -m32 -march=i586 -shared -fPIC \
-Irelease/Wrappers/c-cpp \
-Isrc/sys \
-Isrc/core \
-Isrc/lib \
-Isrc \
src/sys/snap_msgsock.cpp \
src/sys/snap_threads.cpp \
src/sys/snap_tcpsrvr.cpp \
src/sys/snap_sysutils.cpp \
src/core/s7_peer.cpp \
src/core/s7_server.cpp \
src/core/s7_text.cpp \
src/core/s7_client.cpp \
src/core/s7_partner.cpp \
src/core/s7_micro_client.cpp \
src/core/s7_isotcp.cpp \
src/lib/snap7_libmain.cpp \
-o build/bin/i386_linux/libsnap7.so
```
:::tip
-Isrc/sys: Agrega la ruta de ficheros de sistema
-Isrc/core: Agrega la ruta de ficheros del nucleo
-Isrc/lib: Agrega de los ficheros de librería
-Isrc: Ruta base como respaldo adicional
:::

Comprobación
```bash
file build/bin/i386_linux/libsnap7.so
```


#### &#9654; OPCUA
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
Como la gestión de las dependencias y de las librerías se va volviendo complicada, creo una entrada independiente para este cometido.

:::warning[Acceso al cross-compilation]
<a href="cross-compilation.md">Guía de cross-compilation</a>
:::



#### &#128229; Comando de instalación
Antes de instalar comprobar tener estas librerías en /home/root
```bash
- six-1.16.0-py2.py3-none-any.whl
- python_dateutil-2.8.2-py2.py3-none-any.whl
- pytz-2023.3-py2.py3-none-any.whl
- lxml-4.9.3-cp38-cp38-linux_i586.whl  
- cryptography-3.4.8-cp38-cp38-linux_i586.whl
- opcua-0.98.12-py3-none-any.whl
```

## &#128269; Comprobaciones
### &#9989; Verificación
```bash
python3 -c "import snap7; import opcua; print('El estado de las librerías en el sistema es el correcto')"
```

```bash
oot@iot2000:~# rm cryptography-45.0.4-cp311-abi3-manylinux_2_34_x86_64.whl 
root@iot2000:~# python3 -m pip install --user --no-index --find-links=/home/root/ six-*.whl python_dateutil-*.whl  pytz-*.whl   opcua-0.98.12-py3-none-any.whl
Looking in links: /home/root/
Processing ./six-1.16.0-py2.py3-none-any.whl
Processing ./python_dateutil-2.8.2-py2.py3-none-any.whl
Processing ./pytz-2023.3-py2.py3-none-any.whl
Processing ./opcua-0.98.12-py3-none-any.whl
Requirement already satisfied: lxml in /usr/lib/python3.8/site-packages (from opcua==0.98.12) (4.5.0)
Installing collected packages: six, python-dateutil, pytz, opcua
  WARNING: The scripts uabrowse, uacall, uaclient, uadiscover, uahistoryread, uals, uaread, uaserver, uasubscribe and uawrite are installed in '/home/root/.local/bin' which is not on PATH.
  Consider adding this directory to PATH or, if you prefer to suppress this warning, use --no-warn-script-location.
Successfully installed opcua-0.98.12 python-dateutil-2.8.2 pytz-2023.3 six-1.16.0
```

### :warning:  Solucionar el Warning
```bash
echo 'export PATH=$PATH:/home/root/.local/bin' >> /home/root/.profile
```




## &#9201; Comprobaciones
```bash 
root@iot2000:~# python3 -c "import opcua; print('ok')"
cryptography is not installed, use of crypto disabled
cryptography is not installed, use of crypto disabled
ok
root@iot2000:~# python3 -c "import snap7; print('ok')"
ok
```

