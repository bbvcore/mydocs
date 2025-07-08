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
#### Librería libsnap7
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

**Comprobación de la librería**
```bash
file build/bin/i386_linux/libsnap7.so
```
**Resultado de la comprobación**
```bash
libsnap7.so: ELF 32-bit LSB shared object, Intel 80386, version 1 (SYSV), statically linked, BuildID[sha1]=06d7151d3f0a65664efc5ca072f022e694aeb5a4, not stripped
```
**Copiar librería**
```bash
cp libsnap7.so /usr/lib/
chmod 755 /usr/lib/libsnap7.so
ldconfig # Actualizar librerías
ldconfig -p | grep libsnap7
```

## Caso de uso S7
Se va a probar con un servidor y un cliente para testear correctamente snap7.

Al comprobar la librería se produce un error por la versión GCC de la compilación entonces se va a realizar estos pasos:
### En tu dispositivo IOT2000:
cd /usr/lib
mv libsnap7.so libsnap7.so.backup  # Hacer backup

### Descargar versión compatible con GLIBC 2.31
wget https://github.com/SCADACS/PLCinject/raw/master/snap7/release/Linux/i386/glibc_2.21/libsnap7.so


### Verificar compatibilidad
````bash
objdump -T libsnap7.so | grep GLIBC_

file libsnap7.so 
libsnap7.so: ELF 32-bit LSB shared object, Intel 80386, version 1 (SYSV), dynamically linked, BuildID[sha1]=de167e5ce2c0a447ae57d4747e49d3bcd100c763, not stripped
````
### Actualizar cache
```bash
# Copiar la librería libsnap7.so al yocto
ldconfig
```
:::warning[Necesario Python puro]
Ahora la librería es la correcta, con la versión de gcc correcta, pero contiene instrucciones que el Atom del IOT2040 no maneja y el mensaje del server es ilegal instruction, la librería que podía valer no se puede descargar por error 404 entonces la única forma de hacerlo funcionar es con python puro.
:::

