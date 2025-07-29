---
title: Script para Suricata
---

# Script de gestión para Suricata
<details>
<summary>
Código del script para bash
</summary>

```bash
#!/bin/bash

# Declaración de funciones
function interfaces(){
	echo "Lista de las interfaces de red del sistema en ejecución"
	sudo ip -br a
	sleep 1
}
function start(){
	echo "Se procede a inicializar la ejecución del IDS Suricata en la interfaz seleccionada. "
	# Comando lanzamiento de Suricata 
	sudo suricata -c /etc/suricata/suricata.yaml -i "$1"
}

function stop(){
	echo "Se procede a finalizar la ejecución del IDS Suricata"
	sudo pkill -f suricata
	sudo kill -9 $(pidof suricata)

}

function test(){
	echo "Comprobación de la configuración del IDS Suricata"
	sudo suricata -T -c /etc/suricata/suricata.yaml 
}



# Loop
## Menú
while true; do
	echo "Menú principal de gestión del IDS Suricata"
	echo "1) Inicializar Suricata"
	echo "2) Detener Suricata"
	echo "3) Comprobar Suricata (Test)"
	echo "0) Salir"
	
		read -p "Escoger una opción: " opt
		case $opt in
			1) 
			interfaces 
			read -p "Introducir la interfaz de escucha: " interface
			start "$interface"
			;;
			2)
			stop
			;;
			
			3)
			test
			;;
			
			0) 
			echo "Saliendo del Script de gestión de Suricata"
			break
			;;
			
			*) 
			echo "Ha escogido una opción que no existe, por favor escoja una opción válida"
			continue
			;;
			
			
			
	esac # Fin Switch
 	echo ""
 done # Fin del Loop
```

</details>