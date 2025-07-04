---
sidebar_position: 4
title: Suricata
---

## &#128229;Instalación
La instalación, como muchas veces pasa, se puede realizar de diferentes formas, aquí se muestran las dos más habituales.

### &#128230; Desde los repositorios de las distros Debian/Ubuntu
```
sudo apt install suricata -y
```

### &#128230; Desde el repositorio propio de Suricata
```
sudo add-apt-repository ppa:oisf/suricata-stable
sudo apt update
sudo apt install -y suricata
```
Si no se dispone de **add-apt-repository** en la distribución se puede instalar de la siguiente forma.
```
sudo apt install software-properties-common
```

### &#10004; Verificar el resultado de la instalación
```
suricata --build-info
```
<details>
<summary>
<b>Resultado</b> del despligue de <b>Suricata</b>
</summary>

```
┌─[✗]─[borja@parrot]─[~]
└──╼ $suricata --build info
This is Suricata version 6.0.10 RELEASE
Features: NFQ PCAP_SET_BUFF AF_PACKET HAVE_PACKET_FANOUT LIBCAP_NG LIBNET1.1 HAVE_HTP_URI_NORMALIZE_HOOK PCRE_JIT HAVE_NSS HAVE_LUA HAVE_LUAJIT HAVE_LIBJANSSON TLS TLS_C11 MAGIC RUST 
SIMD support: none
Atomic intrinsics: 1 2 4 8 byte(s)
64-bits, Little-endian architecture
GCC version 12.2.0, C version 201112
compiled with _FORTIFY_SOURCE=2
L1 cache line size (CLS)=64
thread local storage method: _Thread_local
compiled with LibHTP v0.5.42, linked against LibHTP v0.5.42
```
</details>

## &#128194; Ficheros importantes
### &#128196; Suricata.yaml
Es el archivo principal de configuración
```
/etc/suricata/suricata.yaml
```
<details>
<summary>
Extracto del contenido del fichero suricata.yaml
</summary>

```
# Suricata configuration file. In addition to the comments describing all
# options in this file, full documentation can be found at:
# https://suricata.readthedocs.io/en/latest/configuration/suricata-yaml.html
#
# This configuration file generated by:
#     Suricata 6.0.10

##
## Step 1: Inform Suricata about your network
##

vars:
  # more specific is better for alert accuracy and performance
  address-groups:
    HOME_NET: "[192.168.0.0/16,10.0.0.0/8,172.16.0.0/12]"
    #HOME_NET: "[192.168.0.0/16]"
    #HOME_NET: "[10.0.0.0/8]"
    #HOME_NET: "[172.16.0.0/12]"
    #HOME_NET: "any"

```
</details>

### &#128220; Logs
Suricata tiene sus propios logs dentro del directorio habitual en GNU/Linux.
```
/var/log/suricata
```
:::info[Principales logs]
- eve.json
- fast.log
- stats.log
- suricata.log
:::

### &#128214; Reglas
El conjunto de reglas locales
```
/etc/suricata/rules
```
Aquí se pueden encontrar **conjuntos de reglas** *agrupadas* por tipo de **protocolo**, destacando algunos como: *dhcp-events.rules, files.rules, http2-events.rules, modbus-events.rules, mqtt-events.rules, smb-events.rules, tls-events.rules, ssh-events.rules o smtp-events.rules*.
<details>
<summary>
Ejemplos de conjuntos de reglas para el protocolo <b>modbus</b>.
</summary>