### Servidor S7 funcionando con Python puro
```bash 
import socket
import struct
import time
import threading
import select
import sys
import signal
import datetime

class Snap7Server:
    def __init__(self, port=1102):
        self.port = port
        self.running = False
        self.db = {1: bytearray(128)}  # DB1 con 128 bytes
        self.mb = bytearray(1024)      # Memoria de marca
        self.eb = bytearray(1024)      # Entradas
        self.ab = bytearray(1024)      # Salidas
        self.last_activity = time.time()
        self.init_db_data()
        
    def init_db_data(self):
        """Inicializa DB1 con valores predeterminados"""
        # Valores iniciales para DB1
        struct.pack_into('>h', self.db[1], 0, 1234)    # DB1.DBW0
        struct.pack_into('>f', self.db[1], 4, 3.14159) # DB1.DBD4
        self.db[1][8] = self.db[1][8] | 0x01           # DB1.DBX8.0
        
        print("Valores iniciales configurados:")
        print(f"  DB1.DBW0: {struct.unpack('>h', self.db[1][0:2])[0]}")
        print(f"  DB1.DBD4: {struct.unpack('>f', self.db[1][4:8])[0]:.5f}")
        print(f"  DB1.DBX8.0: {bool(self.db[1][8] & 0x01)}")
        
    def handle_client(self, conn, addr):
        """Maneja las conexiones de clientes"""
        client_id = f"{addr[0]}:{addr[1]}"
        print(f"[{client_id}] Cliente conectado")
        
        try:
            while self.running:
                # Usar select para manejar múltiples clientes
                ready, _, _ = select.select([conn], [], [], 1.0)
                if not ready:
                    continue
                
                # Recibir cabecera (12 bytes)
                header = conn.recv(12)
                if len(header) < 12:
                    break
                    
                # Decodificar cabecera
                try:
                    function, area, db_number, data_type, start, amount = struct.unpack('>B B B B H H', header)
                except struct.error:
                    print(f"[{client_id}] Cabecera inválida")
                    break
                
                # Procesar solicitud
                if function == 4:  # Lectura
                    data = self.read_area(area, db_number, start, amount)
                    if data is not None:
                        conn.sendall(data)
                        self.last_activity = time.time()
                elif function == 5:  # Escritura
                    data = conn.recv(amount)
                    if len(data) == amount:
                        success = self.write_area(area, db_number, start, data)
                        conn.sendall(b'\x00' if success else b'\xFF')
                        self.last_activity = time.time()
                else:
                    print(f"[{client_id}] Función desconocida: {function}")
                    conn.sendall(b'\xFF')  # NACK
        except ConnectionResetError:
            print(f"[{client_id}] Conexión cerrada por el cliente")
        except Exception as e:
            print(f"[{client_id}] Error: {str(e)}")
        finally:
            conn.close()
            print(f"[{client_id}] Desconectado")

    def read_area(self, area, db_number, start, amount):
        """Lee datos de las áreas"""
        try:
            if area == 0x84:  # DB
                if db_number in self.db:
                    data = self.db[db_number]
                    end = min(start + amount, len(data))
                    return data[start:end]
            elif area == 0x83:  # MB
                end = min(start + amount, len(self.mb))
                return self.mb[start:end]
            elif area == 0x81:  # EB
                end = min(start + amount, len(self.eb))
                return self.eb[start:end]
            elif area == 0x82:  # AB
                end = min(start + amount, len(self.ab))
                return self.ab[start:end]
            return bytearray()
        except Exception:
            return None
            
    def write_area(self, area, db_number, start, data):
        """Escribe datos en las áreas"""
        try:
            if area == 0x84:  # DB
                if db_number in self.db:
                    db_data = self.db[db_number]
                    end = min(start + len(data), len(db_data))
                    db_data[start:end] = data[:end-start]
                    return True
            elif area == 0x83:  # MB
                end = min(start + len(data), len(self.mb))
                self.mb[start:end] = data[:end-start]
                return True
            elif area == 0x81:  # EB
                end = min(start + len(data), len(self.eb))
                self.eb[start:end] = data[:end-start]
                return True
            elif area == 0x82:  # AB
                end = min(start + len(data), len(self.ab))
                self.ab[start:end] = data[:end-start]
                return True
            return False
        except Exception:
            return False

    def start(self):
        """Inicia el servidor"""
        self.running = True
        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.server.bind(('0.0.0.0', self.port))
        self.server.listen(5)
        print(f"Servidor Snap7 en Python iniciado en puerto {self.port}")
        print(f"Fecha: {datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
        print("Áreas disponibles:")
        print(" - DB1 (128 bytes)")
        print(" - MB (1024 bytes)")
        print(" - EB (1024 bytes)")
        print(" - AB (1024 bytes)")
        print("Presiona Ctrl+C para detener...")
        
        try:
            while self.running:
                conn, addr = self.server.accept()
                conn.settimeout(5.0)
                thread = threading.Thread(target=self.handle_client, args=(conn, addr))
                thread.daemon = True
                thread.start()
        except OSError:
            pass  # Servidor detenido
        finally:
            self.server.close()

    def stop(self):
        """Detiene el servidor"""
        if self.running:
            print("Deteniendo servidor...")
            self.running = False
            # Desbloquear el accept()
            try:
                temp_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                temp_sock.connect(('127.0.0.1', self.port))
                temp_sock.close()
            except:
                pass
            print("Servidor detenido")

# Manejo de señales para Ctrl+C
def handle_sigint(signum, frame):
    print("\nSeñal SIGINT recibida, deteniendo servidor...")
    server.stop()
    sys.exit(0)

if __name__ == '__main__':
    server = Snap7Server(1102)
    signal.signal(signal.SIGINT, handle_sigint)
    
    try:
        server.start()
    except Exception as e:
        print(f"Error crítico: {str(e)}")
        server.stop()
        sys.exit(1)
```
Este **servidor puro** realizado en **Python** posee las siguientes características:
- Es **totalmente compatible** con Python al **100%** sin necesidad de dependencias externas.
- Incorpora soporte completo para áreas de memoria: **DB** *(bloque de datos)*,**MD** *(memoria de marca)*, **EB** *(entradas)* y **AB** *(salidas)*
- Compatible con clientes **Snap7**.

Además aporta una seri de ventajas sobre la librería desarrollada en **C++**:
- Elimina problemas de compatibilidad
- No tiene dependencias con bibliotecas externas
- Es más fácil de depurar al estar integramente en Python
- Menor consumo de recursos en sistemas embebidos como el caso del Yocto


## Cliente s7 puro
Este código se ejecuta en otro host diferente al Siemens IoT 2040 pero dentro de la misma LAN

