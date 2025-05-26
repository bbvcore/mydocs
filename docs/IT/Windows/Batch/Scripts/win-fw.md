---
sidebar_position: 1
title: Cortafuegos Windows
---

# Script control FW de Windows
```
@echo off
title Firewall

:menu
cls
echo ================
echo      MENU
echo ================
echo "1. Opcion 1: Apagar cortafuegos"
echo "2. Opcion 2: Encender cortafuegos"
echo "3. Opcion 3: Reiniciar a predeterminado el cortafuegos"
echo "4. Salir"
echo ================
set /p opt=Escoge una opcion:
if "%opt%"=="1" call :apagar_fw
if "%opt%"=="2" call :encender_fw
if "%opt%"=="3" call :predeterminado_fw
if "%opt%"=="4" call :salir
goto menu

:apagar_fw
cls
netsh advfirewall set allprofiles state off
echo "Apagando el cortafuegos"
pause
goto menu

:encender_fw
cls
netsh advfirewall set allprofiles state on
echo "Encender el cortafuegos"
pause
goto menu

:predeterminado_fw
cls
netsh advfirewall reset
echo "Restaurar el cortafuegos a predeterminado"
pause
goto menu


:salir
exit

```