```
┌─[borja@parrot]─[/etc/suricata/rules]
└──╼ $cat modbus-events.rules
# Modbus Protocol version field is incorrect (Modbus version = 0)
alert modbus any any -> any any (msg:"SURICATA Modbus invalid Protocol version"; app-layer-event:modbus.invalid_protocol_id; classtype:protocol-command-decode; sid:2250001; rev:2;)
# Response (answer) we didn't see a Request for. Could be packet loss.
alert modbus any any -> any any (msg:"SURICATA Modbus unsolicited response"; app-layer-event:modbus.unsolicited_response; classtype:protocol-command-decode; sid:2250002; rev:2;)
# Malformed request or response. Malformed means length field is wrong
alert modbus any any -> any any (msg:"SURICATA Modbus invalid Length"; app-layer-event:modbus.invalid_length; classtype:protocol-command-decode; sid:2250003; rev:2;)
# Unit identifier field is incorrect
alert modbus any any -> any any (msg:"SURICATA Modbus invalid Unit Identifier"; app-layer-event:modbus.invalid_unit_identifier; classtype:protocol-command-decode; sid:2250004; rev:2;)
# Modbus Function code is incorrect
alert modbus any any -> any any (msg:"SURICATA Modbus invalid Function code"; app-layer-event:modbus.invalid_function_code; classtype:protocol-command-decode; sid:2250005; rev:2;)
# Modbus Request/Response value field is incorrect
alert modbus any any -> any any (msg:"SURICATA Modbus invalid Value"; app-layer-event:modbus.invalid_value; classtype:protocol-command-decode; sid:2250006; rev:2;)
# Modbus Expception code is incorrect
alert modbus any any -> any any (msg:"SURICATA Modbus Exception code invalid"; flow:to_client; app-layer-event:modbus.invalid_exception_code; classtype:protocol-command-decode; sid:2250007; rev:2;)
# Value field in Modbus Response does not match with Modbus Request
alert modbus any any -> any any (msg:"SURICATA Modbus Data mismatch"; flow:to_client; app-layer-event:modbus.value_mismatch; classtype:protocol-command-decode; sid:2250008; rev:2;)
# Request Flood Detected
alert modbus any any -> any any (msg:"SURICATA Modbus Request flood detected"; flow:to_server; app-layer-event:modbus.flooded; classtype:protocol-command-decode; sid:2250009; rev:2;)

```
</details>

:::warning[SID]
Las reglas personalizadas añadidas han de tener un SID > 1.000.000
:::

### &#128257; Suricata-update
Es el fichero de configuración para **suricata-update**
```
/etc/suricata/update.yaml
```
## &#128737; Ejecución como IDS
Remplazar la interfaz por el nombre correspondiente de la interfaz escogida.
```
sudo suricata -c /etc/suricata/suricata.yaml -i eth0
```
<details>
<summary>
Lanzamiento de <b>Suricata</b> sin especificar reglas
</summary>

```
┌─[borja@parrot]─[/etc/suricata/rules]
└──╼ $sudo suricata -c /etc/suricata/suricata.yaml -i wlx3c52a1c35918
[sudo] contraseña para trabajo: 
14/4/2025 -- 11:40:42 - <Notice> - This is Suricata version 6.0.10 RELEASE running in SYSTEM mode
14/4/2025 -- 11:40:42 - <Warning> - [ERRCODE: SC_ERR_NO_RULES(42)] - No rule files match the pattern /etc/suricata/rules/suricata.rules
14/4/2025 -- 11:40:42 - <Warning> - [ERRCODE: SC_ERR_NO_RULES_LOADED(43)] - 1 rule files specified, but no rules were loaded!
14/4/2025 -- 11:40:42 - <Notice> - all 12 packet processing threads, 4 management threads initialized, engine started.
```
</details>

Existen reglas pero no las cargó **Suricata** por ello se ha de revisar la configuración del fichero **yaml**, y comprobar en la sección **rule-files** que apuntan correctamente al destino.

Entonces en la sección mencionada se añaden todas las reglas que existan en el directorio **/etc/suricata/rules**

<details>
<summary>
Contenido de la sección de rule-files
</summary>
```
rule-files:
  - app-layer-events.rules
  - dns-events.rules
  - ipsec-events.rules
  - nfs-events.rules
  - ssh-events.rules
  - decoder-events.rules
  - files.rules
  - kerberos-events.rules
  - ntp-events.rules
  - stream-events.rules
  - dhcp-events.rules
  - http2-events.rules
  - modbus-events.rules
  - smb-events.rules
  - tls-events.rules
  - dnp3-events.rules
  - http-events.rules
  - mqtt-events.rules
  - smtp-events.rules
```
</details>

:::warning[Comprobar la ruta en suricata.yaml]
Comprobar en el fichero de configuración **suricata.yaml** la ruta por defecto de las reglas, ya que puede no ser **/etc/suricata/rules**. La variable a buscar en el fichero es **default-rule-path**.
:::

A continuación se reinicia **Suricata**
```
sudo systemctl restart suricata
```
:::warning[]
Por defecto los módulos **http2**, **modbus** y **dnp3** vienen como *"enable:no"* y hay que ponerlos a *"enable:yes"* para que **Suricata** arranque bien.
:::

### &#8594; Test de funcionamiento
```
┌─[✗]─[borjao@parrot]─[/etc/suricata/rules]
└──╼ $sudo suricata -T -c /etc/suricata/suricata.yaml
[sudo] contraseña para borja: 
14/4/2025 -- 12:23:23 - <Info> - Running suricata under test mode
14/4/2025 -- 12:23:23 - <Notice> - This is Suricata version 6.0.10 RELEASE running in SYSTEM mode
14/4/2025 -- 12:23:23 - <Notice> - Configuration provided was successfully loaded. Exiting.

```

