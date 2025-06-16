--- 
sidebar_position: 1
title: Virtual Box
---

# Instalar Virtual Box
## Procedimiento
### Instalación de dependencias
```bash
sudo apt install -y dkms build-essential linux-headers-$(uname -r)
```

### Descarga de la clave pública
```bash
wget -q https://www.virtualbox.org/download/oracle_vbox.asc -O /tmp/oracle_vbox.asc
sudo cp /tmp/oracle_vbox.asc /etc/apt/trusted.gpg.d/
```

### Agregar repositorio
```bash
echo "deb http://download.virtualbox.org/virtualbox/debian $(lsb_release -c | awk '{print $2}') contrib" | sudo tee -a /etc/apt/sources.list
```

### Actualizar e instalar
```bash
sudo apt update
sudo apt install virtualbox-6.1
```

