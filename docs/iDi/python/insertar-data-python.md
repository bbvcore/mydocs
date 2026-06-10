---
title: Datos random
---
# Insertar data con Python
```python
import random
import time
from datetime import datetime
import pyodbc

# 1. Configuración de la conexión a SQL Server 
sql_conn = pyodbc.connect(
    "DRIVER={ODBC Driver 18 for SQL Server};"
    "SERVER=192.168.10.200;"
    "DATABASE=Runtime;"
    "UID=sa;"
    "PWD=SQLserver_2026;"
    "TrustServerCertificate=yes;"
)
cursor = sql_conn.cursor()

# 2. Configuración de la simulación
TAGS_DE_PRUEBA = ["Sensor_Temperatura_01", "Presion_Bomba_A", "Flujo_Agua_Principal"]
CANTIDAD_A_INSERTAR = 50  # Registros a insertar

print(f"Insertando {CANTIDAD_A_INSERTAR} registros en SQL Server...")

try:
    # Consulta anti inyección SQL
    query = """
    INSERT INTO Runtime.dbo.AnalogLive (
        DateTime, TagName, Value, Quality, QualityDetail, OPCQuality, wwVersion, wwRetrievalMode
    ) VALUES (?, ?, ?, ?, ?, ?, ?, ?)
    """

    # Generación de datos aleatorios 
    datos_a_insertar = []
    for _ in range(CANTIDAD_A_INSERTAR):
        registro = (
            datetime.now(),  # DateTime actual
            random.choice(TAGS_DE_PRUEBA),  # TagName aleatorio
            round(random.uniform(10.0, 95.0), 2),  # Value (Aleatorio)
            192,  # Quality 
            0,  # QualityDetail
            192,  # OPCQuality
            1,  # wwVersion
            "Full"  # wwRetrievalMode
        )
        datos_a_insertar.append(registro)
        # Micro-delay para que las marcas de tiempo varíen
        time.sleep(0.01)

    # Inserción masiva
    cursor.executemany(query, datos_a_insertar)
    sql_conn.commit()

    print("¡Se ha realizado la inserción con éxito en SQL Server!")

except Exception as e:
    sql_conn.rollback()
    print(f"ERROR al insertar datos: {e}")

finally:
    cursor.close()
    sql_conn.close()


```