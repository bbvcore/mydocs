---
title: Cross Compilation
sidebar_id: 1
---
# &#9881; Cross compilation
Es muy importante tener en cuenta el **OS** que se va a usar, con Ubuntu sufrí más problemas que con **Mint Debian**, esto es debido a que **Ubuntu** incorpora más **flags de compilación modernos** *(como -fcf-protection)* que genera más incompatibilidades con i586, por ello recomiendo usar una distribución **Debian/RHEL**.

:::tips
Para arquitecturas antiguas es importante aplicar los siguientes criterios:
- Usar **--no-binary** para paquetes con extensiones C
- Simplificar los flags en las arquitecturas antiguas *(-m32 -march=i586 -Os)*
:::


## &#8618;Situación previa
:::warning
La situación previa se puede consultar en esta <a href="s7comm.md">entrada</a>.
:::

Previamente se habían descargado dependencias puras que no necesitaban compilación
```bash
pip download --only-binary=:all: --platform manylinux1_i586 --python-version 38 python-dateutil==2.8.2 pytz==2023.3 six==1.16.0
```
También se descargó la librería **OPCUA**
```bash
pip download opcua==0.98.12 --platform any
```
Partiendo de esa situación, se van a obtener las librerías que necesitan compilación, para ello hay que preparar el sistema operativo.

```bash
sudo apt update && sudo apt install -y \
    python3-dev \
    libxml2-dev \
    libxslt1-dev \
    zlib1g-dev \
    libssl-dev
```
## &#128193; Librerías para cross-compilar
### &#8594; Librería lxml
#### Descarga
```bash
pip download --no-binary lxml lxml==4.9.3`
```
#### Configuración de flags
```bash
CFLAGS="-m32 -march=pentium -mtune=generic -Os -fno-stack-protector" \
```
#### Compilación
```bash
python3 setup.py bdist_wheel --plat-name=linux_i586
```
#### Fichero generado
Accesible desde **/dist** con la extensión *.whl, entonces se procede a copiarlo para el sistema destino.

### &#8594; Librería cryptography
```bash
pip download --no-binary cryptography cryptography==3.4.8 
```
#### Configuración de flags
```bash
export CFLAGS="-m32 -march=i586 -fno-stack-protector"
export LDFLAGS="-m32"
export CARGO_TARGET_I586_UNKNOWN_LINUX_GNU_LINKER="i686-linux-gnu-gcc"
```
```bash
python3 setup.py bdist_wheel --plat-name=linux_i586
```
:::warning
Puede fallar debido a la falta de **RUST**
:::

<details>
<summary>
Solución error con <b>RUST</b>
</summary>

Como el entorno de ejecución recomienda el uso de un entorno virtual se va a proceder a realizarlo de esa forma.

python3 -m venv /tmp/crypto_build
source /tmp/crypto_build/bin/activate
pip wheel cryptography --no-binary cryptography -w ./wheels


</details>


## &#128736; Instalación de todas las librerías
```bash
python3 -m pip install --user --no-index --find-links=/home/root/ six-*.whl python_dateutil-*.whl  pytz-*.whl lxml-*.whl cryptography-*.whl opcua-0.98.12-py3-none-any.whl
```

## &#128206;Anexo
Tuve un problema con la librería lxml debido a que no era adecuada para la **versión python 3.8** que es la que usa el **Yocto en el Siemens IoT**, entonces procedo a conseguir de nuevo esa librería adecuada esta vez para el dispositivo OT.

### &#10004; Opción 1: Intentar encontrar directamente la librería
```bash
pip download lxml==4.9.3 --platform manylinux1_i586 --python-version 38 --only-binary=:all:
```
### &#10004; Opción 2: Compilar la librería
Hay varias opciones, como me daba problemas con la versión de python, voy a probar una solución limpia que es usar docker.
```bash
sudo apt install docker.io
docker run --platform linux/386 -it --rm \
  -v "$PWD":/build \
  python:3.8-bookworm \
  bash -c "apt update && apt install -y libxml2-dev libxslt1-dev && \
  pip wheel lxml==4.9.3 --no-binary lxml -w /build && \
  auditwheel repair /build/lxml-*.whl --plat linux_i586 -w /build"
```
:::tip
-v "$PWD":/build: Vincula directorio actual a /build en el contenedor.
-rm: Elimina el contenedor al terminar (pero no los ficheros).
:::ls

#### &#9989; Copiar la librería
```bash
scp *.whl root@192.168.200.1:/home/root
```


