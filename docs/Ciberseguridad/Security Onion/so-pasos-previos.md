---
sidebar_position: 2
title: Pasos Previos
---
# Pasos previos :paw_prints:
**Security Onion** permite realizar diveros tipos de instalaciones y en función de la instalación a realizar el nivel de los requisitos puede oscilar bastante.

## Tipos de instalaciones posibles :pushpin:
 <table>
        <tr>
            <th>Tipo de instalación de SO</th>
            <th>Funcionalidad</th>
        </tr>
        <tr>
            <td>Import</td>
            <td>Se usa para importar o analizar, sin necesidad de sensores, PCAPs y Logs.</td>
        </tr>
        <tr>
            <td>Eval</td>
            <td>Instalación rápida para realizar pruebas.</td>
        </tr>
        <tr>
            <td>Standalone</td>
            <td>Similar a Eval, pero para entornos de producción pequeños.</td>
        </tr>
        <tr>
            <td>Manager</td>
            <td>Nodo central para la administración de la infraestructura y el almacenamiento de datos. No realiza captura tráfico.</td>
        </tr>
        <tr>
            <td>Manager Search</td>
            <td>Manager con capacidad de búsqueda de datos.</td>
        </tr>
        <tr>
            <td>Search Node</td>
            <td>Nodo adicional para mejorar la búsqueda y el almacenamiento de los datos en despliegues grandes.</td>
        </tr>
        <tr>
            <td>Sensor</td>
            <td>Captura el tráfico de red y lo almacena en logs para enviarlos al Manager y poder analizarlos.</td>
        </tr>
        <tr>
            <td>Heavy Node</td>
            <td>Similar a un Sensor, aunque con más capacidad de procesamiento para realizar análisis locales.</td>
        </tr>
        <tr>
            <td>IDH Node</td>
            <td>Para analizar logs y tráfico de red en entornos aislados o de alta seguridad.</td>
        </tr>
        <tr>
            <td>Fleet Node</td>
            <td>Sensor especializado en la gestión de múltiples sensores distribuidos.</td>
        </tr>
        <tr>
            <td>Receiver Node</td>
            <td>Recibe datos y logs de otros sensores. Útil en arquitecturas distribuidas.</td>
        </tr>
    </table>


### Import
Una distribución del tipo **Importación** ejecuta la cantidad mínima de procesos para poder importar ficheros **PCAP** o **EVTX** para analizar. 

### Eval
La distribución de tipo **Evaluación** ejecuta los procesos mínimos de una máquina, por ello sus requisitos son menores a los de una instalación **Standalone** y se ajusta a instalaciones temporales o de bajo presupuesto. No está diseñada para producción, por ello está bien para uso en fase de **desarrollo** e **investigación**.

:::note[Suricata]
**Eval** usa **Suricata** y <u>no ejecuta Logstash o Redis</u> para **economizar** el uso de **memoría RAM**.
:::




## Requisitos en función del tipo de instalación :computer:
<table>
        <tr>
            <th>Node Type</th>
            <th>CPUs</th>
            <th>RAM</th>
            <th>Storage</th>
            <th>NICs</th>
        </tr>
        <tr>
            <td>Import</td>
            <td>2</td>
            <td>4GB</td>
            <td>50GB</td>
            <td>1</td>
        </tr>
        <tr>
            <td>Eval</td>
            <td>4</td>
            <td>8GB</td>
            <td>200GB</td>
            <td>2</td>
        </tr>
        <tr>
            <td>Standalone</td>
            <td>4</td>
            <td>16GB</td>
            <td>200GB</td>
            <td>2</td>
        </tr>
        <tr>
            <td>Manager</td>
            <td>4</td>
            <td>16GB</td>
            <td>200GB</td>
            <td>1</td>
        </tr>
        <tr>
            <td>ManagerSearch</td>
            <td>8</td>
            <td>16GB</td>
            <td>200GB</td>
            <td>1</td>
        </tr>
        <tr>
            <td>Search node</td>
            <td>4</td>
            <td>16GB</td>
            <td>200GB</td>
            <td>1</td>
        </tr>
        <tr>
            <td>Sensor</td>
            <td>4</td>
            <td>12GB</td>
            <td>200GB</td>
            <td>2</td>
        </tr>
        <tr>
            <td>Heavy node</td>
            <td>4</td>
            <td>16GB</td>
            <td>200GB</td>
            <td>2</td>
        </tr>
        <tr>
            <td>IDH node</td>
            <td>2</td>
            <td>1GB</td>
            <td>12GB</td>
            <td>1</td>
        </tr>
        <tr>
            <td>Fleet node</td>
            <td>4</td>
            <td>4GB</td>
            <td>200GB</td>
            <td>1</td>
        </tr>
        <tr>
            <td>Receiver node</td>
            <td>2</td>
            <td>8GB</td>
            <td>200GB</td>
            <td>1</td>
        </tr>
    </table>

