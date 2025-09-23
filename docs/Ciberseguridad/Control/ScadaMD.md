---
title: Aveva
---

# AVEVA
Se trata de un software industrial basado en **Wonderware** *(InTouch HMI)* que dispone de 2 modelos de trabajo.

## Estructura APP
:::title
- **Presentación** *(clientes e interfaces)*
- **Lógica de la Aplicación** *(objetos, reglas, procesamiento, ejecución)*
- **Persistencia de datos** *(configuraciones, datos históricos, logs, etc...)*
:::
### Capa de Presentación
En esta capa esta el **Cliente** o interface de usuario *(HMI/SCADA)* que consta de:
1. **InTouch** / Managed InTouch / Intouch OMI, gestión     
2. **OMI ViewApp**, WebClients, dashboards, vistas         
3. **Alarmas** / Tendencias / Web Reports, eventos   

### Capa de Negocio
En esta capa va la lógica, la definición de objetos, ejecución, procesamiento en runtime, reglas y scripts.
1. **ArchestrA Application Server** / *AppEngines* usa "AutomationObjects" que son bombas, sensores, válvulas, etc.            
2. **Galaxia** *(Galaxy Repository)* guarda los templates, modelos y la configuración de objetos   
3. **IDE** *(Integrated Development Environment)* para el diseño, configuración de objetos y despliegue.        
4. **Servicios de comunicación** con dispositivos PLC, OPC, etc. 

### Capa de persistencia y datos
1. **Galaxy Repository** *(base de datos SQL)* almacena los modelos, templates, objetos y la configuración global                  
2. **Historian** para los históricos, los volumenes, los registros de alarmas...
3. **Bases de datos** de alarmas, logs, etc...


## Interacción entre los componentes
- **Galaxy Repository**: funciona como el almacén central para la configuración: definiciones de objetos‑plantillas, relaciones, propiedades predeterminadas, etc. (modo persistencia).

- **IDE de ArchestrA**: herramienta de desarrollo; aquí defines los objetos, los templates, conectas con PLCs, defines gráficos, alarmas, etc. (capa de aplicación).

- **Application Server / AppEngines**: servidores donde se ejecuta la lógica de esos objetos creados con IDE; gestionan la adquisición de datos, disparo de alarmas, reglas, comunicaciones con PLCs y otros dispositivos (capacidad de aplicación/lógica).

- **Clientes HMI / OMI etc**: son lo que los usuarios ven / interactúan; reciben los datos desde los objetos en los Application Servers, muestran pantallas, gráficos, permiten la interacción operativa (capa de presentación).

- **Historian y otros servicios de datos**: se encargan de guardar datos extensos, históricos, alarmas pasadas, tendencias, análisis; acceso para reportes históricos (persistencia de datos).

- **Servicios de comunicación / OPC / drivers / I/O Servers**: aunque no siempre visibles como una “capa separada”, actúan como puente entre la capa de aplicación (los objetos) y los dispositivos físicos; este componente también contribuye al rendimiento y estructura del sistema.


## InTouch en OMI
Cuando estas en scripts de acción funciona como un objeto raíz (padre) dentro del modelo de objetos de scripting.

InTouch es el espacio de nombres / objeto padre desde el cual cuelgan métodos y propiedades globales.

Los métodos como ShowIn, PlaySound, PrintWindow, etc., cuelgan de ahí.

Cuando escribes InTouch.ShowIn("MiVista"), estás invocando un método global de la aplicación que controla la visualización de ventanas/vistas.
En muchos casos ni siquiera hace falta escribir InTouch. explícitamente, porque el runtime ya asume ese contexto por defecto (igual que window.alert() se puede invocar solo con alert() en un navegador).
Métodos comunes de InTouch

(Se usan con InTouch.<Método> o solo <Método>)

Gestión de ventanas / vistas
| Categoría                | Función                          | Descripción                                                |
| ------------------------ | -------------------------------- | ---------------------------------------------------------- |
| **Gestión de ventanas**  | `Show("WindowName")`             | Abre una ventana.                                          |
|                          | `ShowIn("WindowName", "Target")` | Abre una ventana dentro de un contenedor/frame OMI.        |
|                          | `Hide("WindowName")`             | Oculta una ventana.                                        |
|                          | `Replace("Window1", "Window2")`  | Sustituye una ventana por otra.                            |
| **Gestión de impresión** | `PrintWindow("WindowName")`      | Imprime una ventana.                                       |
|                          | `PrintScreen()`                  | Imprime la pantalla actual.                                |
| **Gestión de alarmas**   | `AckAllAlarms()`                 | Reconoce todas las alarmas visibles.                       |
|                          | `AckAlarm("TagName")`            | Reconoce una alarma de un tag.                             |
| **Gestión de sonido**    | `PlaySound("RutaArchivo.wav")`   | Reproduce un archivo de audio.                             |
|                          | `StopSound()`                    | Detiene el sonido en reproducción.                         |
| **Otros útiles**         | `ShutdownApp()`                  | Cierra la aplicación runtime.                              |
|                          | `StartApp("Programa.exe")`       | Lanza una aplicación externa.                              |
|                          | `LogMessage("Texto")`            | Escribe un mensaje en el log de InTouch (útil para debug). |