### &#8594; Funcionamiento correcto
```
┌─[borja@parrot]─[/etc/suricata/rules]
└──╼ $sudo suricata -c /etc/suricata/suricata.yaml -i wlx3c52a1c35918
[sudo] contraseña para trabajo: 
14/4/2025 -- 12:26:33 - <Notice> - This is Suricata version 6.0.10 RELEASE running in SYSTEM mode
14/4/2025 -- 12:26:33 - <Notice> - all 12 packet processing threads, 4 management threads initialized, engine started.

```


## &#128221; Regas Emerging Threats
Un conjunto de reglas rápidas de añadir a Suricata desarrolladas por la comunidad de **Emerging Threats**.
```
sudo apt install suricata-update
sudo suricata-update
```
## &#128276; Ver alertas
```
sudo tail -f /var/log/suricata/fast.log
```

## &#9989; Comprobaciones
### &#8594; Ejecución en primer plano
```
sudo suricata -c /etc/suricata/suricata.yaml -i eth10 --init-errors-fatal
```
:::note[]
- **c**: indica el path del fichero de configuración
- **i**: configura la interfaz en la que va a escuchar
- **--init-errors-fatal**: muestra los errores fatales en el lanzamiento de Suricata.

### &#8594; Simular tráfico malicioso
```
curl http://testmyids.com
```
:::tip[Web de pruebas]
La **URL** *testmyids.com* sirve para probar si el IDS/IPS está bien configurado, en este caso simula respuesta del comando "id" con lo cuál parece haber tenido éxito una vulnerabilidad y debería de mostrar una alerta el IDS/IPS.
:::

### &#8594; Leer logs 
```
tail -f /var/log/suricata/fast.log
```
:::note[]
- **f**: sigue al descriptor del fichero, aunque se renombre el fichero.
:::

### &#128269; Inspeccionar eve.json
#### &#128297; JQ
**JQ** sirve para procesar JSON y llevar a cabo varias operaciones, como el embellecimiento de los datos.

:::tip[Embellece tu JSON]
-<a href="https://jqlang.org/">Enbellecedor JSON</a>
:::

Si no se encuentra instalado en el equipo es posible instalarlo de la siguiente forma en equipos Linux.
```
sudo apt install jq
```
Un buen ejemplo para comprobar la legibilidad que ofrece esta utilidad es ejecutar los siguientes comandos desde una terminal y apreciar las enormes diferencias.
```
cat eve.json # Se verá un stream de datos dificilmente seguible
jq . eve.json # Se mostrará una sucesión de objetos JSON legibles
```

#### &#128278; Eve.JSON
Fichero principal que genera Suricata en formato JSON, en este fichero se pueden consultar los siguientes eventos:

- **Alertas**: consultando el tipo de evento de alerta, **"event_type":"alert"**.
- **Comprobar las conexiones de red**: a través del tipo de evento flujo,  **"event_type":"flow"**.
- Posibilita el análisis de protocolos como SSH, HTTP, TLS...
- Información sobre archivos detectados.
- Información sobre los protocolos detectados.
- Consulta de los Logs.

```
jq . /var/log/suricata/eve.json | less
```
Este fichero **eve.json** es la base de **Suricata** para trabajar con varios sistemas como **ELK** o **Grafana**.



## &#128295; Crear reglas propias en Suricata
### &#128208; Reglas HTTP
Las reglas en suricata siguen una estructura determinada que es la siguiente:
```
acción protocolo src_ip src_port -> dst_ip dst_port (opciones)
```
:::tip[Parámetros de las reglas]
- **acción**: detectar un evento *(alert, drop o reject)*
- **protocolo**: el protocolo correspondiente *(http, udp, icmp)*
- **src_ip**: ip de origen
- **src_port**: puerto de origen
- **dst_ip**: ip de destino
- **dst_port**: puerto de destino
- **opciones**: opciones varias como mensajes, información adicional, etc...
:::


<details>
<summary>
Listado de características más utilizadas en <b>HTTP</b>
</summary>

