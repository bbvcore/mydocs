
# OpenSSL

## :books: Conceptos teóricos
## &#128196; Pasos para la obtención de un certificado
### &#128229; Solicitud de firma de certificado (CSR)
Contiene **información relevante** e *importante* del **dominio**, **organización** y **clave pública**. Es el primer paso a la hora de generar un certificado **SSL/TLS**.

El **CSR** se envía a una **CA** *(Autoridad de Certificación)*, la cual se encarga de **crear** el **certificado digital real**. 

### &#128737; Funcionamiento de la solicitud CSR
Toda la solicitud se basa en la infraestructura **PKI** *(Clave Pública)* y compete una serie de procedimientos.

<details>
<summary>
Listado de pasos a realizar para completar la solicitud
</summary>

1. Generación de un **CSR** en el servidor mediante OpenSSL.

2. Con el certificado **CSR** se crean un par de claves, la pública y la privada, de forma simultánea. La clave pública va adjunta al CSR mientras que la clave privada se mantiene en el servidor de forma segura.

3. La **CSR** se envía a una *Autoridad de Certificación* **(CA)**

4. LA **CA** verifica la **CSR**, comprobando la propiedad del dominio o de la organización.

5. Obtención del certificado TLS/SSL para instalar en el servidor.

</details>

<details>
<summary>
¿Qué información contiene el CSR?
</summary>

1. Common Name (CN): que se corresponde con el FQDN.
2. Organization (O): el nombre de la organización (empresa).
3. Unidad Organizativa (UO): el departamento de la organización (es opcional).
4. País (C): con 2 letras.
5. State/province (S)
6. Localidad (L)
7. Dirección de email (opcional)
8. Clave Pública
</details>

### &#128451; Generación de un CSR
#### &#128421; Desde la terminal
Se realiza a través de los parámetros de SSL
```bash
openssl req -new -newkey rsa:2048 -nodes -keyout domain.key -out domain.csr
```
Y con esta ejecución se obtienen 2 ficheros:
- Clave privada
- Solicitud de certificado (CSR)

:::info[Leyenda del comando]
- **req**: solicitud de certificados
- **new**: nueva petición
- **newkey rsa:2048**: una clave RSA de 2048 bits, clave asimétrica (privada y pública). de 2048 a 4096 a día de hoy es la longitud más habitual para la clave.
- **nodes**: opcional para no cifrar la clave privada, no pide contraseña.
- **keyout**: fichero de salida de la clave privada
- **out**: archivo de salida CSR
:::


#### &#128421; Desde servidores de hosting
Tanto en servidores GNU/Linux como Windows se suele ofrecer la posibilidad de solicitar CSR con opciones como "Generar un nuevo CSR" o "Crear una solicitud de certificado" y entonces se deben de rellenar una serie de campos en un formulario web para obtener la solicitud.





## &#128221; Instalación
###  &#128194; Desde la terminal y los repositorios
```bash
sudo apt update
sudo apt install openssl
```

### &#128295; Desde github
:::tip
https://github.com/openssl/openssl
:::

## &#128736;Uso habitual

### Generar clave privada
Para generar la clave privada se puede realizar de dos formas, utilizando genpkey o genrsa.
:::tip
La clave privada se utiliza dentro de la encriptación asimétrica en varias situaciones como pueden ser: generar un CSR, realizar firma digital o la configuración de servidores.
:::

Las claves privadas se obtienen con el formato **PEM** *(Privacy Enchanced Mail)*, el cual se trata de un texto plano codificado en formato **Base64** delimitado por unas cabeceras, que indican el comienzo y el final de la clave.

:::tip
**PEM**: es utilizado habitualmente tanto para almacenar claves como certificados en Open SSL.
:::

#### Método clásico, RSA
Este método genera una clave clásica RSA, es importante, en este caso, que sea como mínimo de 2048 bits.
```bash
openssl genrsa -out name.key 2048
```
#### Método moderno, Genpkey
Este método permite utilizar otros algoritmos diferentes y más modernos.
```bash
openssl genpkey -algorithm RSA -out name.key -pkeyopt rsa_keygen_bits:2048
```
:::tip
- genpkey: generar una cave
- algorithm: se específica el algoritmo a usar
- out: el nombre de salida para la clave creada
- pkeyopt: las opciones de configuración
:::

