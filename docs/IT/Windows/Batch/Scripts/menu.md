---
sidebar_position: 2
title: Menus
---
# Menus
## Menu con Set 

```batch
:menu
cls
echo ================
echo      MENU
echo ================
echo "1. Opcion 1"
echo "2. Salir"
echo ================
set /p opt=Escoge una opcion:
if "%opt%"=="1" call :hacer_algo
if "%opt%"=="2" exit
goto menu

:hacer_algo
cls
echo "Haciendo algo"
pause
goto menu
```



## Menu con Choice

:::tip[Modificadores de Choice]
- **c**: *opciones*
- **n**: *ocultar respuesta*
- **m**: *mensaje*
- **goto** *tag (sin puntos)*, **call** *tag (requiere puntos)*
:::

```batch
@echo off
title Menu con Choice
:menu
cls
echo ================
echo      MENU
echo ================
echo 1. Opcion 1
echo 2. Salir
echo ================
choice /c 12 /n /m "Escoge una opción: "

if errorlevel 2 goto salir
if errorlevel 1 goto haceralgo
goto menu

:hacer_algo
cls
echo Haciendo algo...
pause
goto menu

:salir
cls
echo "Saliendo..."
pause
exit
```
