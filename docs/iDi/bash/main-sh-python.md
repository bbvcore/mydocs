---
title: Main bash
---
# Main sh con Python
```bash
#!/bin/bash
clear
############################## CABECERA ##############################
echo "*********************************************************"
echo "*               APP de control de datos                *"
echo "*********************************************************"
echo "*      Laboratorio de Ciberseguridad CIUDEN - INCIBE   *"
echo "*********************************************************"
############################## FUNCIONES ##############################
options(){
	echo "*********************************************************";
	echo "*                        Menú APP                       *";
	echo "*********************************************************";
	echo "Opción 1: Insertar datos en el historian";
	echo "Opción 2: Copiar datos del historian a PostgreSQL";
	echo "Opción 3: Postgre SQL";
	echo "Opción 4: Microsoft SQL Server";
	echo "Opción 5: Salir";
}
insertdata(){
	clear
	echo "Inserción de datos en el Historian SQL Server";
	cd /home/postgre/venv/bin
	source activate
	python3 ../../insertar-sqlserver-data.py
}
inserthistorian(){
	clear
	echo "Inserción de datos en Postgre desde Historian SQL Server";
	cd /home/postgre/venv/bin
	source activate
	python3 ../../historian.py
}


postgree(){
	clear
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
	echo "*************************";
	echo "*         TABLAS        *";
	echo "*************************";
	echo "Las tablas en postgre son: sync_control y analog_live";
	echo "*************************";
	echo "*************************";
	echo "* Consultas recurrentes *";
	echo "*************************";
	echo "Ver tabla de sincronización: select * from sync_control";
	echo "Ver tabla analog_live: select * from analog_live";
	echo "Ver último ID  de analog_live: select * from analog_live";
	sudo -i -u  postgres
	psql
}

sqlserver(){
    clear
    # sudo apt update
    # sudo apt install mssql-tools18
    echo "El path por defecto es: /opt/mssql-tools18/bin/sqlcmd";
    /opt/mssql-tools18/bin/sqlcmd -S 192.168.10.200 -U sa -P 'SQLserver_2026' -C
}


############################## MENÚ ##############################
# LOOP del menú
while true;do
	clear
	options # Opciones a escoger 
	read -p "Escoge la opción deseada (1-5):" opc
	case "$opc" in
		1) insertdata;;
		2) inserthistorian;;
	        3) postgree;;
	        4) sqlserver;;
		5) clear
		break;;
		*) echo "Opción no válida";;
	esac
done
```