#### Clave pública (si fuera necesario)
La clave pública se puede generar desde la clave privada.
```bash
openssl rsa -in <name.key> -pubout -out name.pub
openssl pkey -in <name.key> -pubout -out name.pub
```
:::tip
Recomendable asignar el nombre de la clave pública el mismo que tenía la clave privada para tener una mejor gestión de claves
:::

Con el comando cat podemos ver el contenido de las claves generadas.

### Crear un CSR
Un CSR es una solicitud de firma de certificado.
```bash
opensssl req -new -key name.key -out name.csr
```
:::tip
- req: solicitud
- new: nuevo
- key: clave usada para generar el csr
- out: la salida del csr creado
:::

### Certificado autofirmado
De esta forma se obtiene un **certificado autofirmado** como si proviniera de una entidad de confianza, aunque esto solo funciona realmente bien en entornos de desarollo.
```bash
openssl x509 -req -in name.csr -signkey name.key -out name.crt -days 365
```
:::tip
- req: indica que se introduce un CSR.
- signkey: clave privada para la firma.
- out: certificado obtenido.
- days: días de validez.
- opcional: se puede añadir la clave pública
:::

## &#128221; Anexo
### &#9989; Comprobaciones
#### &#8594; Comprobar contenido clave
```bash
cat name.ley
```
#### &#8594; Ver la clave privada
```bash
openssl rsa -text in <clave.key> -noout
```
#### &#8594; Comprobar la información CSR
```bash
openssl req -text -in <solicitud.csr> -noout -verify
```
#### &#8594; Crear una CA (local)

Para crear un certificado autofirmado se usa el siguiente comando
```bash
openssl req -x509 -new -key ca.key -out ca.crt -days 3650 -subj "/CN=Mi CA"
```

Para firmar una solicitud CSR proveniente de otro usuario o cliente
```bash
openssl x509 -req -in client.csr -CA ca.crt -CAkey ca.key -CAcreateserial -out client.crt -days 365
```
:::tip
- **CA** y **CAkey**: son la dupla correspondiente a la **clave** y al **certificado** de la **CA**.
- **CAcreateserial**: archivo con número de serie *(ca.srl)*.
:::

### &#128736; Formatos de extensiones
<details>
<summary>
Listado de las principales siglas utilizadas
</summary>

- **.pem**: puede contener clave privada, pública,CSR, certificado. (más usado en linux y servidores)
- **.der**: certificados o claves públicas. (más usado en Java o Windows)
- **.crt**: certificado en formato PEM/DER.
- **.cer**: certificado en formato PEM/DER.
- **.key**: clave privada
- **.csr**: solicitud de certificado en formato PEM/DER
- **.p12**: clave privada más certificado (usado en Windows, Java, navegadores web)
- **.pfx**: clave privada más certificado
- **.p7b**: solo certificados 

</details>

### &#128421; Uso en Servidores
#### &#8594; Apache
Añadir a la configuración de virtual host **SSL Engine on**
```bash
# Activar SSL
    SSLEngine on

# Autofirmado
    SSLCertificateFile /ruta/a/name.crt
    SSLCertificateKeyFile /ruta/a/name.key

# Si hubiera una CA propia - es opcional
    SSLCertificateChainFile /ruta/a/ca.crt 
```
A continuación se activa el módulo **SSL** de **apache** con el siguiente comando. 
```
sudo a2enmod ssl
```

#### &#8594; Nginx
La configuración de **Nginx** es más sencilla que con **Apache** aunque conceptualmente es bastante similar.

```bash
server {
    listen 443 ssl; # Activar SSL en el puerto por defecto 443
    server_name example.local;

    ssl_certificate /<path>/name.crt;
    ssl_certificate_key /<path>/name.key;

    # Si fue firmado por tu CA privada:
    ssl_client_certificate /<path>/name.crt;  # opcional para autenticación mutua

    location / {
        root /var/www/html;
    }
}
```
A continuación se comprueba que esten correctos los ajustes y se procede a reiniciar.
```bash
sudo nginx -t   # verifica las configuraciones
sudo systemctl reload nginx
```








