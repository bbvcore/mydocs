---
sidebar_position: 2
title: Open Canary
---

# Open Canary
Se trata de un **honeypot multiprotocolo** descentralizado, implementado en **Python**. Es multiplataforma pero en **GNU/Linux** es donde se aprovecha todo sus potencial.

Los recursos que necesita para su ejecución son muy bajos lo cual permite que pueda ser instalado y operativo en equipos como **Raspberry Pi**.

:::tip[Repositorio del proyecto]
- <a href="https://github.com/thinkst/opencanary">GitHub de Open Canary</a>
:::


## Instalación
### Pasos previos
Los pasos previos que hay que realizar están orientados a configurar el equipo para la ejecución de Python.

#### Actualización del sistema
```
sudo apt update
```
#### Instalación de Python 
```
sudo apt install -y python3 python3-pip python3.12-venv
```
#### Creación de entorno virtual
```
python3 -m venv opencanary-venv
```
#### Activación
```
~opencanary-venv/bin/$ source activate
```
### Instalar Open Canary
```
pip install opencanary
```
### Configuración
Para la configuración del honeypot se requiere de la generación de un fichero de configuración y de su posterior edición indicando los servicios activos a simular.

#### Creación de fichero de configuración
```
opencanaryd --copyconfig
```
#### Acceso al fichero de configuración creado
```
/etc/opencanaryd/opencanay.conf  
```
#### Edición del fichero de configuración
Aquí se añade la configuración, en este caso para los servicios más habituales, **FTP**, **Web** y **SSH**.
```
{
    "device.node_id": "linux_server",
    "ip.ignorelist": [],
    "git.enabled": false,
    "ftp.enabled": true,
    "ftp.banner": "FTP server ready",
    "http.enabled": true,
    "http.banner": "Apache/2.2.22 (Ubuntu)",
    "http.skin": "basicLogin",
    "ssh.enabled": true,
    "ssh.port": 22,
    "ssh.version": "SSH-2.0-OpenSSH_7.2p2 Ubuntu-4ubuntu2.10"
}
```
#### Inicialización de Open Canary
```
opencanaryd --start
```

#### Comprobación de la ejecución de Open Canary
Una vez inicializado se comprueba que el proceso está en ejecución.

```
ps -aux | grep "opencanaryd"

root        9280  0.0  1.2  79552 48976 ?        S    10:06   0:00 /home/lite/opencanary-venv/bin/python3 /home/lite/opencanary-venv/bin/twistd -y /home/lite/opencanary-venv/bin/opencanary.tac --pidfile /home/lite/opencanary-venv/bin/opencanaryd.pid --syslog --prefix=opencanaryd
lite        9393  0.0  0.0  11804  2304 pts/1    S+   10:08   0:00 grep opencanaryd
```

#### Consulta de logs
Visualizando los **logs** se comprueba que realmente esta funcionando el **honeypot** como debería.

```
tail -f /var/tmp/opencanary.log

{"dst_host": "", "dst_port": -1, "local_time": "2025-04-09 08:06:59.264629", "local_time_adjusted": "2025-04-09 10:06:59.264647", "logdata": {"msg": {"logdata": "Added service from class CanaryFTP in opencanary.modules.ftp to fake"}}, "logtype": 1001, "node_id": "opencanary-1", "src_host": "", "src_port": -1, "utc_time": "2025-04-09 08:06:59.264644"}
{"dst_host": "", "dst_port": -1, "local_time": "2025-04-09 08:06:59.264839", "local_time_adjusted": "2025-04-09 10:06:59.264849", "logdata": {"msg": {"logdata": "Canary running!!!"}}, "logtype": 1001, "node_id": "opencanary-1", "src_host": "", "src_port": -1, "utc_time": "2025-04-09 08:06:59.264847"}
```

#### Como servicio de inicio
Si se requiere de su ejecución desde el inicio de la carga del **OS** se debe de crear una unidad de servicio de **systemd**.
```
[Unit]
Description=OpenCanary Honeypot
After=network.target

[Service]
User=root
ExecStart=/usr/local/bin/opencanaryd --start
Restart=always

[Install]
WantedBy=multi-user.target
```

:::tip[Activación del servicio]
- sudo systemctl d-reload
- sudo systemctl enable opencanary
- sudo systemctl start opencanary
:::

## Comprobaciones del funcionamiento
Una vez instalado y configurado se procede a comprobar su funcionamiento, para ello se realizan varias pruebas.

### Nmap a la IP del Open Canary
La primera puerta es hacer un escaneo agresivo de la **IP** del **HoneyPot** y luego proceder a consultar los **logs** del mismo.
<details>
<summary>
Ejecución de <b>nmap</b> al host <b>10.0.2.15</b>
</summary>