```bash
import socket
import struct
import sys
import time

class Snap7Client:
    def __init__(self, ip='192.168.200.1', port=1102):
        self.ip = ip
        self.port = port
        self.sock = None
        self.connected = False
        
    def connect(self):
        """Conecta al servidor con manejo detallado de errores"""
        print(f"Conectando a {self.ip}:{self.port}...")
        try:
            self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.sock.settimeout(5.0)
            self.sock.connect((self.ip, self.port))
            self.connected = True
            print("¡Conexión TCP exitosa!")
            return True
        except ConnectionRefusedError:
            print("Error: Conexión rechazada. Verifica:")
            print("1. Que el servidor esté en ejecución")
            print("2. Que la IP y puerto sean correctos")
            return False
        except socket.timeout:
            print("Error: Tiempo de espera agotado. Verifica:")
            print("1. Que el dispositivo esté encendido")
            print("2. Que la IP sea correcta")
            print("3. Que no haya problemas de red")
            return False
        except Exception as e:
            print(f"Error de conexión: {str(e)}")
            return False
        
    def disconnect(self):
        """Desconecta del servidor"""
        if self.sock:
            self.sock.close()
            self.connected = False
            print("Desconectado")
        
    def read_db(self, db_number, start, size):
        """Lee datos de DB con depuración mejorada"""
        if not self.connected:
            print("Error: No conectado al servidor")
            return None
            
        try:
            # Cabecera: función, área, db_number, tipo, start, size
            header = struct.pack('>BBBBHH', 4, 0x84, db_number, 0, start, size)
            print(f"[DEBUG] Enviando cabecera: {header.hex()}")
            
            self.sock.sendall(header)
            
            # Recibir datos con timeout
            data = bytearray()
            start_time = time.time()
            
            while len(data) < size:
                remaining = size - len(data)
                try:
                    chunk = self.sock.recv(remaining)
                    if not chunk:
                        print("Error: Conexión cerrada por el servidor")
                        return None
                    data.extend(chunk)
                except socket.timeout:
                    if time.time() - start_time > 4.0:
                        print(f"Error: Tiempo de espera agotado. Recibidos {len(data)}/{size} bytes")
                        return None
            
            print(f"[DEBUG] Datos recibidos: {data.hex()}")
            print(f"[DEBUG] Tamaño recibido: {len(data)} bytes")
            return data
            
        except Exception as e:
            print(f"Error en lectura: {str(e)}")
            return None
        
    def write_db(self, db_number, start, data):
        """Escribe datos en DB con depuración mejorada"""
        if not self.connected:
            print("Error: No conectado al servidor")
            return False
            
        try:
            # Cabecera de escritura
            header = struct.pack('>BBBBHH', 5, 0x84, db_number, 0, start, len(data))
            print(f"[DEBUG] Enviando cabecera: {header.hex()}")
            print(f"[DEBUG] Enviando datos: {data.hex()}")
            
            self.sock.sendall(header + data)
            
            # Recibir respuesta
            response = self.sock.recv(1)
            print(f"[DEBUG] Respuesta del servidor: {response.hex() if response else 'None'}")
            
            if response == b'\x00':
                print("Escritura exitosa (confirmación recibida)")
                return True
            else:
                print(f"Error en escritura. Código de respuesta: {response.hex() if response else 'Ninguno'}")
                return False
                
        except Exception as e:
            print(f"Error en escritura: {str(e)}")
            return False


if __name__ == '__main__':
    # Configuración por defecto
    server_ip = "192.168.200.1"
    server_port = 1102
    
    # Manejar argumentos de línea de comandos
    if len(sys.argv) > 1:
        server_ip = sys.argv[1]
    if len(sys.argv) > 2:
        server_port = int(sys.argv[2])
    
    print(f"=== Cliente Snap7 Mejorado ===")
    print(f"Servidor: {server_ip}:{server_port}")
    print(f"Fecha: 2025-07-04")
    print(f"====================================\n")
    
    client = Snap7Client(server_ip, server_port)
    
    try:
        if not client.connect():
            print("\nSugerencias:")
            print("1. Verifica que el servidor esté ejecutándose")
            print("2. Comprueba la IP con 'ping 192.168.200.1'")
            print("3. Prueba con el comando: telnet 192.168.200.1 1102")
            sys.exit(1)
        
        # Primera lectura - DBW0 (2 bytes)
        print("\n[Prueba 1] Leyendo DB1.DBW0 (2 bytes)...")
        dbw0_data = client.read_db(1, 0, 2)
        
        if dbw0_data and len(dbw0_data) == 2:
            value = struct.unpack('>h', dbw0_data)[0]
            print(f"DB1.DBW0 = {value}")
        else:
            print("Error: No se pudo leer DBW0")
            print("Posibles causas:")
            print("a) DB1 no existe en el servidor")
            print("b) El offset 0 no es válido")
            print("c) Problema de protocolo")
        
        # Segunda lectura - DBD4 (4 bytes)
        print("\n[Prueba 2] Leyendo DB1.DBD4 (4 bytes)...")
        dbd4_data = client.read_db(1, 4, 4)
        
        if dbd4_data and len(dbd4_data) == 4:
            value = struct.unpack('>f', dbd4_data)[0]
            print(f"DB1.DBD4 = {value:.5f}")
        else:
            print("Error: No se pudo leer DBD4")
        
        # Escritura de prueba
        print("\n[Prueba 3] Escribiendo nuevo valor en DB1.DBW0...")
        new_value = struct.pack('>h', 5678)
        
        if client.write_db(1, 0, new_value):
            print("Escritura confirmada por servidor")
            
            # Verificación
            print("\n[Prueba 4] Verificando escritura...")
            dbw0_data = client.read_db(1, 0, 2)
            if dbw0_data and len(dbw0_data) == 2:
                new_dbw0 = struct.unpack('>h', dbw0_data)[0]
                print(f"Nuevo DB1.DBW0 = {new_dbw0}")
                if new_dbw0 == 5678:
                    print("¡Escritura verificada correctamente!")
                else:
                    print("Error: El valor no coincide")
            else:
                print("Error: No se pudo verificar la escritura")
        else:
            print("Error: La escritura no fue confirmada por el servidor")
            print("Posibles causas:")
            print("a) Permisos insuficientes en el servidor")
            print("b) Dirección inválida (DB o offset)")
            print("c) Error de protocolo")
        
    except KeyboardInterrupt:
        print("\nOperación cancelada por el usuario")
    except Exception as e:
        print(f"\nError inesperado: {str(e)}")
        import traceback
        traceback.print_exc()
    finally:
        client.disconnect()
```

