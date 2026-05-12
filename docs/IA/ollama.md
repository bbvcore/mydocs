---
title: Ollama Runtime
---

# Ollama Runtime
## Conceptos básicos
Ollama es una herramienta que permite temer un entorno de ejecución e inferencia de modelos de lenguaje en local, teniendo LLMs en ámbito local aumentando la privacidad de los datos. Ollama es una infraestructura que permite gestionar diferentes modelos: **LLama**, **Mistral**, **Gemma**, **Phi....**
### Ventajas
-	Simplifica el uso de modelos locales: descarga de modelos y ejecución de forma directa.
-	Aumenta la privacidad al ser local: no se envían los datos a servidores remotos.
-	Puede ser offline: no requiere de internet.
-	Control total sobre el modelo: como usarlo y configurarlo.
-	Coste menor: más barato que pagar por consultas, aunque requiere un hardware específico.
-	Permite utilizar diferentes modelos sin montar varias infraestructuras.

### Ollama, Chatbots y Agentes
Un **chatbot** suele responder preguntas, conversar y generar texto mientras que un agente toma acciones, usa **herramientas** *(bases de datos, APIs, etc...)* logrando ser más autónomo. **Ollama** es el motor que ejecuta modelos, un chatbot la interfaz para interaccionar y un agente un sistema autónomo que usa un modelo, herramientas y lógica para actuar.

## Conceptos de los LLM
Para una comprensión correcta de los LLM hay ciertos términos importantes que conocer. Son los siguientes:
-	**Token**: fragmento de caracteres que los modelos utilizan, pueden ser una palabra completa, una silaba o un carácter. Los limites de los modelos se miden en función de los tokens usados.
-	**Embeddings**: conversión de palabras en coordenadas matemáticas.
-	**Attention**: indica al modelo que partes de una frase son más importantes para entender el contexto.
-	**Context Window**: cantidad máxima de tokens que puede tener en consideración a la vez, es decir cuantos tokens puede retener el modelo para no perder el hilo. Se puede sufrir el “lost in the middle”
-	**Sampling**: elección de la siguiente palabra más probable de una lista de candidatas.
-	**Temperature**: sirve para calibrar el nivel de riesgo en el sampling. Una temperatura baja (0.1/0.3) hace que el modelo sea conservador y determinista (más literal) y una temperatura alta (0.7/1.0) hace que el modelo escoja palabras menos probables (más creativo).
-	**Hallucinations**: son las mentiras estadísticas. Es cuando se genera información coherente, pero es falsa, al ser información generada en base a probabilidad y no a una base de datos puede escoger opciones que suenan convincentes.
-	**RAG (retrieval – augmented generation)**: es cuando se conecta el modelo de IA a una fuente externa de datos para evitar alucinar.
-	**Fine-tuning**: es un entrenamiento especializado con un modelo ya entrenado. De esta forma se puede especializar en una temática al modelo.
-	**Quantization**: al ser modelos tremendamente pesados la cuantización permite reducir la precisión de los números, reduciendo los bits, logrando reducciones amplias de espacio a cambio del sacrificio de precisión. De esta forma se pueden ejecutar modelos en hardware más limitado.

## INSTALACIÓN DE OLLAMA
La forma más básica es usarlo directamente desde la terminal, en ese caso la instalación se realizará con el siguiente comando:
```bash
curl -fsSL https://ollama.com/install.sh | sh
```

Y para comprobar la versión del runtime ejecutar el siguiente comando
```bash
ollama –version
```
Depende de la distro y versión de GNU/Linux puede hacer falta instalar zstd.
```bash
  - **Debian/Ubuntu**: sudo apt-get install zstd
  - **RHEL/CentOS/Fedora**: sudo dnf install zstd
  - **Arch**: sudo pacman -S zstd
```

:::[Algoritmo Zstd] 
**Zstd** es un algoritmo de compresión más rápido y eficiente que otros como **gzip**, además de poseer una gran compatibilidad con varios formatos de ficheros. Sus principales ventajas son una mayor velocidad, unas mejores ratios de compresión y un diseño para el manejo de datos.
:::

## Descarga del entorno de ejecución
Dentro de los diferentes modelos el uso de ellos suele ir principalmente en función de su complejidad.


| Categoría | Modelo |
| --- | --- |
| **Muy ligeros** | **llama3.2:3b** |
|  | **pPhi4-mini** |
| **Equilibrados** | **mistral** |
|  | **gemma3** |
| **Más potentes** | **llama3.1:8b** |
|  | **qwen3:8b** |

### Tamaño de los modelos
En función de los parámetros que tiene el modelo, lo cual describe las conexiones aprendidas y la memoria matemática del modelo. A mayor número de parámetros (capacidad, razonamiento) mayor consumo (RAM, VRAM). Los modelos pequeños alucinan más que los grandes. Los modelos 3B pueden funcionar con poca RAM y en portátil, los de 70B necesitan mucha RAM, GPU potente y varias GPUs

#### Memoria requerida
Modelo	RAM 
3B	2 / 4 GB
7B	6 / 8 GB
8B	8 / 10 GB
13B	12 /16 GB
70B	40 / +50 GB

