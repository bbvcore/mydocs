---
sidebar_position : 1
title : certificados
---
# Certificados
Suelen constar de una clave publica, un nombre común (CN), una firma digital y una clave privada.

## Firma
Pueden ser autofirmados *(donde el issuer y subject coinciden)* o puede ser firmado 
por una CA (autoridad certificadora), donde se genera una CSR (certificate signing request) con la clave privada, que se manda a un CA (letsscript, DigiCert) y se devuelve un .crt firmado con ellos.

### ¿Quién firma los certificados? 
- Autofirmado, como por ejemplo el propio servidor 
- Una autoridad de certificación (CA), que puede ser una autoridad propia o externa.

## Certificado tipo P12
Es un tipo de certificado asimétrico que agrupa tanto el propio certificado como la clave privada, además de la firma ya que se trata de un tipo de certificado autofirmado.