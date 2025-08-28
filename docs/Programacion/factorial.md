---
title: Factorial recursivo
---

# Factorial
El cálculo del factorial es un caso ideal para probar el concepto de recursividad
## LLamadas
```bash
factorial(5) → llamada a la función factorial(4)
factorial(4) → llama a la función factorial(3)
factorial(3) → llama a la función factorial(2)
factorial(2) → llama a la función factorial(1)
factorial(1) → caso base = 1
```

## Resolver la pila al llegar a caso base
```bash
factorial(2) = 2 * factorial(1) = 2 * 1 = 2
factorial(3) = 3 * factorial(2) = 3 * 2 = 6
factorial(4) = 4 * factorial(3) = 4 * 6 = 24
factorial(5) = 5 * factorial(4) = 5 * 24 = 120
```

Cada **factorial(n)** usa el resultado anterior, no usa solo el valor declarado en el código de **n-1**. Se realiza la **multiplicación** por todo lo previamente calculado