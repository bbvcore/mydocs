---
title: IA
---
# IA
# Qué es la IA?
Se utiliza el termino IA con tanta frecuencia que no se sabe como definir correctamente.
Se podría decir que originalmente eran métodos de búsqueda automática de información, en la actualidad
podemos decir que la IA es una disciplina científica compleja que auna conceptos, problemas y métodos 
de resolución de problemas.

:::tip
La influencia de la ciencia ficción generando personajes robóticos con apariencia humana
también ha generado mucha confusión, además en estos contextos hay personajes buenos y otros
más perversos asociados a este concepto.
:::


## Aplicaciones

### 1. Automoviles autónomos:
- Búsqueda y planificación rutas (optimizar tiempos, ahorro combustible)
- Evitar obstaculos (sistemas visión)

:::tip
Siempre con supervisión humana
:::


### 2. Recomendación de contenidos
- Determinar en base a algoritmos que tienen en cuenta hábitos y gustos de las personas
las preferencias de contenido a mostrar, como en plataformas streaming o prensa.

:::tip
De los algoritmos no suelen desvelarse sus detalles, ya que son normalmente propiedad
intelectual de las empresas. 
:::

#### Problemas
- Burbujas de filtro:
- Cámaras de eco:
- Granjas de troles:
- Fake news:
- Propaganda:

### 3. Tratamiento de imágenes y video
#### Reconocimientos
- Reconocimiento facial
- Organización de fotografías en función de personas que aparecen
- Etiquetado automático
### Generación
- Generación de imágenes o videos
- Modificación de imágenes o videos

:::tip
Con el avance de estás tecnologías es y será fácil ver la creación de videos que hagan casi imposible
diferenciar lo auténtico de lo falso.
:::

## Campos
### Aprendizaje automático
Se puede clasificar como un subcampo de la IA, que es a su vez un subcampo de la informática. Ciertas
partes o con ciertos contenidos de este aprendizaje automático pueden encajar mejor como subcategoría
de matemáticas por estar dentro de la estadística.

El Aprendizaje automático se basa en la mejora de sistemas en la ejecución de una tarea en función
de la acumulación de datos.

Dentro del aprendizaje automático se encuentra el aprendizaje profundo, el cual es un aprendizaje más
complejo matemáticamente y que esta beneficiado por el aumento cualitativo y cuantitativo de la capacidad
de computación de los equipos informáticos.

### Ciencia de datos
Incluye el aprendizaje automático, la estadística, algoritmos, persistencia de datos y desarrollo
de aplicaciones web. Requiere de un conocimiento del campo al que se va a aplicar, como por ejemplo
en los negocios. Y también utiliza IA.

### Robótica
Se encarga de la construcción y programación de robots que pueden llevar a cabo operaciones
en situaciones del mundo real. La robótica puede conjugar los diferentes ámbitos de la IA:
- Visión mediante ordenador
- Reconocimiento del habla
- Procesamiento del lenguaje natural: recuperando información y realizando razonamientos en base
al procesamiento de instrucciones para predecir consecuencias a determinadas acciones.
- Modelado cognitivo y afectivo, para interactuar con seres humanos mediante expresiones que imitan
los sentimientos humanos.

:::[¿Qué es un robot?]
Es una máquina con sensores (sirven para realizar detecciones el entorno) y actuadores (permiten realizar actuaciones en el entorno) que reciben una 
programación para ejecutar unas determinadas acciones
:::

## Filosofía de la IA
### Test de turing
Un interrogador humano mantiene un intercambio escrito con 1 persona y 1 ordenador, si no es capaz de discernir
cuál es cuál se da por superada la prueba al ordenador. Se presupone que en este caso el ordenador alcanzó una inteligencia equiparable a la de los humanos.
### Críticas
Se dice que el test no mide si se es inteligente, sino si se comporta el ordenador como un humano.
### Argumento habitación china
Una persona encerrada en una habitación no sabe chino, y otra persona fuera le puede mandar notas,
la de afuera sabe chino y las notas van en chino. La persona de dentro recibe muchas notas y la de fuera
puede pensar en que está teniendo una conversación, pero eso no significa que el de dentro entienda las notas.

