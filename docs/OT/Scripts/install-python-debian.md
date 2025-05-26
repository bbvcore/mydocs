---
sidebar_position: 1
title: Install python
---

# Script python y librerías

<details>
<summary>
</summary>

```bash
#!/bin/bash
echo "Instalación de Python3 y librerías necesarias en Debian 11"
apt update
apt install python3 -y
apt install python3-pip -y

echo "Python3 y Pip correctamente instalados."

# Pymysql
pip3 install pymysql

# Pymodbus
pip3 install pymodbus==2.5.3


# Comprobación
python3 -c "import pymysql; print('OK');"
python3 -c "import pymodbus; print('OK');"
```
</details>
