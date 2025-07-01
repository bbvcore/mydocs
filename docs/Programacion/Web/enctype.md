---
title: Tipos de codificación de formularios
---

# &#128228; Enctype en formularios

| Enctype                       | Uso                   | Método   | Descripción                                  |
|------------------------------|-------------------------------|----------|----------------------------------------------|
| `application/x-www-form-urlencoded` (por defecto) | Para formularios normales sin archivos | GET/POST | Datos codificados en la **URL** *(pares clave=valor)* |
| `multipart/form-data`          | Para formularios con archivos       | POST     | Datos en partes según MIME, soporta ficheros       |
| `text/plain`                  | Poco habitual                 | POST     | Información en formato texto plano, no hay codificación       |
