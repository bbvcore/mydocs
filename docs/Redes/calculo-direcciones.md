---
sibebar_position: 1
title: Calcular direcciones IP
---

# Cálculos de redes
A continuación una serie de ejemplos de calculo de direcciones de red y de broadcast, además de indicar si son IPs/redes privadas o públicas.
:::warning
- **Cálculo de direccion de Red**: Aplicación de la **AND** lógica.
- **Dirección de Broadcast**: Aplicación de la **NOT** lógica y después se implementa una **OR** lógica.
:::


## Primer caso
:::note
- **Dirección IP**: 196.34.109.133 
- **Máscara de red**: 255.255.255.128
:::

### Cálculos
#### Dirección de red
```cmd
196.34.109.133 ---> 11000100.00100010.01101101.10000101
255.255.255.128---> 11111111.11111111.11111111.10000000
                    ___________________________________

                    11000100.00100010.01101101.10000000
```

**Solución**: red 196.34.109.128

#### Dirección de broadcast
```cmd
196.34.109.133 ---> 11000100.00100010.01101101.10000101
255.255.255.128(OR)>00000000.00000000.00000000.01111111
		    ___________________________________

		    11000100.00100010.01101101.11111111 
```
**Solución**: 196.34.109.255	

:::tip[Solución]
Clase C, Red Pública.
:::


## Segundo caso
:::note
- **Dirección IP**: 192.168.20.29
- **Máscara de red**: 255.255.255.240
:::

### Cálculos
#### Dirección de red
```cmd
192.168.20.29 ---> 11000100.10101000.00010100.00011101
255.255.255.240 -> 11111111.11111111.11111111.11110000
                   ___________________________________

                   11000100.10101000.00010100.00010000 
```

**Solución dirección de red**: 192.168.20.16

#### Dirección de broadcast
```cmd
192.168.20.29 -----> 11000100.10101000.00010100.00011101
255.255.255.240(OR)> 00000000.00000000.00000000.00001111
                     ___________________________________
                    
                     11000100.10101000.00010100.00011111 
```
**Solución dirección de broadcast**:  192.168.20.31

:::tip[Solución]
Clase C, Red Privada.		
:::



## Tercer caso
:::note
- **Dirección IP**: 192.168.20.12
- **Máscara de red**: 255.255.255.224
:::


### Cálculos
#### Dirección de red
```cmd
192.168.20.12 -----> 11000100.10101000.00010100.00001100
255.255.255.224 ---> 11111111.11111111.11111111.11100000
                     ___________________________________

                     11000100.10101000.00010100.00000000 
```
**Solución dirección de red**: 192.168.20.0

#### Dirección de broadcast
```cmd
192.168.20.12 -----> 11000100.10101000.00010100.00001100
255.255.255.224 ---> 11111111.11111111.11111111.00011111
                     ___________________________________

                     11000100.10101000.00010100.00011111 
```

**Solución dirección de broadcast**: 192.168.20.31

:::tip[Solución]
Clase C, Red Privada.
:::


## Cuarto caso
:::note
- **Dirección de red**: 192.168.20.74
- **Máscara de red**: 255.255.255.192
:::

### Cálculos
#### Dirección de red
```cmd
192.168.20.74 -----> 11000100.10101000.00010100.01001010
255.255.255.192 ---> 11111111.11111111.11111111.11000000
		     ___________________________________

                     11000100.10101000.00010100.01000000 
```

**Solución**: 192.168.20.64

```cmd
192.168.20.74 -----> 11000100.10101000.00010100.01001010	
255.255.255.192 ---> 00000000.00000000.00000000.00111111
                     ___________________________________

		     11000100.10101000.00010100.01111111
```

**Solución**: 192.168.20.127

 
### Quinto caso
```cmd
Dirección IP: 140.190.57.10 
Máscara de red: 255.255.192.0
Dirección de red: 140.190.0.0
Dirección de broadcast: 140.190.63.255
```

### Sexto caso
```cmd
Dirección IP: 140.190.171.19
Máscara de red: 255.255.192.0
Dirección de red: 140.190.128.0
Dirección de broadcast: 140.190.191.255
```
### Septimo caso
```cmd
Dirección IP: 140.190.200.11 
Máscara de red: 255.255.192.0
Dirección de red: 140.190.192.0
Dirección de broadcast: 140.190.255.255
