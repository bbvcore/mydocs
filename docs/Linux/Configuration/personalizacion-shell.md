---
title: Personalización de la shell 
---
# Personalizacióin de la shell
## Color de la shell


### Código escape ANSII
- **"["** : Marca el inicio de la secuencia
- **"0"**: Especifica el modo, en este caso **reset/normal** *(sin negrita o subrayado)*. Si se quiere cambiar y usar la negrisa poner a **"1"**
- **";"**: Separa parámetros
- **"36"**: Especifica el color del texto
- **"m"**: Finaliza la secuencia e indica que es un comando de formato para el texto.

```bash
#!/bin/bash
AZUL='\033[0;34m'
NC='\033[0m' # Sin color (reset)
echo -e "${AZUL}Este texto es azul${NC}. A partir de aquí el color es el habitual de la terminal"
```

:::tip[Evitar ambiguedades]
Usar ${variable} puede evitar problemas en ciertos contextos sobre el uso, por ejemplo, directo de $variable
:::