:::warning[Para S7 solo Python puro]
Para usar el **protocolo S7** sobre el sistema Yocto en un **Siemens IoT2040** usar Python puro dado que las librerías de **C++** dan problemas por instrucciones que no puede procesar el microprocesador **Intel** del dispositivo. Además la alternativa, que era usar una librería ofrecida por el fabricante el enlace esta roto *(404)*
:::

Como seguía habiendo problemas se comprueba la librería desde el propio **Yocto** por si había algun problema y todo era aparentemente correcto.
```bash
root@iot2000:~# ldd /usr/lib/libsnap7.so
	linux-gate.so.1 (0xb76e1000)
	libpthread.so.0 => /lib/libpthread.so.0 (0xb7669000)
	librt.so.1 => /lib/librt.so.1 (0xb765f000)
	libstdc++.so.6 => /usr/lib/libstdc++.so.6 (0xb748b000)
	libgcc_s.so.1 => /lib/libgcc_s.so.1 (0xb746c000)
	libc.so.6 => /lib/libc.so.6 (0xb72c6000)
	/lib/ld-linux.so.2 (0xb76e2000)
	libm.so.6 => /lib/libm.so.6 (0xb71c7000)
```
El estado de la librería era perfecto, algo que se esperaba ya que fue descargada de https://sourceforge.net/projects/snap7/files/Snap7-IoT/snap7-iot-quark/ , siendo oficial para el dispositivo Siemens IoT 2040.


## Compatibilidad de la librería
### Análisis binario de la librería 
Pero como seguía dando problemas la ejecución y el error era de **instrucción ilegal** se procede a realizar un análisis binariode la misma, para ello se convierte a **asm** *(ensamblador)* mediante el comando **objdump**.
:::tip
- objdump permite inspeccionar el código de archivos binarios ejecutables
- d: desensamblar el código máquina a ensamblador (más legible)
:::
```bash
objdump -d /usr/lib/libsnap7.so > libsnap7.asm # se obtiene fichero libsnap7.asm
```
Entonces mediante el uso del comando grep se pueden buscar instrucciones incompatibles en el código con el microprocesador del Siemens Yocto.
```bash
grep -i -E '<instrucciones>' librería.asm
```

