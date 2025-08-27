---
title: Factorial recursivo
---

# Factorial
## LLamadas
factorial(5) → llama factorial(4)
factorial(4) → llama factorial(3)
factorial(3) → llama factorial(2)
factorial(2) → llama factorial(1)
factorial(1) → caso base = 1

## Resolver la pila al llegar a caso base
factorial(2) = 2 * factorial(1) = 2 * 1 = 2
factorial(3) = 3 * factorial(2) = 3 * 2 = 6
factorial(4) = 4 * factorial(3) = 4 * 6 = 24
factorial(5) = 5 * factorial(4) = 5 * 24 = 120

Cada factorial(n) usa el resultado completo del nivel inferior, no solo n-1. Por eso no es simplemente restar 1, sino multiplicar por todo lo que ya se calculó abajo.