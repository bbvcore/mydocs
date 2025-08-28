---
title: Conceptos PHP
---
# Conceptos PHP


## Visualización datos
### Con print_r
```php
$persona=[
    "Nombre"=>"Fulanito", 
    "Edad"=>21
];
echo "<pre>";
print_r($persona);
echo "</pre>";
```
### Con var_dump
```php
var_dump($persona);
```


## Arrays
```php
// Array asociativo
$ficha = [
    "Nombre" => "Borja",
    "Perfil" => "Técnico"
];
echo $ficha["Perfil"]."<br>";

// Array con índice numérico
$decimal = [0,1,2,3,4,5,6,7,8,9];
echo $decimal[0];
```
### Iteración de arrays
#### Con for clásico
```php
$matriz = [
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9]
];

for ($i = 0; $i < count($matriz); $i++) {
       for ($j = 0; $j < count($matriz[$i]); $j++) {
        echo "Posición [$i][$j]: " . $matriz[$i][$j] . "<br>";
    }
}
```

#### Con foreach
```php
$bidimensional = array(
    array(1, 2, 3),
    array(4, 5, 6),
    array(7, 8, 9)
);
foreach ($bidimensional as $matriz){
    foreach ($matriz as $key => $value){
        echo "Indice: ".$key.", Valor:".$value."<br>";
    }
}
```


### Métodos de arrays
#### Array_map
```php
$numbers = [0,1,2,3,4,5,6,7,8,9];
// Primer argumento función a aplicar a cada argumento
// Segundo argumento, array sobre el que se aplica
$multip = array_map(fn($n)=> $n *2, $numbers);

```
#### Array_walk
Es similar al foreach
```php
$numeros = [10,20,30];
// Primer argumento array, segundo argumento función
array_walk($numeros, function($fn){
    echo $numeros."\n";
})
```

#### Array_fill
```php
// indice inicial, longitud, valor
$array = array_fill(0,10,0);
print($array);
```
#### Array_merge
```php
array_merge($array_a,$array_b);
```

#### Array_filter
```php
$nums = [10, 20, 30, 40, 50];
$pares = array_filter($nums, fn($n) => $n % 2 === 0);
```

#### Array_reduce
Toma un array y lo reduce a un valor
```php
$nums = [10, 20, 30, 40, 50];
// array, función callback, valor inicial del acumulador
$sum = array_reduce($nums, fn($acum, $n) => $acum + $n, 0);
```


#### Otros métodos
```php
array_keys($array);
array_values($array);
in_array($value, $array);
array_slice($array,$pos_init, $longitud);
array_splice($arr, $pos_init, $longitud, $reemplazo);
```



## Funciones
### Funciones nombradas
```php
function welcome($nombre){
    return "Hola, $nombre";
}
```
### Funciones anónimas (Closures)
```php
$variable = function($nombre){
    return "";
}
echo $variable("Fulanito");
```
:::tip[Use]
Se pueden combinar con use para acceder a variables externas use($variableExterna)
```php
$variable = function($nombre) use($variableExterna) {}
```
:::
### Funciones arrow
Siempre son de una sola línea, no como en JS que permite multilínea.
```php
// Estructura
fn (argumentos) => expresion; 
$mensaje = fn($texto) => "El mensaje es: $texto";
```



### Asignación de argumentos en la declaración de variables
```php
declare(strict_types=1); // Activar el modo estricto
// Parámetros con asignación de valor SIEMPRE al final
function suma (int $a, int $b, int $c = 18) :int {
    return $a+$b+$c;
}
echo suma(5,13);
```