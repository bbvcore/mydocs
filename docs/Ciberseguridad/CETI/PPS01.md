---
title: Puesta en producción segura
---

# Puesta en producción segura
## Lenguajes de programación
### Lenguajes compilados e interpretados
El lenguaje compilado tiene un mejor rendimiento que un lenguaje de programación interpretado, también en los interpretados hay una mayor abstracción y pueden resultar más sencillos. Un programa es un conjunto de secuencia de instrucciones entendible por el ordenador para un objetivo o tarea concreta.

#### Modos de ejecución
:::tip["Modo de ejecución de lenguajes de programación"]
- **Compilado**: *compila a binario*
- **Interpretado**: *leído en tiempo real por un interprete que lo traduce a código máquina (binario)*
- **Intermedio**: *compilado a un lenguaje intermedio ejecutado en máquina virtual*
:::

Existen lenguajes que permiten compilado multiplataforma, como **Golang** donde se escoge la plataforma y arquitectura para la que compilar.

#### Comandos de programa
- Comandos pre-procesamiento (importación de módulos/librerías)
- Funciones
- Declaraciones variables 
- Sentencias & expresiones
- Comentarios.

### Pruebas de software
Son un elemento crítico para garantizar la calidad de un producto de Software, se pueden clasificar en 2 tipos, manuales y automáticas

#### Pruebas manuales
- Pruebas de aceptación: comprobar 
- Pruebas de integración: verifica los módulos 
- Examen de la unidad: valida la unidad de software y su funcionamiento
- Pruebas funcionales: verifica las funciones
- Pruebas de rendimiento: en función de cargas de trabajo.
- Pruebas de regresión: comprueba que si el código agregado rompe el programa
- Pruebas de estrés: prueba la tensión que puede soportar el sistema antes de romper
- Pruebas de usabilidad: válida la usabilidad por parte de un cliente de una aplicación web.

### Evaluación del riesgo de los lenguajes de programación
Para ello se evalua al programador, la tecnología y el volumen de código. Si hubiera que clasificar el lenguaje con más vulnerabilidades sería C, pero no porque sea más inseguro que otros sino por:
- Porque es de los más antiguos y más usados
- Es el lenguaje con mayor volumen de código abierto publicado en la red
- Los sistemas Windows y GNU/Linux usan mucho C

:::tip[Sandbox]
El desarrollo y la prueba de software requiere de un entorno controlado no influenciado por otro software o hardware donde se pueden tener las mismas condiciones. Estos entornos sirven para realizar pruebas de software de funcionalidad y también permiten las pruebas de software malicioso para ver su comportamiento sin entrañar un riesgo.
:::

## Determinación del nivel de seguridad requerido por aplicaciones
En el desarrollo del software existen fundaciones que se interesan por la mejora en la seguridad del software como **OWASP**.

