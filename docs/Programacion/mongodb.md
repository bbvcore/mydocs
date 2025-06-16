---
sidebar_position: 1
title: MongoDB
---

# MongoDB
## Instalación
### Actualizar sistema operativo
```bash
sudo apt update && sudo apt upgrade -y
```

### Clave GPG
```bash
curl -fsSL https://pgp.mongodb.com/server-6.0.asc | sudo gpg --dearmor -o /usr/share/keyrings/mongodb-server-6.0.gpg
```

### Agregar repositorio
```bash
echo "deb [ arch=amd64,arm64 ] https://repo.mongodb.org/apt/debian $(lsb_release -cs)/mongodb-org/6.0 main" | sudo tee /etc/apt/sources.list.d/mongodb-org-6.0.list
```

### Actualizar con el repositorio nuevo agregado
```bash
sudo apt update
```
### Instalación
```bash
sudo apt install -y mongodb-org
```
### Iniciar el servicio
```bash
sudo systemctl start mongod
sudo systemctl enable mongod
```
### Verificar instalación
```bash
sudo systemctl status mongod
mongosh (mongo en versiones anteriores a la 5)
```

### Habilitar mongo 
```bash
sudo systemctl enable mongod
```


## Soluciones posibles problemas
### Si falla mongosh
```bash
sudo apt install mongodb-mongosh
```

### Falta librería libssl1.1.
```bash
wget http://ftp.debian.org/debian/pool/main/o/openssl/libssl1.1_1.1.1n-0+deb10u3_amd64.deb
sudo dpkg -i libssl1.1_1.1.1n-0+deb10u3_amd64.deb
sudo apt --fix-broken install
```

