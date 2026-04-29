---
title: Leer fichero con PHP
---
# Leer fichero con PHP
```php
<?php
/*
// Todo el fichero, función file_get_contents
$file = file_get_contents("file.txt");
echo $file;
*/

/*
// Leer línea por línea
$file = fopen("file.txt", "r");
if($file){
        while(($line = fgets($file)) !== false){
                echo $line;
        }
        fclose($file);
}
*/

/*
// Leer con array
$file = file("file.txt");
foreach ($file as $linea){
        echo $linea;
}
*/

/*
// Leer caracter a caracter
$file = fopen("file.txt", "r");
while (($char = fgetc($file)) !== false) {
        echo $char;
}
fclose($file);
*/

?>
```
