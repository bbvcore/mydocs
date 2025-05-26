---
sidebar_position: 2
title: Open VPN
---

# Open VPN

## Instalación
```bash
sudo apt install openvpn easy-rsa -y
```

## Infraestructua PKI
La infraestructura PKI es la infraestructura de clave pública.


### Ejecución VARS (método viejo)
Creación de la estructura base
```bash
make-cadir ~/openvpn-ca
cd ~/openvpn-ca
```
:::tip[make-cadir]
Se trata de un comando que sirve para genear una entidad CA local gracias a este comando perteneciente a Easy-RSA.
:::

Una vez creado este directorio se dispone en su interior de los siguientes ficheros:
- Scripts de Easy-RSA
- Entorno listo para claves y certificados
En las versiones anteriores, eran necesaria la ejecución del script **vars**, ejecutado con source para que su ejecución sea en la shell y su entorno actual, que es donde actua **source**
```bash
sudo source vars
```
A continuación se ejecutaban otros 2 scripts, estos con ./ dado que así se procede a crear procesos hijos de la shell actual. Esto se hacía así para la shell con source carga variables de entorno que los procesos hijos de los 2 siguientes scripts utilizan.
```
./clean-all
./build-ca
```
### Ejecución actual (Easy-RSA 3)
#### Creación estructura base
Para la ejecución del método actual, la versión 3 de Easy-RSA, se crea la siguiente estructura, mediante la creación del directorio easy-rsa en el home del usuario y copiando los ficheros del directorio /usr/share necesarios para utilizar e inicializar la PKI con Easy-RSA 3.
```
mkdir ~/easy-rsa
cp -r /usr/share/easy-rsa/* ~/easy-rsa/
cd #/easy-rsa
```
#### Despliegue PKI
Una vez creada la estructura, se accede al directorio /easy-rsa/ y se ejecuta el comando necesario para el despliegue de la PKI generando la CA.
```
./easy-rsa init-pki
```

#### Despliegue CA
A continuación, se despliega la **CA** con el siguiente comando.
```
./easy-rsa build-ca
```
Entonces te pedirá 2 datos, primero una **passphrase** y luego un nombre para el **CN** *(commun name)* en este caso, como ejemplo, he utilizado **mi-vpn-ca**.

Una vez finalizado este proceso se obtendra la siguiente dirección donde está alojado el certificado de CA.
```bash
/home/<user>/easy-rsa/pki/ca.crt
```
Ahora se procede a configurar un certificado y una clave para el servidor
```bash
./easyrsa gen-req server nopass
```
Entonces el OS pide un CN para identificarlo, dado que es el servidor, en este caso se usa **server**. A continuación nos muestra las rutas donde se generan la clave privada y la solicitud pública de certificado.
```bash
/home/<user>/easy-rsa/pki/reqs/server.req
/home/<user>/easy-rsa/pki/private/server.key
```
Una vez se tiene la petición del servidor se procede a firmarla
```bash
./easyrsa sign-req server server
```
Se muestran los datos del CN y se pide otra passphrase para 
el certificado y se muestra el fichero de configuración usado
```
/home/<user>/easy-rsa/pki/openssl-easyrsa.conf
```
Y también el uso de la passphrase del fichero
```
/home/<user>/easy-rsa/pki/private/ca.key
```
Y muestra la ruta de la creación del certificado, además de la fecha de validación (825 days).
```
/home/<user>/easy-rsa/pki/issued/server.crt
```
Con todo esto ahora se ha de generar el Diffie-Hellman
```
./easy-rsa gen-dh
```
Que posee un tamaño de 2048 bits y esta accesible en la ruta siguiente
```bash
/home/<user>/easy-rsa/pki/dh.pem
```
Y para finalizar, como paso opciona se crea la clave TLS-Auth
```bash
openvpn --genkey secret ta.key
```
Esta ta.key se usa dentro del fichero de configuración del servidor server.conf y en el cliente dentro del .ovpn
```
tls-auth ta.key 0 # servidor
tls-auth ta.key 1 # cliente
```
La numeración 0/1 representa el modo de uso, la dirección del canal HMAC.

## Clientes
Hay que generar una solicitud y firmarla. También pide un CN, en este caso proporciono el del servidor, que era **server**. La duración también es de 825 days).
```bash
./easyrsa gen-req clientN nopass # Genera clave privada y CSR para cliente
```
Se obtiene clientN.key (clave privada) y clientN.req (CSR), que están accesibles en las siguientes rutas.
```bash
/home/<user>/easy-rsa/pki/reqs/clientN.req
/home/<user>/easy-rsa/pki/private/clientN.key
```
A continuación se procede a firmar la CSR. Se pide confirmación del sujeto CN y se pide una passphrase haciendo uso de la configuración de /easy-rsa/pki/openssl-easyrsa.cnf y la passphrase de /easy-rsa/pki/private/ca.key.
```bash
./easyrsa sign-req client clientN # Firma la CSR con la CA del servidor y genera el certificado del cliente
```
Y de esta forma se obtiene el certificado del cliente que está disponible en la ruta siguiente
```
/home/<user>/easy-rsa/pki/issued/clientN.crt
```


Con esto se obtiene todo lo necesario para que un cliente se pueda conectar:
- client.key: clave privada
- client.crt: certificado firmado por la CA
- ca.crt: certificado de la CA
- ta.key: clave TLS-Auth compartida
- clientN.ovpn: Configuración del cliente (todo embebido)

### Creación OVPN
Recapitulando los ficheros necesarios son:
- ca.crt, en /pki/ca.crt, resultante de ejecutar la creación de la CA
- clientN.crt, en /pki/issued/clientN.crt, resultante de ejecutar sign-req
- clientN.key, en /pki/private/clientN.key, resultante de ejecutar gen-req clientN nopass
- ta.key, resultante de ejecutar openvpn --genkey secret ta.key

<details>
<summary>
Plantilla para la creación del fichero ovpn embebiendo los datos generados
</summary>
```
cat > clientN.ovpn <<EOF
client
dev tun
proto udp
remote <IP o Dominio del Server> 1194
resolv-retry infinite
nobind
persist-key
persist-tun

<ca>
$(cat pki/ca.crt)
</ca>

<cert>
$(cat pki/issued/client1.crt)
</cert>

<key>
$(cat pki/private/client1.key)
</key>

<tls-auth>
$(cat ta.key)
</tls-auth>
key-direction 1

cipher AES-256-CBC
auth SHA256
verb 3
EOF
```

</details>


Y una vez se tiene el fichero OVPN, desde el cliente ejecutando "openvpn + fichero.ovpn" se accede al servidor por el tunneling.







