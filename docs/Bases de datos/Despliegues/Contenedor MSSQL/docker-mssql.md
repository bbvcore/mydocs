---
title: Contenedor MS SQL
sidebar_id: 1
---
# Contenedor MSSQL

## Docker-compose
<details>
<summary>
Fichero docker-compose.yml para despliegue de contenedor SQL Server y Grafana
</summary>
<details>

```bash
version: "3.9"

networks:
  monitoring_net:
    driver: bridge
    name: monitoring_net

volumes:
  sqlserver_data:
  grafana_data:

services:
  sqlserver:
    image: mcr.microsoft.com/mssql/server:2022-latest
    container_name: sqlserver-control
    hostname: sqlserver
    restart: unless-stopped
    networks:
      - monitoring_net
    ports:
      - "1433:1433"
    environment:
      ACCEPT_EULA: "Y"
      MSSQL_SA_PASSWORD: "Str0ng_Passw0rd!"
      MSSQL_PID: "Developer"
    volumes:
      - sqlserver_data:/var/opt/mssql

  grafana:
    image: grafana/grafana:latest
    container_name: grafana-control
    restart: unless-stopped
    networks:
      - monitoring_net
    ports:
      - "3000:3000"
    depends_on:
      - sqlserver
    volumes:
      - grafana_data:/var/lib/grafana
```
</details>

## Arranque y accesos
## Ejecución de los contenedores y comprobaciones
Para desplegar el fichero yml y los contenedores se usa el siguiente comando.
```bash
sudo docker compose up -d
```
Para acceder al contenedor de MSSQL y hacer uso del cliente sqlcmd se usa el siguiente comando.
```bash
sudo docker exec -it sqlserver-control bash
```
Para realizar la monitorización de la red y comprobar su correcto funcionamiento
```bash
docker network inspect <name red>
```
### Acceso grafana
<details>
<summary>

```bash
- URL: http://localhost:3000
- user/password: admin/admin **se ha de cambiar el password en el primer acceso**
```
</summary>
</details>

<details>
<summary>
Configuración del plugin MSSQL

```
| Campo    | Valor                |
| -------- | -------------------- |
| Host     | `sqlserver:1433`     |
| Database | `master` (o otra) |
| User     | `sa`                 |
| Password | `Str0ng_Passw0rd!`   |
| Encrypt  | `disable`  |

```
</summary>
</details>

### Acceso MS SQL Server
<details>
<summary>

```bash
- Host: sqlserver-control
- Puerto: 1433
- User: sa
- Password: 
```
</summary>
</details>

<details>
<summary>
Tipo de autenticaciones que maneja el plugin

```
- **Windows Authentication Windows Integrated Security** - single sign on for users who are already logged onto Windows and have enabled this option for MS SQL Server.
- **Windows AD: Username + password Windows Active Directory** - Sign on for domain user via username/password.
- **Windows AD: Keytab Windows Active Directory** - Sign on for domain user via keytab file.
- **Windows AD: Credential cache Windows Active Directory** - Sign on for domain user via credential cache.
- **Windows AD: Credential cache file Windows Active Directory** - Sign on for domain user via credential cache file.

```
</details>

```bash
#Path: /opt/mssql-tools18/bin/
./sqlcmd   -S localhost   -U sa   -P 'Str0ng_Passw0rd!' -C
```