🔹 Propiedades globales

| **Propiedad**              | **Ejemplo**                | **Descripción**                                                    |
| -------------------------- | -------------------------- | ------------------------------------------------------------------ |
| `InTouch.CurrentWindow`    | `InTouch.CurrentWindow`    | Devuelve el nombre de la ventana activa.                           |
| `InTouch.ApplicationTitle` | `InTouch.ApplicationTitle` | Obtiene o establece el título de la aplicación.                    |
| `InTouch.Language`         | `InTouch.Language`         | Devuelve el idioma actual de la aplicación (si usa multilenguaje). |
| `InTouch.NodeName`         | `InTouch.NodeName`         | Devuelve el nombre del nodo/máquina donde corre el runtime.        |
| `InTouch.UserName`         | `InTouch.UserName`         | Devuelve el usuario que está logueado en el sistema.               |


🔹 Notas importantes

Muchas funciones que ves en InTouch. también se pueden usar sin el prefijo, porque InTouch es el objeto padre global (igual que window en JS).

En System Platform con OMI, algunas funciones cambian o se amplían (ej. ShowIn cobra más importancia porque se trabaja con layouts y contenedores OMI).

No todo está documentado directamente en el IDE, así que conviene apoyarse en la ayuda de scripting de Wonderware/AVEVA.


| Método                           | Descripción                                  | Ejemplo                              |
| -------------------------------- | -------------------------------------------- | ------------------------------------ |
| `Show("WindowName")`             | Abre una ventana                             | `Show("Tanque1")`                    |
| `ShowIn("WindowName", "Target")` | Abre una ventana dentro de un contenedor OMI | `ShowIn("MotorView", "MainContent")` |
| `Hide("WindowName")`             | Oculta una ventana                           | `Hide("Tanque1")`                    |
| `Replace("Window1", "Window2")`  | Sustituye una ventana por otra               | `Replace("Menu", "MenuNuevo")`       |
| `PrintWindow("WindowName")`      | Imprime una ventana                          | `PrintWindow("Reporte")`             |
| `PrintScreen()`                  | Imprime la pantalla actual                   | `PrintScreen()`                      |
| `AckAllAlarms()`                 | Reconoce todas las alarmas visibles          | `AckAllAlarms()`                     |
| `AckAlarm("TagName")`            | Reconoce la alarma de un tag específico      | `AckAlarm("Motor1.Fail")`            |
| `PlaySound("archivo.wav")`       | Reproduce un archivo de sonido               | `PlaySound("alarma.wav")`            |
| `StopSound()`                    | Detiene el sonido actual                     | `StopSound()`                        |
| `ShutdownApp()`                  | Cierra la aplicación runtime                 | `ShutdownApp()`                      |
| `StartApp("Programa.exe")`       | Lanza un programa externo                    | `StartApp("notepad.exe")`            |
| `LogMessage("Texto")`            | Escribe un mensaje en el log de InTouch      | `LogMessage("Arrancó el Motor1")`    |



| Propiedad                  | Descripción                 | Ejemplo                                      |
| -------------------------- | --------------------------- | -------------------------------------------- |
| `InTouch.CurrentWindow`    | Nombre de la ventana activa | `LogMessage(InTouch.CurrentWindow)`          |
| `InTouch.ApplicationTitle` | Título de la aplicación     | `InTouch.ApplicationTitle = "Planta Sur"`    |
| `InTouch.Language`         | Idioma actual del runtime   | `LogMessage(InTouch.Language)`               |
| `InTouch.NodeName`         | Nombre del nodo/máquina     | `LogMessage(InTouch.NodeName)`               |
| `InTouch.UserName`         | Usuario logueado            | `LogMessage("Usuario: " + InTouch.UserName)` |

{ Abrir ventana en contenedor OMI }
InTouch.ShowIn("TanqueDetail", "MainFrame");

{ Reconocer una alarma de un motor }
InTouch.AckAlarm("Motor1.Fail");

{ Log de diagnóstico }
InTouch.LogMessage("Operador abrió la pantalla de Tanques");