```
nmap -A 10.0.2.15

Starting Nmap 7.94SVN ( https://nmap.org ) at 2025-04-09 10:23 CEST
Nmap scan report for lite-VirtualBox (10.0.2.15)
Host is up (0.000044s latency).
Not shown: 995 closed tcp ports (conn-refused)
PORT    STATE SERVICE     VERSION
21/tcp  open  ftp         vsftpd (before 2.0.8) or WU-FTPD
22/tcp  open  ssh         OpenSSH 9.6p1 Ubuntu 3ubuntu13.9 (Ubuntu Linux; protocol 2.0)
| ssh-hostkey: 
|   256 95:64:73:30:e2:42:fd:37:64:b3:6b:26:a4:71:49:a2 (ECDSA)
|_  256 3d:03:91:34:9f:a8:41:29:20:77:3d:4a:52:b4:5a:ea (ED25519)
25/tcp  open  smtp        Postfix smtpd
|_ssl-date: TLS randomness does not represent time
| ssl-cert: Subject: commonName=linux
| Subject Alternative Name: DNS:linux
| Not valid before: 2025-04-08T08:34:17
|_Not valid after:  2035-04-06T08:34:17
|_smtp-commands: linux, PIPELINING, SIZE 10240000, VRFY, ETRN, STARTTLS, ENHANCEDSTATUSCODES, 8BITMIME, DSN, SMTPUTF8, CHUNKING
139/tcp open  netbios-ssn Samba smbd 4.6.2
445/tcp open  netbios-ssn Samba smbd 4.6.2
Service Info: Host:  linux; OS: Linux; CPE: cpe:/o:linux:linux_kernel

Host script results:
|_nbstat: NetBIOS name: LINUX, NetBIOS user: <unknown>, NetBIOS MAC: <unknown> (unknown)
| smb2-security-mode: 
|   3:1:1: 
|_    Message signing enabled but not required
| smb2-time: 
|   date: 2025-04-09T08:23:14
|_  start_date: N/A

```
</details>

#### Consulta de los logs de Open Canary
Una vez ha finalizado el escaneo del **host** se consultan los logs del **honeypot**.

```
tail -f /var/tmp/opencanary.log

{"dst_host": "", "dst_port": -1, "local_time": "2025-04-09 08:06:59.264629", "local_time_adjusted": "2025-04-09 10:06:59.264647", "logdata": {"msg": {"logdata": "Added service from class CanaryFTP in opencanary.modules.ftp to fake"}}, "logtype": 1001, "node_id": "opencanary-1", "src_host": "", "src_port": -1, "utc_time": "2025-04-09 08:06:59.264644"}
{"dst_host": "", "dst_port": -1, "local_time": "2025-04-09 08:06:59.264839", "local_time_adjusted": "2025-04-09 10:06:59.264849", "logdata": {"msg": {"logdata": "Canary running!!!"}}, "logtype": 1001, "node_id": "opencanary-1", "src_host": "", "src_port": -1, "utc_time": "2025-04-09 08:06:59.264847"}
{"dst_host": "10.0.2.15", "dst_port": 21, "local_time": "2025-04-09 08:23:14.061297", "local_time_adjusted": "2025-04-09 10:23:14.061329", "logdata": {"PASSWORD": "IEUser@", "USERNAME": "anonymous"}, "logtype": 2000, "node_id": "opencanary-1", "src_host": "10.0.2.15", "src_port": 58572, "utc_time": "2025-04-09 08:23:14.061325"}
{"dst_host": "10.0.2.15", "dst_port": 21, "local_time": "2025-04-09 08:23:14.061889", "local_time_adjusted": "2025-04-09 10:23:14.061899", "logdata": {"PASSWORD": "IEUser@", "USERNAME": "anonymous"}, "logtype": 2000, "node_id": "opencanary-1", "src_host": "10.0.2.15", "src_port": 58586, "utc_time": "2025-04-09 08:23:14.061896"}
{"dst_host": "10.0.2.15", "dst_port": 21, "local_time": "2025-04-09 08:23:14.071571", "local_time_adjusted": "2025-04-09 10:23:14.071592", "logdata": {"PASSWORD": "IEUser@", "USERNAME": "anonymous"}, "logtype": 2000, "node_id": "opencanary-1", "src_host": "10.0.2.15", "src_port": 58598, "utc_time": "2025-04-09 08:23:14.071586"}
```
Se puede comprobar como ha habido comprobaciónes de intento de acceso al puerto **21** del servicio **FTP**.

### Comprobación de acceso al ftp conectado a la máquina por SSH
Otra prueba realizada consisten en conectarse por **SSH** al host que tiene instalado y configurado el **honeypot** e intentar establecer una conexión **FTP**.

```
ftp 10.0.2.15

Connected to 10.0.2.15.
220 FTP server ready
Name (10.0.2.15:lite): lite
331 Password required for lite.
Password: 
530 Sorry, Authentication failed.
ftp: Login failed
ftp> 
ftp> exit
221 Goodbye.
```

#### Logs de dicho intento de acceso al FTP 
Después del intento de establecimiento de conexión **FTP** consultando los **logs del honeypot** se puede comprobar los datos introducidos por el **atacante**.
```
{"dst_host": "10.0.2.15", "dst_port": 21, "local_time": "2025-04-09 08:28:20.855439", "local_time_adjusted": "2025-04-09 10:28:20.855478", "logdata": {"PASSWORD": "123456", "USERNAME": "lite"}, "logtype": 2000, "node_id": "opencanary-1", "src_host": "10.0.2.15", "src_port": 33896, "utc_time": "2025-04-09 08:28:20.855471"}
```

