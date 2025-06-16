1. update
sudo apt update && sudo apt upgrade -y
2. Clave GPG
curl -fsSL https://pgp.mongodb.com/server-6.0.asc | sudo gpg --dearmor -o /usr/share/keyrings/mongodb-server-6.0.gpg

3. Agregar repo
echo "deb [ arch=amd64,arm64 ] https://repo.mongodb.org/apt/debian $(lsb_release -cs)/mongodb-org/6.0 main" | sudo tee /etc/apt/sources.list.d/mongodb-org-6.0.list
4. Actualizar
sudo apt update
5. Instalar
sudo apt install -y mongodb-org
6. Iniciar el servicio
sudo systemctl start mongod
sudo systemctl enable mongod
7. Verificar instalación
sudo systemctl status mongod
mongosh (mongo en versiones anteriores a 5, actuales mongosh)


8. Habilitar mongo 
sudo systemctl enable mongod


Problemas:
1. Si falla mongosh
sudo apt install mongodb-mongosh

2. falta librería libssl1.1.
wget http://ftp.debian.org/debian/pool/main/o/openssl/libssl1.1_1.1.1n-0+deb10u3_amd64.deb
2.1 Instalar la librería descargada:
sudo dpkg -i libssl1.1_1.1.1n-0+deb10u3_amd64.deb
sudo apt --fix-broken install

