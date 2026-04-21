---
title: Básico
---

# Inskcape
Software open source de diseño vectorial

## Conceptos
En Inkscape se trabaja principalmente con 2 tipos de objetos que se pueden ver iguales pero son diferentes:
1. No geométricos
- Objetos especiales o objetos inteligentes: se corresponden con formas que guardan información sobre el tipo de objeto como el radio, las esquinas... En este caso se sabe si es un circulo o una estrella.
- Trazos: simplemente son una línea con grosor. 

2. Geométricos
- Trayectos (geometría pura): se corresponden a formas que son solo nodos o segmentos. En este caso son solo contornos no se sabe si son un cuadrado o un triángulo.

## Herramientas básicas

## Menú Trayecto
### Conversiones
Aquí es importante convertir los objetos creados en trayecto, al ser trayectos se convierten de objetos editables a objetos formados por nodos.

Otra opción interesante es de trazo a trayecto, es decir de formas abiertas a formas cerradas.

### Dividir
Aquí es importante convertir los objetos creados en trayecto, al ser trayectos se convierten de objetos editables a objetos formados por nodos.

Otra opción interesante es de trazo a trayecto, es decir de formas abiertas a formas cerradas.

#### Ejemplo de uso
| Paso | Acción                      | Detalle                                                                |
| ---- | --------------------------- | ---------------------------------------------------------------------- |
| 1    | Dibujar las formas              | Crear la circunferencia y los rectángulos para generar los huecos      |
| 2    | Convertirlas a trayecto        | Seleccionar todo → `Trayecto > Objeto a trayecto`                       |
| 3    | Unir rectángulos (si son varios) | Seleccionar los rectángulos → `Trayecto > Unión`                        |
| 4    | Revisar el orden correcto              | Asegurar que los rectángulos están **encima** de la circunferencia |
| 5    | Seleccionar los elementos                | Seleccionar la circunferencia y los rectángulos                                |
| 6    | Aplicar el corte               | `Trayecto > División`                                                  |
| 7    | Separar o descombinar las piezas              | `Trayecto > Separar` o `Trayecto > Descombinar`                               |
| 8    | Limpieza                    | Borrar los trozos no necesarios                                      |
