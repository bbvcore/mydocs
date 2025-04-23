---
sidebar_position: 1
title: Ip
---

# Ip
## Anexo redes [comando ip]
### Comprobaciones de namespaces (espacios de red)
Obtener el UUID con el parámetro **netns** que sirve para averiguar un **network namespace** *(espacio de red aislado, como en la contenerización)*, entonces desde un host se puede interaccionar con estos espacios.
```
ip netns list
```
Ver información de ese de **UUID**.
```
ip netns exec netns-35c7edf0-709c-0cb3-7bd1-216a73b9a29e ip a
```

:::info[Parámetros netns usados]
- **ip netns exec**, comando a ejecutar en un espacio de red.
- **netns-...**, identificador del nombre del espacio.
- **ip a**, el comando a ejecutar dentro del espacio de red.
:::

<details>
<summary>
Resultado de la consulta
</summary>

```
┌─[trabajo@parrot]─[/etc/suricata]
└──╼ $sudo ip netns exec netns-35c7edf0-709c-0cb3-7bd1-216a73b9a29e ip a
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host proto kernel_lo 
       valid_lft forever preferred_lft forever
2: eth0@if5: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc noqueue state UP group default qlen 1000
    link/ether 6e:8f:28:bf:5d:4e brd ff:ff:ff:ff:ff:ff link-netnsid 0
    inet 10.89.0.2/24 brd 10.89.0.255 scope global eth0
       valid_lft forever preferred_lft forever
    inet6 fe80::6c8f:28ff:febf:5d4e/64 scope link proto kernel_ll 
       valid_lft forever preferred_lft forever

```
</details>










