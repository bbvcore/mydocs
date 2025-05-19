---
sidebar_id : 1
title : OPNsense
---
# OPNsense
OPNsense se trata de un firewall/router basado en la distribución FreeBSB. Permite realizar tunneling a través de varios métodos como OpenVPN, WireGuard e IPsec.

:::warning[Descarga]
- <a href="https://opnsense.org/download/">URL Descarga</a>
:::

:::tip[Datos acceso OPNsense]
Las credenciales para usar OPNsense por defecto son:
- User: root
- Password: opnsense
:::

<details>
<summary>
Credenciales para instalar OPNsense
</summary>

Las credenciales para instalar OPNsense son diferentes a las de acceso, de hecho la forma de instalar OPNsense es un poco peculiar comparada con otras ISO en el ecosistema Unix/Linux.

Una vez se llega al menú de login, se ha de hacer login con las sisguientes credenciales:
- **User**: *installer*
- **Contraseña**: *opnsense*

Una vez logueado sale una instalación vía terminal y ofrece unos modos de instalación entre los que destacan los siguientes:
- **UFS**: es el modo Unix File System, más liviano. Para desarrollo.
- **ZFS**: es un modo con una mayor complejidad como el uso de snapshots o verificación de integridad. Para producción.
</details>

## Conceptos seguridad
### Claves
Claves públicas y privadas utilizadas en procesos asimétricos.
### Emisión certificado
Una autoridad de certificación emite un certificado, como en España es por ejemplo la FNMT-RCM, la cual se encarga de comprobar los datos y generar el certificado. Dicho certificado está vinculado a una clave pública.

La clave privada, dentro de un sistema asimétrico, es utilizada para descifrar la información cifrada con clave pública.

