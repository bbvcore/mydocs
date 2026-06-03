---
title: Main bash
---
# Main sh con Python
```bash
#!/bin/bash
echo "************************************";
echo "Script de control de bases de datos";
echo "************************************";

options(){
	echo "*****";
	echo "Menú";
	echo "*****";
	echo "Opción 1: insertar datos en el historian";
	echo "Opción 2: copiar datos del historian a PostgreSQL";
	echo "Opción 3: consultar las tablas de PostgreSQL";
	echo "Opción 4: salir";
}
insertdata(){
	clear
	echo "Inserción de datos en el Historian SQL Server";
	cd venv
	cd bin
	source activate
	python3 ../../insertar-sqlserver-data.py
}
inserthistorian(){
	clear
	echo "Inserción de datos en Postgre desde Historian SQL Server";
	cd venv
	cd bin
	source activate
	python3 ../../historian.py
}
synctable(){
	clear
	echo "Consulta de la tabla de sincronización";
	
}
analogtable(){
	clear
	echo "Consulta la tabla analog";
}

postgree(){

echo "Acceso a PostgreSQL a través del usuario propio postgre";
echo "******************";
echo "Comandos de ayuda";
echo "******************";
echo "Lanzar la aplicación: psql";
echo "\l: lista de todas las bases de datos";
echo "\c <nameDB>: conexión a la base de datos";
echo "\dt lista de las tablas";
echo "\coninfo: información de la conexión actual";
echo "\q: salir";
echo "******************";
echo "Consultas recurrentes";
echo "******************";
echo "Ver tabla de sincronización: select * from syn_control";
echo "Ver tabla analog_live: select * from analog_live";
echo "Ver último ID  de analog_live: select * from analog_live";
sudo -i -u  postgres
psql
}


sqlserver(){
    # sudo apt update
    # sudo apt install mssql-tools18
	echo "El path por defecto es: /opt/mssql-tools18/bin/sqlcmd";
    /opt/mssql-tools18/bin/sqlcmd -S 192.168.10.200 -U sa -P 'SQLserver_2026' -C
}

# LOOP del menú
while true;do
	options # Opciones a escoger 
	read -p "Escoge la opción deseada (1-4):" opc
	case "$opc" in
		1) insertdata;;
		2) inserthistorian;;
		2) synctable;;
		3) analogtable;;
        4) postgree;;
        5) sqlserver;;
		6) break;;
		*) echo "Opción no válida";;
	esac
done
```