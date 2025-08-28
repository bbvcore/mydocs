---
title: Ficheros Php
---
# Ficheros Php
## Lectura ficheros
### Método con while
```php
// Lectura con método clásico
$file = fopen("bas.txt","r");
echo $file; // Devuelve un recurso del tipo "Resource id #"
while(!feof($file)){
    $line = fgets($file);
    echo $line;
}
fclose($file);
echo "Fichero cerrado<br>";
```

:::tip[Atributos]
- **r**: *read*
- **r+**: *read y write*
- **+w**: *write*
- **+w+**: *write y read*
- **a**: *añade al final*
- **a+**: *leer y añadir*
:::

### Método con función propia
```php
// Leer todo el contenido mediante la función file_get_contents
$content = file_get_contents("bas.txt");
echo $content;
```
