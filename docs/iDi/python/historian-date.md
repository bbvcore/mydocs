---
title: Script inserción por timestamp
---
# Historian
## Previo
### Permisos
```bash
sudo -u postgres psql -d idi

-- Cambiar el dueño de las tablas al usuario de tu script
ALTER TABLE sync_control_time OWNER TO idi;
ALTER TABLE analog_live_time OWNER TO idi;

-- Por si acaso, asegurar todos los privilegios
GRANT ALL PRIVILEGES ON TABLE sync_control_time TO idi;
GRANT ALL PRIVILEGES ON TABLE analog_live_time TO idi;
```
## Script
```python
import pyodbc
import psycopg2
from psycopg2.extras import execute_batch

# ==========================================
# 1. CONEXIONES (ZONA OT -> DMZ)
# ==========================================

# SQL SERVER (Zona OT - Aveva Historian Runtime)
sql_conn = pyodbc.connect(
    "DRIVER={ODBC Driver 18 for SQL Server};"
    "SERVER=192.168.10.200;"
    "DATABASE=Runtime;"
    "UID=sa;"
    "PWD=SQLserver_2026;"
    "TrustServerCertificate=yes;"
)

# POSTGRESQL (Zona DMZ)
pg_conn = psycopg2.connect(
    host="192.168.10.201",
    database="idi",
    user="idi",
    password="idi"
)

sql_cursor = sql_conn.cursor()
pg_cursor = pg_conn.cursor()

# Configuración de nombres de tablas nuevas
PROCESO = 'analoglive'
TABLA_SQL = 'Runtime.dbo.AnalogLive'
TABLA_PG_DATOS = 'analog_live_time'
TABLA_PG_CONTROL = 'sync_control_time'

# ==========================================
# 2. CONTROL DE EXTRACTORES (TIMESTAMP)
# ==========================================

# Asegurar la existencia de la NUEVA tabla de control
pg_cursor.execute(f"""
CREATE TABLE IF NOT EXISTS {TABLA_PG_CONTROL} (
    process_name TEXT PRIMARY KEY,
    last_datetime TIMESTAMP
)
""")
pg_conn.commit()

# Buscar la fecha de la última transferencia exitosa en la tabla _time
pg_cursor.execute(f"""
SELECT last_datetime FROM {TABLA_PG_CONTROL} WHERE process_name = %s
""", (PROCESO,))
row = pg_cursor.fetchone()

# Si es la primera ejecución, iniciamos en el año 2000
last_datetime = row[0] if row else '2000-01-01 00:00:00'

# ==========================================
# 3. EXTRACCIÓN DESDE SQL SERVER (AVEVA)
# ==========================================

# Extraemos filtrando por DateTime (sin ID)
sql_cursor.execute(f"""
SELECT
    DateTime,
    TagName,
    Value,
    Quality,
    QualityDetail,
    OPCQuality,
    wwVersion,
    wwRetrievalMode
FROM {TABLA_SQL}
WHERE DateTime > '{last_datetime}'
ORDER BY DateTime ASC
""")

rows = sql_cursor.fetchall()

# ==========================================
# 4. TRANSFORMAR & CARGAR EN POSTGRESQL
# ==========================================
if rows:
    # Mapeo de datos (omitiendo la columna ID)
    data = [
        (
            r.DateTime,
            r.TagName,
            r.Value,
            r.Quality,
            r.QualityDetail,
            r.OPCQuality,
            r.wwVersion,
            r.wwRetrievalMode
        )
        for r in rows
    ]

    # Inserción en la NUEVA tabla de datos analógicos
    execute_batch(pg_cursor, f"""
    INSERT INTO {TABLA_PG_DATOS} (
        datetime, tagname, value, quality, qualitydetail, opcquality, wwversion, wwretrievalmode
    )
    VALUES (%s,%s,%s,%s,%s,%s,%s,%s)
    ON CONFLICT (datetime, tagname) DO NOTHING
    """, data)

    # El último registro de la lista contiene la fecha más reciente extraída
    new_last_datetime = rows[-1].DateTime

    # Guardamos la marca de tiempo en la NUEVA tabla de control
    pg_cursor.execute(f"""
    INSERT INTO {TABLA_PG_CONTROL}(process_name, last_datetime)
    VALUES (%s, %s)
    ON CONFLICT (process_name)
    DO UPDATE SET last_datetime = EXCLUDED.last_datetime
    """, (PROCESO, new_last_datetime))

    pg_conn.commit()
    print(f"{len(rows)} registros copiados en {TABLA_PG_DATOS}. Última fecha: {new_last_datetime}")
else:
    print("Sin datos nuevos en el Historian para la tabla de tiempo.")

# Cierre de conexiones
sql_cursor.close()
pg_cursor.close()
sql_conn.close()
pg_conn.close()

```



## Cron
```bash 
crontab -e
# Escoger nano
# minuto hora día-mes  mes día-semana
*/2 * * * * /home/postgre/venv/bin/python3 /home/postgre/historian-time.py 
```

## Comprobación
```
idi=# select * from sync_control_time;
 process_name |       last_datetime        
--------------+----------------------------
 analoglive   | 2026-06-09 12:19:36.512448
(1 row)

idi=# select count(*) from analog_live_time;
 count 
-------
   715
(1 row)

idi=# select * from sync_control_time;
 process_name |       last_datetime        
--------------+----------------------------
 analoglive   | 2026-06-09 12:19:36.512448
(1 row)

idi=# select count(*) from analog_live_time;
 count 
-------
   715
(1 row)

idi=# select * from sync_control_time;
 process_name |       last_datetime        
--------------+----------------------------
 analoglive   | 2026-06-09 12:19:36.512448
(1 row)

idi=# select * from sync_control_time;
 process_name |       last_datetime        
--------------+----------------------------
 analoglive   | 2026-06-09 12:19:36.512448
(1 row)

idi=# select * from sync_control_time;
 process_name |       last_datetime        
--------------+----------------------------
 analoglive   | 2026-06-09 12:19:36.512448
(1 row)

idi=# select * from sync_control_time;
 process_name |       last_datetime        
--------------+----------------------------
 analoglive   | 2026-06-09 12:21:02.870938
(1 row)

idi=# select count(*) from analog_live_time;
 count 
-------
   765
(1 row)


```