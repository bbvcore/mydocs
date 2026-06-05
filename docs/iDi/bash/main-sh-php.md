---
title: Main con Php
---
# Main con php
```php
#!/usr/bin/php
<?php
//===============================================================
// Función menú 
//===============================================================
function menu(){
    echo PHP_EOL; // Salto de línea en CLI
    echo "************************************\n";
    echo "Script de control de bases de datos\n";
    echo "************************************\n";
    echo "1. Insertar datos en el Historian\n";
    echo "2. Copiar datos del Historian a PostgreSQL\n";
    echo "3. PostgreSQL\n";
    echo "4. Microsoft SQL Server\n";
    echo "5. Salir\n";
    echo PHP_EOL;
}

//===============================================================
// Función insertar datos alternativos
//===============================================================
function insertData(){
// Comandos salida sistema: system(terminal, uíltima línea), passthru
// (toda salida por terminal), exec (array), shell_exec(string)
	system('clear'); 
	echo "Inserción de datos en el Historian SQL Server\n";
	$cmd = "bash -c 'source /home/postgre/venv/bin/activate && python3 /home/postgre/insertar-sqlserver-data.py'";
	// Alternativa a bash -c, usar directamente'/home/postgre/venv/bin/python3 /home/postgre/insertar-sqlserver-data.py
	passthru($cmd); 
}

function insertHistorian(){
    system('clear');
    echo "Inserción de datos en Postgre desde Historian SQL Server\n";
    $cmd = "bash -c 'source /home/postgre/venv/bin/activate && python3 /home/postgre/historian.py'";
    passthru($cmd);
}

function postgres(){
    echo "Acceso a PostgreSQL\n";
    echo "******************\n";
    echo "Comandos útiles\n";
    echo "******************\n";
    echo "psql\n";
    echo "\\l\n";
    echo "\\c nombre_bd\n";
    echo "\\dt\n";
    echo "\\conninfo\n";
    echo "\\q\n\n";

    passthru("sudo -iu postgres"); // Funciona
    // pcntl_exec('comando',[argumentos en array]
    // Estec comando permite ejecutar procesos como haría C
    // pero te saca de PHP, el proceso que abre es donde te quedas
    // es decir saldría del script y entonces al salir de psql
    // se volvería a bash y no al script en php
    // ejemplo: pcntl_exec('/usr/bin/sudo',['-iu','postgres'])
    

}

function sqlServer()
{
    echo "Acceso a Microsoft SQL Server\n";

    passthru(
        "/opt/mssql-tools18/bin/sqlcmd " .
        "-S 192.168.10.200 " .
        "-U sa " .
        "-P 'SQLserver_2026' -C"
    );
}

while (true) {

    menu();

    $opc = readline("Escoge la opción deseada (1-5): ");

    switch ($opc) {
        case "1":
            insertData();
            break;

        case "2":
            insertHistorian();
            break;

        case "3":
            postgres();
            break;

        case "4":
            sqlServer();
            break;

        case "5":
            echo "Saliendo...\n";
            exit(0);

        default:
            echo "Opción no válida\n";
    }
}


?>
```