Por ello no es lo mismo la inteligencia que el comportamiento inteligente. Lo que se pretende demostrar es
que la inteligencia no se puede descomponer en instrucciones mecánicas automatizadas. Otro ejemplo sería el coche
autonomo, realiza un comportamiento inteligente en base a su automatización, pero no es inteligencia.
El coche no entiende su entorno ni conduce como lo hace un ser humano, sino que sigue instrucciones de un algoritmo.

Así que en sintesis la cuestión es investigar sobre sistemas útiles para resolver problemas, sin tener 
la preocupación de si son inteligentes o se comportan como si lo fueran.

### Conceptos
IA general: es la IA capaz de enfrentarse a cualquier tarea.
IA estrecha: es la IA capaz de enfrentarse a una tarea.
Actualmente todo es IA estrecha, la general de momento ciencia ficción

IA fuerte: sería una mente inteligente, de nuevo ciencia ficción
IA debil: es un sistema que muestra comportamientos inteligentes pero no son más que ordenadores



# Algoritmos de búsqueda

Muchas problemáticas pueden resolverse con algoritmos de búsqueda, se busca la forma de llegar a un objetivo,
para ello pueden existir diversas formas de resolver un problema y se realiza teniendo en cuenta algún
criterio específico. 

## Importancia de los juegos
Ofrecen un ámbito restringido y práctico para numerosas investigaciones de técnicas de búsqueda y planitificación.
Con información perfecta, se saben las normas de los juegos, el escenario/tablero, los participantes, los elementos
físicos (piezas o cartas) y su configuración...
### Resolución de juegos
#### Árboles de juego (algoritmo minmax)
Los distintos estados de juego se van representando jerarquicamente, en el estado inicial, en la cúspide del árbol
esta el tablero inicial, sin movimientos, y luego bajando un nivel están todos los posibles primeros movimientos.
Cada hipótesis de un movimiento se denomina Nodo. Luego en un tercer nivel estarían los movimientos posibles del otro
jugador como reacción a los del segundo nivel y así hasta el final.

Establecemos valores a los resultados que producen victoria, para jugador A se le asigna un valor máximo +1
y para jugador B un valor mínimo -1, y cuando nadie gana se usa el valor 0 como neutral.

Este proceso se ha de repetir en númerosas ocasisones, desde diferentes enfoques o posiciones que puedan tomar
los jugadores para predecir de antemano quién ganará. Esto se reflejará en el nodo raíz, esto también
parte con la base de que cada jugador va a escoger lo más optimo para ganar.

Una vez determinados los valores se ha de buscar los óptimos.

#### Problemática árboles de juegos
El problema es cuando un árbol puede ser muy extenso y son necesarios un número elevador de nodos, para ello
existen trucos como:
- función de evaluación heurística (heuristica: atajo mental para la indagación o descubrimimiento):
sabiendo la posición del juego y el jugador que va a actuar asigna una puntuación estimada probable,
depende del juego, por ejemplo el ajedrez, se ha de ponderar también el valor de las figuras pq no todas
tienen el mismo impacto e influye en la posibilidad de los movimientos a realizar

:::tip[Alogritmo de profundidad limitada]
Es cuando la heurística se aplica a nodos de X profundidad determinada
:::


# IA en el mundo real
La IA en la actualidad funciona mejor gracias al enfoque de como afronta la incertidumbre, debido a que los
métodos de búsqueda requieren una cantidad de información precisa y determinista que no suele abundar
en los escenarios cotidianos.

:::tip
Los datos erroneos o imprecisos de los sensores se denominan **ruido**
:::

Para trabajar con la incertidumbre se hace uso de la probabilidad, y esta se puede más o menos
cuantificar y en función de esa cuantificación ya se tiene un valor, y los valores se pueden comparar.

Por ello y dada la dificultad de medir las probabilidades es importantísimo los datos, su cantidad y calidad.

Y en este caso la IA no hace nada nuevo, hace lo mismo que un médico o un profesional con información incierta
que ha de tomar decisiones racionales.


