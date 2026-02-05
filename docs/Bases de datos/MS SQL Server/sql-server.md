crea---
title: SLQ Server
sidebar_id: 1
---
# SQL Server
En Microsoft **SQL Server** el núcleo duro lo constituye **.sys** además de ser compatible con el estandar *SQL* **information_schema**.

## Sentencias SQL
### Crear una base de datos
```sql
create database grafana_lab;
go
```
### Crear un esquema tipo historian
```sql
CREATE TABLE dbo.measurements (id BIGINT IDENTITY(1,1) PRIMARY KEY,ts DATETIME2(3) NOT NULL, tag NVARCHAR(100) NOT NULL, value FLOAT NOT NULL);
GO
```
- **dbo**: esquema por defecto, **SQL Server** siempre necesita un esquema
- **datetime2(3)**, tiempo en milisegundos
- **tag**, nombre de la señal
- **value**, valor numérico

### Insertar valores
```sql
insert into measurements (ts,tag,value) values (dateadd(minute,-30,sysdatetime()),'Pump1.Pressure',12.3);
insert into measurements (ts,tag,value) values (dateadd(minute, -10, sysdatetime()),'Pump1.Flow', 125);
```


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