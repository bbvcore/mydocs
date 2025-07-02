---
title: Replica del entorno Siemens IoT2040
---

# Replica del entorno Siemens IoT 2040

Para poder trabajar dentro de GNU/Linux sin tener que estar instalado al Yocto  se va a crear un entorno virtual para disponer de la misma versión de Python y de las mismas liberías.

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

### Actualizar entorno virtual
```bash
pip install --upgrade "pip<24.0"  # Compatible con Python 3.8
```
### Instalar setuptools y wheel
```bash
pip install setuptools wheel
```

## Instalar librerías
```bash
pip install python-snap7==1.0 opcua==0.98.12
```