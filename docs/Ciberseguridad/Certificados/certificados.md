---
sidebar_position : 1
title : Certificados
---
# Certificados
Están basados en el estándar x.509 y sirven para validar la identidad de un usuario. 

<details>
<summary>
Estructura básica de un certificado
</summary>

- **Versión**: la versión del estándar x.509 utilizada.
- **Número de serie**: generado por la entidad certificadora (CA).
- **Algoritmo de la firma**.
- **Emisor**: la entidad que firma el certificado (CA)
- **Sujeto**: entidad identificada
- **Clave pública**: usada para cifrar
- **Periodo de validez**.
- **Usos permitidos**

</details>


## Firma
Pueden ser autofirmados *(donde el issuer y subject coinciden)* o puede ser firmado por una **CA** *(autoridad certificadora)*, donde se genera una **CSR** *(certificate signing request)* con la clave privada, que se manda a un **CA** *(LetsScript, DigiCert)* y se devuelve un **.crt** firmado por esa **CA**. Se validan mediante la clave pública presente en el certificado.

Sus principales usos son para:
- **Proporcionar autentidad**, constatar el firmante.
- **Mantener la integridad**, evitar que el contenido sea adulterado.
- **Evitar el No Repudio**, no se puede negar la autoría.

### ¿Quién firma los certificados? 
- Autofirmado, como por ejemplo el propio servidor, mediante su propia clave privada. Estos certificados NO son confiables por defecto. Su uso está destinado a entornos de prueba o entornos locales y privados.

- Una autoridad de certificación (CA), que puede ser una autoridad propia o externa.

## Certificado tipo P12/PFX
Es un tipo de **certificado asimétrico** que agrupa tanto el propio **certificado** como la **clave privada**, además de la firma ya que se trata de un tipo de certificado autofirmado.

Se suele usar para la autenticación en clientes (navegador web o aplicaciones), se puede importar y exportar y está protegido por contraseña.