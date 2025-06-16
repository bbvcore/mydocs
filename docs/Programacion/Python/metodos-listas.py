lista = [1,2,3,4]
print("Toda la lista", lista)
lista.append(5) # como push en JS
print("Añadir al final", lista)
lista.pop() # como pop en JS
print("Borrar al final", lista)
lista.pop(0) # como shift en JS
print("Borrar al inicio", lista)
lista.insert(0,-1) # como unshift en JS, 1º argumento donde, 2º valor
print("Añadir al inicio", lista)
lista2 = [10,20,30,40,50] # añade varios al final
lista.extend(lista2)
print("Añadir una lista al final de la lista:", lista)
lista.remove(40) # Eliminar la primera ocurrencia
print(lista)
lista.clear() # Vaciar la lista
print(lista)
