---
title: Consultas Oracle
---
# Consultas Oracle
El cliente de Oracle en terminal es **sqlplus**.

## Rutas importantes
```bash
/opt/oracle/oradata	#Datos de la base (PDB, CDB, ficheros de control, etc.)
/opt/oracle/product/23c/dbhomeFree	#Instalación del motor Oracle
/opt/oracle/diag	#Logs y diagnósticos
/home/oracle	#Tu home dentro del contenedor
```

## Acceso
Acceso como administrador
```bash
sqlplus / as sysdba
```
Acceso como usuario
```bash
sqlplus user/password@basedatos
```
## Comandos
### Crear usuario
Un user es un esquema no se crean base de datos en oracle
```bash
create user userPrueba identified by userPrueba123; # Identified es la password
grant connect, resource to userPrueba;
```
### Basicos
- **CDB**: container database, como el host de las dbs
- **PDB**: pluggable database, como mv dentro del host

Las PDB pueden estar:
- **Mounted** *(montadas pero no abiertas)*
- **Open** *(listas para usar)*

```bash
+---------------------------+
|           CDB             |  ← Host
|   +-------------------+   |
|   |      PDB1         |   |  ← Bases de datos
|   +-------------------+   |
|   |      PDB2         |   |
|   +-------------------+   |
+---------------------------+
```
Esta forma de funcionar se realiza porque Oracle permite tener muchas bases de datos en un servidor y poder mover las **PDB** entre servidores

#### Conexiones habituales
```bash
show pdbs; # Mostrar bases de datos
alter pluggable database FREEPDB1 open; # Abrir PDB si no está abierta, como encender la MV
alter session set container=FREEPDB1 # Conexión a la PDB, entrar a la PDB
```

En este listado de PDBs se puede ver la SEED que es la semilla que usa Oracle como plantilla para crear bases de datos
y las FREE son las bases de datos reales.
```bash
    CON_ID CON_NAME			  OPEN MODE  RESTRICTED
---------- ------------------------------ ---------- ----------
	 2 PDB$SEED			  READ ONLY  NO
	 3 FREEPDB1			  READ WRITE NO

```


### Sintesis
```sql
sqlplus / as sysdba
show pdbs;
alter pluggable database FREEPDB1 open;
alter session set container=FREEPDB1;
CREATE USER demo IDENTIFIED BY demo123;
GRANT CONNECT, RESOURCE TO demo;
```


### Crear una tabla sencilla
:::tip
Equivalente a auto_increment en MySQL/MariaDB es **generated always 
as identity** 
:::
```sql
create table users (
    id number generated always as identity primary key,
    name varchar2(100),
    precio number(10,2)
)   
```
### CRUD
```sql
INSERT INTO productos (nombre, precio) VALUES ('Teclado', 19.99);
SELECT * FROM productos;
```

## PL SQL
### Introducción PL / SQL

### Ejemplo de uso
Activar mostrar mensajes en pantalla
```bash
set serveroutput on;
```
#### Mandar un mensaje
```sql
begin
    DBMS_OUTPUT.PUT_LINE('Primer mensaje PL/SQL');
end;
/
```
## Procedimientos
Los procedimientos son algoritmos que permiten ejecutar una serie de pasos cada vez que sea necesario, contribuyendo a la modularidad y reutilización.
### Ejemplo de uso de un procedimiento
#### Comprobar contenedor
```bash
show con_name
```
#### Ver PDBS
```bash
show pdbs;
```
#### Abrir la PDB 
Solo si no está abierta
```bash
alter pluggable database freepdb1 open
```
#### Cambiar contexto de la PDB
Solo si no se está en el correcto
```bash
alter session set container = freedb1;
show con_name; # Comprobar el contexto
```
#### Crear un user para trabajar
```bash
CREATE USER worker IDENTIFIED BY worker;
GRANT CONNECT, RESOURCE TO worker;
ALTER USER worker QUOTA UNLIMITED ON USERS; # Espacio ilimitado dentro del tablero users
```
#### Crear table 
```bash
CREATE TABLE people (
    id   NUMBER,
    name VARCHAR2(50)
);

```
##### Comprobación de la tabla
```bash
SQL> select table_name from user_tables;

TABLE_NAME
-------------------------
PEOPLE

```



#### Crear procedimiento
```sql
-- Procedure
CREATE OR REPLACE PROCEDURE insertar_user(
    p_id   NUMBER,
    p_name VARCHAR2
) IS
BEGIN
    INSERT INTO people(id, name)
    VALUES (p_id, p_name);
END;
/
```
<details>
<summary>
Ejemplo de creacción correcta
</summary>

```bash
SQL> create or replace procedure insertar_user(
  2  p_id number, 
  3  p_name varchar2
  4  )
  5  is
  6  begin
  7  insert into people(id,name)
  8  values (p_id, p_name);
  9  end;
 10  /

Procedure created.
SQL> begin
  2  insertar_user(25, 'Borja');
  3  end;
  4  /

PL/SQL procedure successfully completed.

SQL> select * from people;

	ID NAME
---------- 
	25 Borja

```

</details>

#### Ejecutar procedimiento
```sql
-- Ejecutar procedure
BEGIN
    insertar_user(25, 'Borja');
END;
/

```

## Ver usuarios
```bash
SELECT username FROM dba_users; # Todos users current db
SELECT username FROM all_users; # Usuarios accesibles
SELECT username FROM user_users; # Mi user
```
### Cambiar usuario dentro de sqlplus
```bash
conn worker/worker@localhost:1521/FREEPDB1
conn worker/worker@freepdb1
```
## Ver errores
```bash
# Para procedures
SHOW ERRORS PROCEDURE insertar_user;
# Generalista
show errors;
```