```
- "msg:text" texto del mensaje 
- "sid: number": ID único de las reglas, para personalizadas superior a 1000000.
- "classtype:type": tipo aplicación
- "rev:value" versión de la regla, incrementa con las ediciones
- "flow: to_server, established": paquete hacía el servidor, conexión establecida
- "flow: to_client, established": paquete hacía el cliente, conexión establecida
- "flow: established", solo conexiones establecidas
- "http.method": método 
- "http.uri": ruta del recurso
- "http.host": nombre del dominio
- "http.user_agent": el agente (curl, mozilla)
- "http.request_line": línea de la petición (VerboHTTP /url HTTP/version)
- "content:cadena": una cadena literal a buscar:
1. 'nocase': no case sensitive
2. 'offset:x;': rangos de búsqueda
3. 'depth:y;': rangos de búsqueda
- 'pcre:"/expr/" : expresiones regulares tipo PCRE
- 'threshold:type limit, track by_src, count number, seconds number' alerta por IP cada X tiempo.
```
</details>



#### &#8594; Regla para peticiones HTTP
Establecimiento de una regla propia básica de Suricata para comprobar cualquier tipo de petición HTTP que se produzca.
```
alert http any any -> any any (msg:"HTTP GET Request Detected"; flow:to_server,established; http.method; content:"GET"; classtype:web-application-activity; sid:1000001; rev:1;)
```
<details>
<summary>
Explicación de la estrutura de la regla aplicada.
</summary>

```
- <b>Tipo de acción</b>: alert, se notifica una alerta
- <b>Protocolo</b>: http.
- <b>any</b>: cualquier IP origen
- <b>any</b>: cualquier PORT origen
- <b>any</b>: cualquier IP destino
- <b>any</b>: cualquier PORT destino
- <b>()</b>: incluye las opciones. Condiciones ESTRICTAS para que la alerta se dispare.
```
</details>

<details>
<summary>
Explicación de las opciones.
</summary>

```
- <b>msg</b>: mensaje que aparecerá en el LOG cuando la regla se dispare.
- <b>flow</b>: to_server, stablished: flujo de datos, paquete de cliente a servidor  y conexión establecida.
- <b>http.method</b>: se indica la búsqueda en el campo http.method.
- <b>content</b>:"get", busca GET en la cabecera HTTP
- <b>classtype</b>:web-application-activity: clasifica la alerta en la categoría correspondiente.
- <b>SID</b>: idnetificador único de la regla
- <b>rev1</b>: versión de la regla, cada vez que se cambié la regla se debe de incrementar.
```
</details>

#### &#8594; Comprobación del funcionamiento de la regla
```
sudo tail -f /var/log/suricata/fast.log 
04/16/2025-09:35:55.545375  [**] [1:1000001:1] HTTP GET Request Detected [**] [Classification: access to a potentially vulnerable web application] [Priority: 2] {TCP} 10.0.2.15:52994 -> 193.110.128.199:80
```

#### &#8594; Regla para respuestas HTTP
```
alert http any any -> any any (msg:"HTTP 200 OK Response Detected"; flow:to_client,established; http.response_line; content:"200 OK"; classtype:successful-user; sid:1000002; rev:1;)
```


<!--
// Perndiente de instalar y trabajar con el, vigilar HTTP y HTTPS
## Evebox
-->





















## &#127760; Anexo redes [comando ip]
### &#9989; Comprobaciones de namespaces (espacios de red)
Obtener el **UUID** con el parámetro **netns** que sirve para averiguar un **network namespace** *(espacio de red aislado, como en la contenerización)*, entonces desde un host se puede interaccionar con estos espacios.

```
ip netns list
```
Ver información de dicho **UUID**.
```
ip netns exec netns-35c7edf0-709c-0cb3-7bd1-216a73b9a29e ip a
```

:::info[Parámetros netns usados]
- **ip netns exec**, comando a ejecutar en un espacio de red.
- **netns-...**, identificador del nombre del espacio.
- **ip a**, el comando a ejecutar dentro del espacio de red.
:::

<details>
<summary>
Resultado de la consulta
</summary>

```
┌─[borja@parrot]─[/etc/suricata]
└──╼ $sudo ip netns exec netns-35c7edf0-709c-0cb3-7bd1-216a73b9a29e ip a
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host proto kernel_lo 
       valid_lft forever preferred_lft forever
2: eth0@if5: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc noqueue state UP group default qlen 1000
    link/ether 6e:8f:28:bf:5d:4e brd ff:ff:ff:ff:ff:ff link-netnsid 0
    inet 10.89.0.2/24 brd 10.89.0.255 scope global eth0
       valid_lft forever preferred_lft forever
    inet6 fe80::6c8f:28ff:febf:5d4e/64 scope link proto kernel_ll 
       valid_lft forever preferred_lft forever

```
</details>









