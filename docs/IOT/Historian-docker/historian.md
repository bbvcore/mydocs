---
title: Clon del Historian
---

# Clon del Historian
Para este clon se crean varios contenedores con docker:
- **Node-red**: opcional para trabajar con Mqtt
- **MS SQL server**: base de datos que usa historian
- **Grafana**: visualizador de datos y creaciones de dashboards

Todos ellos con persistencia y una red para interconectarlos

## Grafana
### Plugin SQL Server
Para configurar el plugin de SQL Server usando contenedores se usan las siguientes opciones:
- **User**: sa
- **Password**: Str0ng_Passw0rd!
- **Database**: historian
- **TLS**: disable

:::tip
Como host nunca usar con contenedores localhost sino el nombre del host, en este caso **sqlserver**, y el puerto por defecto **1433**
:::

### Consulta para Gráfica
```sql
SELECT TOP 200
  EventTime AS time,
  ValueFloat AS value
FROM History
ORDER BY EventTime DESC;
```


## SQL Server
Creación de la simulación para Historian
```sql

CREATE DATABASE Historian;
GO

USE historian;
GO

CREATE TABLE History (
    Id BIGINT IDENTITY(1,1) PRIMARY KEY,
    TagName NVARCHAR(100) NOT NULL,
    ValueFloat FLOAT NOT NULL,
    Quality INT DEFAULT 192,
    EventTime DATETIME2 NOT NULL DEFAULT SYSUTCDATETIME()
);
GO

```
### Script inserción
```bash
#!/bin/bash
while true; do
    VALUE=$(LC_NUMERIC=C awk -v min=20 -v max=30 'BEGIN{srand(); print min+rand()*(max-min)}')
    docker exec sqlserver-control /opt/mssql-tools18/bin/sqlcmd \
        -S localhost -U sa -P 'Str0ng_Passw0rd!' -d Historian \
        -C \
        -Q "INSERT INTO History (TagName, ValueFloat, Quality, EventTime) VALUES ('Temperature1', $VALUE, 192, SYSUTCDATETIME());"
    echo "Insertado valor: $VALUE"
    sleep 5
done
```
