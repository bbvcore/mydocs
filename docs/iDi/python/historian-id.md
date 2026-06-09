---
title: Historian
---
# Historian
```python
import pyodbc
import psycopg2
from psycopg2.extras import execute_batch

# SQL SERVER
sql_conn = pyodbc.connect(
    "DRIVER={ODBC Driver 18 for SQL Server};"
    "SERVER=192.168.10.200;"
    "DATABASE=Runtime;"
    "UID=sa;"
    "PWD=SQLserver_2026;"
    "TrustServerCertificate=yes;"
)

# POSTGRESQL
pg_conn = psycopg2.connect(
    host="192.168.10.201",
    database="idi",
    user="idi",
    password="idi"
)

sql_cursor = sql_conn.cursor()
pg_cursor = pg_conn.cursor()

# Último ID copiado
pg_cursor.execute("""
CREATE TABLE IF NOT EXISTS sync_control (
    process_name TEXT PRIMARY KEY,
    last_id BIGINT
)
""")
pg_conn.commit()

pg_cursor.execute("""
SELECT last_id
FROM sync_control
WHERE process_name = 'analoglive'
""")

row = pg_cursor.fetchone()

last_id = row[0] if row else 0

# Leer nuevos datos SQL Server
sql_cursor.execute(f"""
SELECT
    ID,
    DateTime,
    TagName,
    Value,
    Quality,
    QualityDetail,
    OPCQuality,
    wwVersion,
    wwRetrievalMode
FROM Runtime.dbo.AnalogLive
WHERE ID > {last_id}
ORDER BY ID
""")

rows = sql_cursor.fetchall()

if rows:

    data = [
        (
            r.ID,
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

    execute_batch(pg_cursor, """
    INSERT INTO analog_live (
        id,
        datetime,
        tagname,
        value,
        quality,
        qualitydetail,
        opcquality,
        wwversion,
        wwretrievalmode
    )
    VALUES (%s,%s,%s,%s,%s,%s,%s,%s,%s)
    ON CONFLICT (id) DO NOTHING
    """, data)

    new_last_id = rows[-1].ID

    pg_cursor.execute("""
    INSERT INTO sync_control(process_name, last_id)
    VALUES ('analoglive', %s)
    ON CONFLICT (process_name)
    DO UPDATE SET last_id = EXCLUDED.last_id
    """, (new_last_id,))

    pg_conn.commit()

    print(f"{len(rows)} registros copiados. Último ID: {new_last_id}")

else:
    print("Sin datos nuevos")

sql_conn.close()
pg_conn.close()

```