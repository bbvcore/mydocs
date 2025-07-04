---
title: Replica del entorno Siemens IoT2040
---

# Replica del entorno Siemens IoT 2040

Para poder trabajar dentro de **GNU/Linux** sin tener que estar instalado al **Yocto**  se va a crear un entorno virtual para disponer de la misma versión de Python y de las mismas liberías.

:::tip[Características del entorno]
Entre las caracterísiticas del entorno a replicar figuran las siguientes:
- Entorno Python 3.8.
- Librería Opcua  0.98.12
- Libreria Python-Snap7 1.0
:::


## Preparar el entorno virtual
### Opción repositorios de la distribución
```bash
sudo add-apt-repository ppa:deadsnakes/ppa
sudo apt update
sudo apt install python3.8 python3.8-dev python3.8-venv
python3.8 --version
```

### Opción instalación desde el código fuente
#### Descarga del código fuente
```bash
wget https://www.python.org/ftp/python/3.8.18/Python-3.8.18.tgz
```
#### Compilación
Previo a la compilación
```bash
sudo apt update
sudo apt install  libffi-dev build-essential libssl-dev zlib1g-dev libbz2-dev libreadline-dev libsqlite3-dev wget curl llvm libncursesw5-dev xz-utils tk-dev libxml2-dev libxmlsec1-dev  liblzma-dev
```

```bash
./configure --enable-optimizations # Preparación de las dependencias con optimización para los makefiles
make -j $(nproc) # Make inicia la compilación de los makefiles, jobs número de procesos paralelos a usar en la compilación y nproc devuelve el valor de núcleos disponibles
sudo make altinstall # Install instala pudiendo sobrescribir, altinstall sin sobrescribir ficheros críticos.

```

## Creación del entorno virtual

```bash
python3.8 -m venv ./iot2040-dev
source sourc/iot2040-dev/bin/activate
```
### Ejemplo para Versión de librería 1.3
<details>
<summary>
Versión snap7 1.3
</summary>

### Comprobaciones de versiones
Dentro de la terminal ejecutar
```bash
python3.8 --version # comprobar que es la versión correcta de 3.8.x
```
Una vez activado el entorno virtual ejecutar
```bash
python --version # debe de devolver la versión 3.8.x
```
### Instalación librerías
```bash
python -m ensurepip --upgrade # actualizar pip
pip install --upgrade pip setuptools wheel # herramientas para las librerías
pip install python-snap7 # instalación de la librería
```
Y se comprueba que este todo correctamente instalado

```bash
pip install python-snap7
Requirement already satisfied: python-snap7 in /*****/*****/*****/lib/python3.8/site-packages (1.3)
```
#### Versión específica
Si se quiere una versión específica se puede usar el siguiente método
```bash
pip install python-snap7==1.3
```
## Librería libsnap7.so
### Configuración de variables
```bash
export CFLAGS="-m32 -march=i586 -mtune=atom"
export CXXFLAGS="-m32 -march=i586 -mtune=atom"
export LDFLAGS="-m32"
```

### Limpieza y compilación
```bash
make -f i386_linux.mk clean
make -f i386_linux.mk
```

### Preparación de paquete para transferir
```bash
mkdir -p snap7-iot2000/lib
cp ../bin/i386_linux/libsnap7.so snap7-iot2000/lib/
tar czvf snap7-iot2000.tar.gz snap7-iot2000
```

## Caso de uso de librería Siemens 7 (v-1.3)
Debido a la librería usada de S7 se han de tener en cuenta ciertas peculiaridades:
- Por temas de permisos en el OS se ha usado 1102 en vez de 102 como alternativa en desarrollo(otra opción es usar sudo).
- Usar solo el área DB que es la más estable en esta versión. 

### Código servidor
```python
import snap7
import ctypes
import time
import struct
import sys

def run_server():
    print("Iniciando servidor Snap7 1.3 en puerto 1102...")
    
    # Crear instancia del servidor
    server = snap7.server.Server()
    
    # Tamaño del área de datos
    db_size = 128
    
    # Configurar área DB (única área que funciona consistentemente en 1.3)
    db_data = (ctypes.c_uint8 * db_size)()
    
    try:
        # Registrar área DB - método compatible con 1.3
        server.register_area(snap7.server.srvAreaDB, 1, db_data)
        
        # Valores iniciales
        print("Configurando valores iniciales en DB1...")
        struct.pack_into('>h', db_data, 0, 1234)    # Entero en DB1.DBW0
        struct.pack_into('>f', db_data, 4, 3.14159) # Real en DB1.DBD4
        db_data[8] = db_data[8] | 0x01              # Bool en DB1.DBX8.0
        
        # Usar puerto 1102 (no privilegiado) en lugar de 102
        port = 1102
        print(f"Iniciando servidor en puerto {port}...")
        server.start(tcpport=port)
        
        print(f"Servidor Snap7 funcionando en localhost:{port}")
        print("Presiona Ctrl+C para detener...")
        
        while True:
            time.sleep(1)
            
    except Exception as e:
        print(f"Error: {str(e)}", file=sys.stderr)
    finally:
        server.stop()
        print("Servidor detenido")

if __name__ == '__main__':
    run_server()
```

### Código cliente
```python
import snap7
from snap7 import util

def run_client():
    print("Iniciando cliente Snap7...")
    
    client = snap7.client.Client()
    server_ip = '127.0.0.1'
    port = 1102  # Mismo puerto que el servidor
    
    try:
        print(f"Conectando a {server_ip}:{port}...")
        client.connect(server_ip, 0, 1, port)
        print("Conexión exitosa!")
        
        print("\nLeyendo DB1...")
        db1 = client.db_get(1)
        
        # Mostrar valores
        print(f"DB1.DBW0 (entero): {util.get_int(db1, 0)}")
        print(f"DB1.DBD4 (real): {util.get_real(db1, 4):.5f}")
        print(f"DB1.DBX8.0 (bool): {util.get_bool(db1, 8, 0)}")
        
        # Escribir y verificar nuevo valor
        print("\nEscribiendo 5678 en DB1.DBW10...")
        util.set_int(db1, 10, 5678)
        client.db_write(1, 0, db1)
        
        print("Valor actualizado:", util.get_int(client.db_get(1), 10))
        
    except Exception as e:
        print(f"Error: {e}")
    finally:
        client.disconnect()
        print("\nDesconectado")

if __name__ == '__main__':
    run_client()
```
</details>









