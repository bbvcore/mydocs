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
Acceso a Grafana
</summary>

```bash
- URL: http://localhost:3000
- user/password: admin/admin **se ha de cambiar el password en el primer acceso**
```

</details>

<details>
<summary>
Configuración del plugin MSSQL
</summary>

```
| Campo    | Valor                |
| -------- | -------------------- |
| Host     | `sqlserver:1433`     |
| Database | `master` (o otra) |
| User     | `sa`                 |
| Password | `Str0ng_Passw0rd!`   |
| Encrypt  | `disable`  |

```

</details>


### Consulta canónica para Grafana
```sql
SELECT
  ts AS time,
  value
FROM measurements
WHERE
  tag = 'Pump1.Pressure'
  AND $__timeFilter(ts)
ORDER BY ts;
```
#### Reglas
- La columna debe llamarse **time**
- **__$timeFilter()** es de Grafana, no de SQL Server
- **ORDER BY ts** es recomendable para time series

### Comprobaciones rápidas en Grafana
#### Valores
```sql
SELECT COUNT(*) AS value
FROM dbo.measurements;
```
#### Tags
```sql
SELECT COUNT(*) AS value
FROM dbo.measurements;
ORDER BY tag;
```

### Acceso MS SQL Server
<details>
<summary>
Datos acceso a MS SQL Server
</summary>

```bash
- Host: sqlserver-control
- Puerto: 1433
- User: sa
- Password: 
```

</details>

<details>
<summary>
Tipo de autenticaciones que maneja el plugin
</summary>

```
- <b>Windows Authentication Windows Integrated Security</b> - single sign on for users who are already logged onto Windows and have enabled this option for MS SQL Server.
- <b>Windows AD: Username + password Windows Active Directory</b> - Sign on for domain user via username/password.
- <b>Windows AD: Keytab Windows Active Directory</b> - Sign on for domain user via keytab file.
- <b>Windows AD: Credential cache Windows Active Directory</b> - Sign on for domain user via credential cache.
- <b>Windows AD: Credential cache file Windows Active Directory</b> - Sign on for domain user via credential cache file.

```
</details>

```bash
#Path: /opt/mssql-tools18/bin/
./sqlcmd   -S localhost   -U sa   -P 'Str0ng_Passw0rd!' -C
```