:::[ods y frecuencias naturales]
- Los odds ayudan a cuantificar la incertidumbre con probabilidades, por ejmplo 3 a 1, es decir por cada 
3 "algos" sucedera 1 "algo". Es decir 3 para lograr X y 1 para lograr Y.
- Las frecuencias naturales serían convertir el caso de 3:1 en 3/4, es decir usar fracciones.
:::

Se utilizan odd y frecuencias naturales, en vez de porcentajes, porque está demostrado que la gente se confunde
más con los porcentajes, aunque los mátemáticos prefieren porcentajes, por ello ser podría usar 50%

## La regla de Bayes
Sirve para ponderar pruebas contradictorias y ruido. Para ello se usan odds a priori y a posteriori, se calculan
probabilidades de que algo ocurra a priori, en función de ello se calcula los a posteriori, y si
aparece nueva información se vuelve a recalcular los odds a priori.

Ejemplo: 
- Pluvimetria de días anuales: dias lluvia 206, días sin lluvia 159, probabilidades 206:159
- Día nublado: probabilidad lluvia con nubes 9/10, lluvia sin nubes 1/10

:::[Razón de verosimilitud]
Es la división entre la posibilidad de suceder y la posibilidad de no suceder
:::

:::[odds]
Son una relación o razón entre 2 conceptos, casos favorables y desfavorables
:::

- Prior (probabilidad de lluvia) a priori = 206/365
- Prior a posteriori

entonces odds a priori: 206/365 / 159/365 = 206/159
Razón verosimilitud: 9/10 : 1/10 = 9
odds (a posteriori): versolimitud * oddsa priori => 9 * 206/159 = 11.66

Total:
1) Probabilidad a priori a Odds a priori, calculo odds a priori: Los días de lluvia son la probabilidad y sin lluvia tb
entonces lo convierto a ODDS que son otra forma de expresar probabilidad que compara casos favorables con desfavorables.
O prior = P/1-P = (206/365)/ 1 - (206/365) = 206/159 (con mcm y cruzado)

"Se podría decir 206 a 159 de que llueva"

2) Razon de verosimilitud (LR) son odds de evidencia bajo las hipotesis de si llueve o no llueve
9/10 : 1/10 = 9
3) Odds a posteriori (Bayes)
206/159 (O priori) * 9 = 11,66037
4) Odds a posteriori a probabilidad a posteriori 
O post P = 0/1+0 = 1854/159 / 1 + 1854/159 = 0.92 = 92%

| Etapas                         | Qué se representa                 | Fórmulas                      | Resultados  |
| ----------------------------- | ------------------------------ | ---------------------------- | ----------------------- |
| **1. Prob. a priori**         | % de lluvia antes de ver nubes | (P(\text{lluvia}) = 206/365) | 0.5658                  |
| **2. Odds a priori**          | proporción lluvia : no lluvia  | (206/159)                    | 1.2956 : 1              |
| **3. Razón de verosimilitud** | fuerza de la evidencia (nubes) | (9/10 ÷ 1/10 = 9)            | 9                       |
| **4. Odds a posteriori**      | nuevos odds tras ver nubes     | (1.2956 × 9 = 11.66)         | 11.66 : 1               |
| **5. Prob. a posteriori**     | probabilidad actualizada       | (11.66 / (1+11.66))          | 0.9219 (92.2%)          |


1 a 9 de lluvia serían los odds
1/10 de lluvia sería la probabilidad


FRECUENCIAS NATUALES: en estadística tienen que ver con numeros enteros que representan casos concretos, 4 personas
3 ojos castaños y 1 azules. Es la fracción o la proporción.


## Clasificación Bayesiana ingenua
Es una técnica de aprendizaje automático que se puede utilizar para clasificar objetos en 2 o más categorías
y para ello se entrena usando un conjunto de datos de entrenamiento previamente clasificados correctamente.

### Ejemplo correo (spam o no spam)
Se denomina ingenuo porque procesa las palabras de forma independiente y en función de ellas dice si son spam,
si viene con palabra tipo oferta, gratis, puede ser spam y es ingenuo pq al procesarlas independientemente
hace como si no estuvieran relacionadas y pueden estarlo.

A pesar de su ingenuidad suele funcionar bastante bien en la realidad.
