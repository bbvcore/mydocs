---
title: Conceptos y herramientas
---

# Conceptos y herramientas para el hacking ético
## Hacking ético
Es la disciplina que se encarga de comprobar el nivel de seguridad de un determinado sistema o activo, para ello se realizan una serie de pruebas de seguridad *(también denominadas de intrusión o auditorias de HE)*, las cuales son ejecutadas por atacantes externos para comprometer la seguridad y de esta forma detectar las vulnerabilidades presentes en un determinado sistema.

### Actores 
#### Hacker
Un experto en tecnologías que utiliza sus conocimientos técnicos para encontrar y resolver un problema relacionado con la seguridad de la información. Suelen ser técnicos o ingenieros con conocimientos específicos en seguridad de la información.

Descubren errores/fallos de seguridad en sistemas informáticos, aplicativos, dispositivos o infraestructuras tecnológicas que comparten sus descubrimientos con los desarrolladores o en portales públicos ya que son informáticos éticos.

#### Ciberdelicuente / Cibercriminal
También posee amplios conocimientos en materia de seguridad informática pero al contrario que los hackers no son éticos y sí intentan lucrarse mediante la explotación de los fallos detectados.

#### Hacktivista
Es cualquier Hacker ético que utilice sus destrezas técnicas en el ámbito de la seguridad de la información con fines sociales, ecológicos, humanitarios o en defensa de los DDHH.

### Actividades relacionadas
#### Auditorias de hacking ético o test de intrusión
Se realizan para encontrar fallos en un sistema informático con permiso del propietario y se realiza un informe con los fallos de seguridad localizados para que puedan ser solucionados.

#### Incidente de seguridad
Actividad realizada por ciberdelincuentes donde se consigue obtener un beneficio económico de la explotación de una vulnerabilidad.

#### Hacktivismo
Tipo de actividades de hacking ético ejecutadas por un Hacktivista.

## Tipos de redes disponibles en internet
### ClearNet
Es todo el contenido que se encuentra disponible de manera pública en Internet o al que se puede acceder mediante el usuario de una plataforma.

### DeepWeb
Es todo el contenido privado que no se encuentra a disposición del público en general pero que a través de la clearNet puede accederse a ciertos datos contenidos en ella. Como podrían ser las bases de datos de aplicaciones web legítimas, que no están indexadas en la clearNet pero se podría llegar a acceder a ellas.

#### DarkWeb
Redes privadas utilizadas por ciberdelincuentes para ofrecer sus servicios, vender información robada, vulnerabilidades no informadas, venta de sustancias prohibidas, material no autorizado.

## Seguridad de la información VS Seguridad informática
### Seguridad de la información
Esta más orientada a la parte estratégica:
- Análisis de riesgos
- Normativas
- Plan director 

:::tip
**Conjunto de medidas** establecidas por las distintas organizaciones con el fin de **proteger la información** garantizando su **CID** *(confidencialidad, integridad y disponibilidad)*.
:::

#### Principios de la seguridad de la información
Existen 3 principios fundamentales que deben de respetar la gestión de la información. 
- **Confidencialidad**: requiere que la información sea accesible para las personas que estén autorizadas. Su protección se lleva a cabo mediante sistemas de automatización y control para mantener en secreto determinada información o recursos.
- **Integridad**: la información se ha de mantener inalterada ante incidentes o accesos malintencionados, permitiendo solo su moficiación por los medios autorizados.
- **Disponibilidad**: se requiere que el sistema informático se mantenga accesible sin degradación ni interrupción del servicio, permitiendo el acceso a los recursos cuando sea necesario.

### Seguridad informática
Esta más centrado en la parte operacional:
- Configuración segura.
- Técnicas de protección.
- Eventos auditorias.

:::tip
Área de informática orientada a la **protección** de las **infraestructuras**, sean hardware o software y a la **información** que contiene, procesa o transmite.
:::

## Concepto de riesgo y vulnerabilidad
### Riesgo
Es la perdida potencial, daño o destrucción producida en un determinado sistema de información como resultado de la una vulnerabilidad al materializarse las consecuencias de una amenaza.
#### Tipos de riesgo
- **Activo**: en un objeto / recurso de valor de una organización cuya perdida o daño establece un riesgo para dicha organización.
- **Amenaza**: es un evento que puede causar un incidente de seguridad en la organización produciendo un daño en los activos.
- **Vulnerabilidad**: es la debilidad que puede ser explotada mediante una o varias amenazas.

### Valoración de vulnerabilidades
#### Common Vulnerability and Score System (CVSS)
No todas las vulnerabilidades producen el mimso impacto, por ello se utiliza un estándar abierto conocido como **CVSS**. Este sistema fue desarrollado por **FIRST** *(Forum of incident Response and Security Teams)*. Este estándar está actualmente en la versión 3.1 y esta conformado por 3 métricas:
- **Métrica base**: representa las características intrínsecas de la vulnerabilidad a evaluar.
- **Métrica temporal**: representa las características de vulnerabilidad que pueden cambiar a lo largo del tiempo.
- **Métrica de entorno**: representa las características de vulnerabilidad propias del entorno en que ha sido encontrada, adecuándo la criticidad al entorno.

#### Calculadora CVSS
Existen varias calculadoras CVSS para poder realizar el cálculo de criticidad de una vulnerabilidad, obteniendo dos valores:
- Valor: Puntuación de 0-10 de la criticidad valorada.
- Vector CVSS: en un solo vector recoge los valores de cada métrica para calcular la criticidad.

#### Clasificación de vulnerabilidades
##### Dependiendo acceso al componente vulnerable
###### Vulnerabilidad remota
Permite acceder al componente vulnerable de manera remota porque se encuentra expuesto directamente en internet.
###### Vulnerabilidad local
Requiere acceso local al componente vulnerable que puede ser mediante distintas vías:
- El atacante tiene acceso al activo vulnerable.
- El atacanta compromete el acto vulnerable tiene acceso.

###### Dependiendo a quién va dirigida
- 


