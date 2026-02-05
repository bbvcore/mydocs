---
title: Contenedor Oracle
---
# Contenedor Oracle
## Creación desde la terminal
### Permisos para el volumen local
Oracle a la mínima cierra el contenedor, por ello es importante dejarlo todo bien atado.
```bash
sudo mkdir -p /home/borja/oradata
sudo chown 54321:54321 /home/borja/oradata
```

### Comando ejecución y creación del contenedor de Oracle
```bash
docker run -d \
  --name oracle23c \
  -p 1521:1521 \
  -p 5500:5500 \
  -e ORACLE_PWD=MiPassword123 \
  -v /home/borja/oracle:/opt/oracle/oradata \
  container-registry.oracle.com/database/free:latest
```

### Comprobación de la ejecución
```bash
docker exec -it oracle23c sqlplus sys/MiPassword123@localhost:1521/FREEPDB1 as sysdba
```
O usar este comando
```bash
docker exect -it oracle sqlplus
```
Y a continuación pedirá el user y el password, en ese caso para el usuario se usará
```bash
sys as sysdba # como Administrador
# también se puede usar: sys as sysoper
```
Luego se meterá la contraseña y se estará dentro de oracle SQL.

:::tip[Información]
sys	Usuario
MiPassword123:	la contraseña
localhost: host con Oracle
1521:	Listener
FREEPDB1:	Servicio 
as sysdba:	Rol de admin
:::



### Detener contenedor
```bash
docker stop <tag ID>
```
### Eliminar contenedor
```bash
docker rm <tag ID>
```

## Creación con docker coompose
<details>
<summary>
Fichero docker compose
</summary>

```bash
version: '3'
services:
  oracle:
    image: container-registry.oracle.com/database/free:latest
    container_name: oracle23c
    ports:
      - "1521:1521"
      - "5500:5500"
    environment:
      ORACLE_PWD: MiPassword123
    volumes:
      - ./oradata:/opt/oracle/oradata

```
</details>

:::tip
- Puerto 1521: listener, puerto principal por donde pasan todas las conexiones clientes.
- Puerto 5500: puerto para la interfaz web de administración (/em)
::: 

