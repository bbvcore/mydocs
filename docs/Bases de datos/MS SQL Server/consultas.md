---
title: Consultas base MS SQL Server
---
# MS SQL Server
## Sintaxis
- Uso de **comillas simples** para valores de texto.
- Uso de esquemas en el **from**, si se usa "puntopunto", se usa esquema por defecto (suele ser dbo).

## Seleccionar las bases de datos y las tablas
```bash
select name from sys.databases; # Ver bases de datos
select name from sys.tables; # Ver tablas DB actual (Reales)
select table_name from <dbName>.information_schema.tables; # Solo tablas estandar para el esquema (sin temporales ni especiales)
select * from master.dbo.spt_values; #<dbName>.<esquema><tabla>
```
:::tip
No es obligatorio usar esquema en las consultas pero sí recomendable
:::

### Dentro del esquema de tablas
- table_catalog
- table_schema
- table_name
- table_type