### Análisis hexadecimal de la librería 
También se utiliza la herramienta **hexdump** *(con parámetro -c)* para ver el código hexadecimal del binario en formato hexadecimal y con codificación ASCII
```bash
root@iot2000:~# hexdump -C /usr/lib/libsnap7.so | grep '66 0f'

0001c1f0  05 00 00 0f 8f 87 02 00  00 83 fa 66 0f 84 ae 05  |...........f....|
00025170  fe ff 66 0f af 46 10 66  89 44 24 1e 0f b6 47 01  |..f..F.f.D$...G.|
```

Consultando se observo que **66 0f** es un prefijo habitual para la ejecución de instrucciones de tipo **SSE/SSE2** que incluyen algunas como las siguientes: movupd, addpd, mulpd...

Este tipo de instrucciones no se pueden ejecutar en procesadores como el Quark X1000 dado que no existen en el micro y por consiguiente lanzan el mensaje recibido tras la ejecución del script de **Illegal instruction**.



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


## &#9201; Verificado
```bash 
root@iot2000:~# python3 -c "import opcua; print('ok')"
cryptography is not installed, use of crypto disabled
cryptography is not installed, use of crypto disabled
ok
root@iot2000:~# python3 -c "import snap7; print('ok')"
ok
```
## Caso de uso OPCUA
### Servidor OPCUA
```python
from opcua import Server
import time

try:
    print("[DEBUG] Creando servidor OPC UA...")
    server = Server()

    print("[DEBUG] Configurando endpoint a 0.0.0.0:4840...")
    server.set_endpoint("opc.tcp://0.0.0.0:4840/freeopcua/server/")

    print("[DEBUG] Agregando espacio de nombres...")
    uri = "http://examples.freeopcua.github.io"
    idx = server.register_namespace(uri)

    print("[DEBUG] Creando objetos...")
    objects = server.get_objects_node()

    print("[DEBUG] Agregando variable de prueba...")
    myvar = objects.add_variable(idx, "MyVariable", 6.7)
    myvar.set_writable()

    print("[DEBUG] Iniciando servidor...")
    server.start()
    print("[DEBUG] Servidor iniciado correctamente.")

    try:
        while True:
            time.sleep(1)
            # Puedes actualizar variable aquí si quieres
            # myvar.set_value(myvar.get_value() + 0.1)
    except KeyboardInterrupt:
        print("[DEBUG] Deteniendo servidor por interrupción de teclado...")

    print("[DEBUG] Parando servidor...")
    server.stop()
    print("[DEBUG] Servidor detenido.")

except Exception as e:
    print(f"[ERROR] Excepción en servidor OPC UA: {e}")


```

### Cliente OPCUA
```python
from opcua import Client

url = "opc.tcp://192.168.200.1:4840/freeopcua/server/"
client = Client(url)

try:
    print("Conectando cliente OPC UA...")
    client.connect()
    print("Cliente conectado correctamente.")

    root = client.get_root_node()
    print("Root node es:", root)

    objects = client.get_objects_node()
    print("Navegando objetos:")
    for child in objects.get_children():
        print("  ->", child, child.get_display_name().Text)

    print("Accediendo a variable MyVariable...")
    myvar = objects.get_child(["2:MyVariable"])  # Usa el namespace que aparece al hacer get_children
    val = myvar.get_value()
    print("Valor de MyVariable:", val)

except Exception as e:
    print(f"Error al conectar o leer: {e}")

finally:
    client.disconnect()
    print("Cliente desconectado")
```




## Anexo: problemas Siemens IoT20240
Los tiempos de ejecución de scripts son algo elevados, scripts que en un entorno actual se ejecutan en segundos pueden llevar 3 minutos en el Yocto del Siemenes IoT2040, como en el caso del despliegue del servidor OPCUA incluido en esta entrega.

Los motivos o causas de ese comportamiento se pueden clasificar acorde a las siguientes características:
- Hardware limitado (microprocesador)
- Python en sistemas embebidos va más lento.
- Implementación de asyncio o sockets puede consumir mucho hardware en entornos limitados.
- La librería OPCUA lleva a cabo unos procesos que son costosos en consumo de hardware.