Ollama utiliza normalmente modelos cuantificados, es decir que están comprimidos, compresión del modelo, reducción de la precisión numérica y ahorro de memoria.

Otros factores que pueden hacer que un modelo inferior funcione mejor que otro superior son el datasheet de entrenamiento además de que no todos los parámetros valen igual y hay modelos especializados en determinadas tareas.
### Descarga de modelo
```bash
ollama pull llama3.2:3b
``` 
Lanzamiento del servicio y del servidor
```bash
ollama serve
```

## EJECUCIÓN DE OLLAMA
Consulta desde la terminal
Ollama run llama 3.2:3b
 
### Comandos
```bash
Ollama list # Listar
Ollama rm llama3.2:3b # Borrar
ollama ps # Consular modelos en ejecución
```
#### Lista de modelos disponibles
Desde la siguiente URL se pueden comprobar los modelos disponibles https://ollama.com/library?utm_source=chatgpt.com

### Consulta desde la API
Al lanzar el entorno de ejecución se encuentra también disponible una API en el puerto 11434: http://localhost:11434. Para consumo de esta API desde la interfaz de la terminal se hacen peticiones con Curl

#### Petición con curl
```bash
┌──(user㉿DESKTOP-T6HK311)-[/mnt/c/Users/develop]
└─$ curl http://localhost:11434/api/generate -d '{
  "model": "llama3.2:3b",
  "prompt": "Explica qué es una API REST",
  "stream": false
}'
```


