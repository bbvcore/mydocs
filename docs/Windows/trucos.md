---
title: Trucos
---

# Trucos en windows
## Propiedades avanzadas
Acceso rápido a las propiedades avanzadas del sistema a través del siguiente comando desde **Ejecutar**.
```batch
SystemPropertiesAdvanced
```

## Conseguir SIDç
Hay varias opciones, las más comunes son whoami o wmic
### Whoami
```batch

```

### Wmic
```batch
wmic useraccount get SID
```
:::tip[Caso de uso]
```batch
wmic useraccount get AccountType, Name, SID
```
:::