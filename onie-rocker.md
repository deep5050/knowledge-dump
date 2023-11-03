# Simulating a QEMU Device as a Switch with Rocker Configuration
References:
1. https://github.com/scottfeldman/qemu-rocker/blob/rocker/README
2. [Rocker-switchdev-prototyping-vehicle.pdf (netfilter.org)](https://people.netfilter.org/pablo/netdev0.1/papers/Rocker-switchdev-prototyping-vehicle.pdf)


To simulate a QEMU device as a switch, we'll use the `rocker` configuration with QEMU. You can use the provided Python script to generate the QEMU commands. Below is the script:

```python
#!/usr/bin/env python3

import json
import subprocess

def generate_qemu_command(config):
    command = [
        'sudo', 'qemu-system-x86_64',
        '--enable-kvm', '-cpu', 'host',
        '-smp', f'{config["cpu"]}',
        '-m', f'{config["ram"]}',
        '-name', 'onie',
        '-boot', 'order=d,once=d',  # Skipping CD-ROM, always boot from disk
        '-drive', f'file={config["disk"]},media=disk,if=virtio,index=0',
        '-vnc', '0.0.0.0:128',
        '-device', 'virtio-net,netdev=onienet,mac=52:54:00:13:34:1E',  # Management interface assignment
        '-netdev', 'user,id=onienet,hostfwd=tcp::4022-:22',  # Management interface with SSH port forwarding
        '-nographic',
        f'-serial telnet:localhost:{config["telnet_port"]},server',  # Dynamic telnet port
    ]

    num_tap = config['num_tap_interfaces']

    # Generate the rocker len-ports
    partial_command = "-dev rocker,name=sw1"
    len_ports = str(num_tap)
    port_details = ",".join(f"ports[{i}]=dev{i}" for i in range(num_tap))
    tap_command = f"-device rocker,name=sw1,len-ports={len_ports},{port_details}"

    netdev_command = " ".join(f"-netdev tap,id=dev{i},ifname=tap{i+1}" for i in range(num_tap))

    command.append(tap_command)
    command.append(netdev_command)

    return command

def main():
    with open('qemu_config.json', 'r') as config_file:
        config = json.load(config_file)

    qemu_command = generate_qemu_command(config)
    concatenated_string = " ".join(qemu_command)
    print(concatenated_string.strip())
    # subprocess.run(qemu_command)

if __name__ == '__main__':
    main()
```

Here is the configuration file (`qemu_config.json`):

```json
{
    "cpu": 2,
    "ram": 2048,
    "disk": "dent.qcow2",
    "telnet_port": 9500,
    "num_tap_interfaces": 50
}
```

Explanation:
- The script generates QEMU commands based on the provided configuration.
- It specifies CPU, RAM, disk, telnet port, and the number of TAP interfaces for the guest OS.
- TAP interfaces are used to create virtual interfaces for the guest OS.

> Note: This command has been tested on QEMU version 2.11.1.

You can run the script to generate the QEMU command for simulating a QEMU device as a switch with the specified configuration.


## Result (with 4 rocker TAP interfaces)
### HOST OS
Tap interfaces are created on the host system

```bash

tatha@oth-163:~$ ifconfig -a
docker0: flags=4099<UP,BROADCAST,MULTICAST>  mtu 1500
        inet 172.17.0.1  netmask 255.255.0.0  broadcast 172.17.255.255
        inet6 fe80::42:1fff:fe34:cea  prefixlen 64  scopeid 0x20<link>
        ether 02:42:1f:34:0c:ea  txqueuelen 0  (Ethernet)
        RX packets 958048  bytes 50726235 (50.7 MB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 1797781  bytes 2703551051 (2.7 GB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

enp2s0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 192.168.4.48  netmask 255.255.252.0  broadcast 192.168.7.255
        inet6 fe80::9935:12c7:b4be:d328  prefixlen 64  scopeid 0x20<link>
        ether 94:de:80:fe:78:ee  txqueuelen 1000  (Ethernet)
        RX packets 9907098  bytes 12003126999 (12.0 GB)
        RX errors 0  dropped 3691  overruns 0  frame 0
        TX packets 5720158  bytes 1056172469 (1.0 GB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

lo: flags=73<UP,LOOPBACK,RUNNING>  mtu 65536
        inet 127.0.0.1  netmask 255.0.0.0
        inet6 ::1  prefixlen 128  scopeid 0x10<host>
        loop  txqueuelen 1000  (Local Loopback)
        RX packets 3154018  bytes 167235338 (167.2 MB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 3154018  bytes 167235338 (167.2 MB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

tap1: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet6 fe80::10b5:79ff:fe48:c7e8  prefixlen 64  scopeid 0x20<link>
        ether 12:b5:79:48:c7:e8  txqueuelen 1000  (Ethernet)
        RX packets 0  bytes 0 (0.0 B)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 35  bytes 3872 (3.8 KB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

tap2: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet6 fe80::e073:33ff:fe23:c478  prefixlen 64  scopeid 0x20<link>
        ether e2:73:33:23:c4:78  txqueuelen 1000  (Ethernet)
        RX packets 0  bytes 0 (0.0 B)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 34  bytes 3802 (3.8 KB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

tap3: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet6 fe80::68fa:97ff:fecb:943  prefixlen 64  scopeid 0x20<link>
        ether 6a:fa:97:cb:09:43  txqueuelen 1000  (Ethernet)
        RX packets 0  bytes 0 (0.0 B)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 34  bytes 3802 (3.8 KB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

tap4: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet6 fe80::64f7:8cff:fe86:23a6  prefixlen 64  scopeid 0x20<link>
        ether 66:f7:8c:86:23:a6  txqueuelen 1000  (Ethernet)
        RX packets 0  bytes 0 (0.0 B)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 34  bytes 3802 (3.8 KB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0
...

```

### GUEST OS
Example scenario on dent OS (guest) with 4 ports
```bash

root@localhost:~# ifconfig -a
enp0s4nsw1p1: flags=4098<BROADCAST,MULTICAST>  mtu 1500                <----- switch name: sw, port: p1 (mapped with host tap1)
        ether 52:54:00:12:35:01  txqueuelen 1000  (Ethernet)
        RX packets 0  bytes 0 (0.0 B)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 0  bytes 0 (0.0 B)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

enp0s4nsw1p2: flags=4098<BROADCAST,MULTICAST>  mtu 1500               <----- switch name: sw, port: p2 (mapped with host tap2)
        ether 52:54:00:12:35:02  txqueuelen 1000  (Ethernet)
        RX packets 0  bytes 0 (0.0 B)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 0  bytes 0 (0.0 B)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

enp0s4nsw1p3: flags=4098<BROADCAST,MULTICAST>  mtu 1500               <----- switch name: sw, port: p3 (mapped with host tap3)
        ether 52:54:00:12:35:03  txqueuelen 1000  (Ethernet)
        RX packets 0  bytes 0 (0.0 B)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 0  bytes 0 (0.0 B)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

enp0s4nsw1p4: flags=4098<BROADCAST,MULTICAST>  mtu 1500                <----- switch name: sw, port: p4 (mapped with host tap4)
        ether 52:54:00:12:35:04  txqueuelen 1000  (Ethernet)
        RX packets 0  bytes 0 (0.0 B)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 0  bytes 0 (0.0 B)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

ip6tnl0: flags=128<NOARP>  mtu 1452
        unspec 00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00  txqueuelen 1000  (UNSPEC)
        RX packets 0  bytes 0 (0.0 B)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 0  bytes 0 (0.0 B)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

lo: flags=73<UP,LOOPBACK,RUNNING>  mtu 65536
        inet 127.0.0.1  netmask 255.0.0.0
        inet6 ::1  prefixlen 128  scopeid 0x10<host>
        loop  txqueuelen 1000  (Local Loopback)
        RX packets 12  bytes 922 (922.0 B)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 12  bytes 922 (922.0 B)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

ma1: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 10.0.2.15  netmask 255.255.255.0  broadcast 10.0.2.255
        inet6 fe80::5054:ff:fe13:341e  prefixlen 64  scopeid 0x20<link>
        ether 52:54:00:13:34:1e  txqueuelen 1000  (Ethernet)
        RX packets 477  bytes 38512 (37.6 KiB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 479  bytes 37998 (37.1 KiB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0
...

```