#### Respuesta al Curl
```bash
└─$ curl http://localhost:11434/api/generate -d '{ "model": "llama3.2:3b", "prompt": "Explica qué es una API REST", "stream": false }' {"model":"llama3.2:3b","created_at":"2026-05-11T11:34:01.468203519Z","response":"Introducción a las API REST\n\nUna API (Application Programming Interface) REST (Representational State of Resource) es un conjunto de reglas y protocolos que permiten a diferentes sistemas comunicarse entre sí de manera programática. La API REST es una forma común de diseñar y implementar interfaces de software para intercambiar datos entre diferentes aplicaciones, servidores y dispositivos.\n\nCaracterísticas clave de las API REST\n\nLas API REST tienen varias características clave que las distinguen de otras formas de diseño de interfaces:\n\n* Estilo de comunicación: La API REST utiliza el estilo de comunicación HTTP (HyperText Transfer Protocol) para enviar y recibir datos.\n* Recursos: Las API REST se centran en recursos, como objetos o entidades, que se pueden crear, leer, actualizar y eliminar.\n* Métodos HTTP: Las API REST utilizan los siguientes métodos HTTP:\n * GET: Obtenimiento de un recurso\n * POST: Creación de un nuevo recurso\n * PUT: Actualización de un recurso existente\n * DELETE: Eliminación de un recurso\n* Encabezados HTTP: Las API REST utilizan encabezados HTTP para proporcionar información adicional sobre la solicitud, como el formato del cuerpo y las credenciales de autenticación.\n\nEjemplo de una API REST\n\nConsideremos un ejemplo simple de una API REST que gestiona libros:\n\n* Recursos: Los recursos son los libros.\n* Métodos HTTP:\n * GET /libros: Obtenimiento de todos los libros\n * GET /libros/{id}: Obtenimiento de un libro específico\n * POST /libros: Creación de un nuevo libro\n * PUT /libros/{id}: Actualización de un libro existente\n * DELETE /libros/{id}: Eliminación de un libro\n* Encabezados HTTP:\n * Content-Type: El formato del cuerpo de la solicitud (por ejemplo, application/json)\n * Authorization: Credenciales de autenticación\n\nBeneficios de las API REST\n\nLas API REST ofrecen varios beneficios, incluyendo:\n\n* Flexibilidad: Las API REST pueden ser utilizadas para diseñar interfaces de software que sean flexibles y adaptables a diferentes requisitos.\n* Escalabilidad: Las API REST pueden ser escaladas para manejar un gran volumen de tráfico y datos.\n* Reutilización de código: Las API REST permiten la reutilización de código en diferentes aplicaciones y servidores.\n\nEn resumen, las API REST son una forma común de diseñar y implementar interfaces de software para intercambiar datos entre diferentes aplicaciones, servidores y dispositivos. Ofrecen varias características clave, como el estilo de comunicación HTTP, recursos, métodos HTTP y encabezados HTTP, que les permiten ser flexibles, escalables y reutilizables.","done":true,"done_reason":"stop","context":[128006,9125,128007,271,38766,1303,33025,2696,25,6790,220,2366,18,271,128009,128006,882,128007,271,8193,15677,43388,1560,5203,5446,26487,128009,128006,78191,128007,271,334,1090,4653,22776,264,5252,5446,26487,57277,65194,5446,320,5095,39524,20620,8,26487,320,66843,1697,3314,315,12027,8,1560,653,68593,409,1239,14833,379,11766,437,1744,11810,268,264,46418,89249,46915,2648,9465,45815,409,44992,2068,49602,13,5034,5446,26487,1560,5203,22544,470,25155,409,67581,277,379,4305,277,25066,409,3241,3429,958,66,3042,13884,18224,9465,46418,30540,12712,11,4958,81521,379,58551,25204,382,334,9028,2540,62527,61942,409,5252,5446,26487,57277,44903,5446,26487,47539,86050,93554,61942,1744,5252,1612,287,10529,409,51966,84189,409,84908,409,25066,1473,9,256,3146,14101,18536,409,46915,5840,96618,5034,5446,26487,77161,658,70383,409,46915,5840,10339,320,75046,1199,24078,25590,8,3429,63878,379,94280,18224,627,9,256,3146,3905,49022,96618,16132,5446,26487,513,2960,6713,665,60180,11,8112,75148,297,1218,13910,11,1744,513,41604,48837,11,54238,11,79729,379,49504,627,9,256,3146,44,10515,16790,10339,96618,16132,5446,26487,33272,276,2537,86961,36252,16790,10339,512,262,353,256,1595,3891,45722,4761,2002,16721,409,653,64648,708,198,262,353,256,1595,3019,45722,7948,5840,409,653,29396,64648,708,198,262,353,256,1595,6353,45722,34459,42600,409,653,64648,708,3073,6960,198,262,353,256,1595,14762,45722,43420,258,5840,409,653,64648,708,198,9,256,3146,7560,84578,5670,10339,96618,16132,5446,26487,33272,276,3289,84578,5670,10339,3429,80943,277,35615,1008,63893,15482,1208,96957,11,8112,658,55956,1624,63613,379,5252,4281,8968,645,409,3154,4351,5840,382,334,36,73,31310,409,5203,5446,26487,57277,38275,15295,653,58300,4382,409,5203,5446,26487,1744,13033,42790,73446,1473,9,256,3146,3905,49022,96618,9853,60180,4538,2537,73446,627,9,256,3146,44,10515,16790,10339,334,512,262,353,256,1595,3891,611,2808,3714,45722,4761,2002,16721,409,15887,2537,73446,198,262,353,256,1595,3891,611,2808,3714,9573,307,5658,25,4761,2002,16721,409,653,52111,79020,4042,198,262,353,256,1595,3019,611,2808,3714,45722,7948,5840,409,653,29396,52111,198,262,353,256,1595,6353,611,2808,3714,9573,307,5658,25,34459,42600,409,653,52111,3073,6960,198,262,353,256,1595,14762,611,2808,3714,9573,307,5658,25,43420,258,5840,409,653,52111,198,9,256,3146,7560,84578,5670,10339,334,512,262,353,256,1595,2831,11038,45722,4072,55956,1624,63613,409,1208,96957,320,4406,58300,11,1595,5242,9108,25158,262,353,256,1595,18616,45722,356,1171,8968,645,409,3154,4351,5840,271,334,60076,26414,409,5252,5446,26487,57277,44903,5446,26487,64195,268,74918,4270,26414,11,18916,4168,8862,1473,9,256,3146,32771,57335,96618,16132,5446,26487,41604,1446,33272,11354,3429,67581,277,25066,409,3241,1744,85522,5882,21041,379,39732,33210,264,46418,45682,26675,627,9,256,3146,37221,278,55362,96618,16132,5446,26487,41604,1446,27533,11354,3429,53460,19571,653,16109,63920,268,409,490,95283,379,18224,627,9,256,3146,697,1338,42600,409,45159,96618,16132,5446,26487,11810,268,1208,312,1338,42600,409,45159,665,46418,30540,12712,379,4958,81521,382,1737,594,28999,11,5252,5446,26487,4538,5203,22544,470,25155,409,67581,277,379,4305,277,25066,409,3241,3429,958,66,3042,13884,18224,9465,46418,30540,12712,11,4958,81521,379,58551,25204,13,5046,2827,268,86050,93554,61942,11,8112,658,70383,409,46915,5840,10339,11,60180,11,36252,16790,10339,379,3289,84578,5670,10339,11,1744,3625,11810,268,1446,5882,21041,11,27533,4893,379,312,1338,450,4893,13],"total_duration":27396401024,"load_duration":110639782,"prompt_eval_count":32,"prompt_eval_duration":223060864,"eval_count":664,"eval_duration":26506578843}
```

## AGENTES
Para el entorno de ejecución de **Ollama** se dispone de un agente de Claude Code, que es **OpenClaw** *(orquestador, herramientas y persistencia)*. Con launch se lanza una APP de IA completa, ya que dispone de herramientas para navegar web, ejecución de código, shells, APis, leer ficheros... además de tener persistencia de sesiones, memoria y estado, integraciones con telegram o whatsapp y automatización para planificar, dividir trabajo o ejecutar flujos de trabajo.


### Lanzamiento del agente openclaw
```bash
Ollama launch openclaw
```
En este caso el modelo escogido es **gemma4**, para la ejecución del agente hay que ejecutar el siguiente comando.
```bash
Openclaw onboard
```
#### Medidas de seguridad
```bash
openclaw security audit --deep                                                            
openclaw security audit --fix   
```