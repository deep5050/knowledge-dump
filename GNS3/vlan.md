![image](https://github.com/deep5050/knowledge-dump/assets/27947066/5084148d-93bb-4e12-bee7-2ac7dc352754)


# Test Network Overview

Explore the test network configuration below, where any device can ping any other device. The PCs on switch1 can even chat with those on switch2.

Before setting VLANs, observe ARP messages on every PC.

Let's choose PC1 and attempt to ping PC3 while monitoring with Wireshark on PC4.

```bash
PC1> ping 192.168.20.20
host (192.168.10.1) not reachable
PC1>
```

Wireshark capture:
![Wireshark Capture](https://github.com/deep5050/knowledge-dump/assets/27947066/1ee7a86c-0875-42ed-ba19-0d21e4bc856d)

Now, ping a machine within the network (PC5).

```bash
PC1> ping 192.168.10.30

84 bytes from 192.168.10.30 icmp_seq=1 ttl=64 time=5.747 ms
84 bytes from 192.168.10.30 icmp_seq=2 ttl=64 time=3.744 ms
84 bytes from 192.168.10.30 icmp_seq=3 ttl=64 time=3.129 ms
84 bytes from 192.168.10.30 icmp_seq=4 ttl=64 time=4.184 ms
84 bytes from 192.168.10.30 icmp_seq=5 ttl=64 time=3.719 ms

PC1>
```

Wireshark capture:
![Wireshark Capture](https://github.com/deep5050/knowledge-dump/assets/27947066/ed713726-1e47-4d47-87f4-c5833ff4a452)

Now, without VLANs, broadcast packets reach every machine.

## Introducing VLANs

Let's configure switch 1 with planned VLANs and repeat the previous tasks.

On switch 1:

```bash
/ # ovs-vsctl set port eth1 tag=10
/ # ovs-vsctl set port eth2 tag=20
/ #
```

On switch 2:

```bash
/ # ovs-vsctl set port eth3 tag=20
/ # ovs-vsctl set port eth4 tag=10
/ # ovs-vsctl set port eth5 tag=20
/ #
```

Now, from PC1, ping PC3 and PC5 and observe the results.

```bash
PC1> ping 192.168.10.30

84 bytes from 192.168.10.30 icmp_seq=1 ttl=64 time=7.163 ms
84 bytes from 192.168.10.30 icmp_seq=2 ttl=64 time=3.390 ms
84 bytes from 192.168.10.30 icmp_seq=3 ttl=64 time=4.092 ms
84 bytes from 192.168.10.30 icmp_seq=4 ttl=64 time=6.130 ms
84 bytes from 192.168.10.30 icmp_seq=5 ttl=64 time=3.611 ms
```

Wireshark capture:
![Wireshark Capture](https://github.com/deep5050/knowledge-dump/assets/27947066/b6daaa34-3fad-4d9e-bcd7-ca49420f4cf7)

Ping another VLAN:

```bash
PC1> ping 192.168.20.10

host (192.168.10.1) not reachable

PC1>
```

Wireshark capture:
![Wireshark Capture](https://github.com/deep5050/knowledge-dump/assets/27947066/7647f49d-f7c1-4966-9c0a-a4fb26e0320f)

Now, capture on a PC on a different VLAN (on PC3).

```bash
PC1> ping 192.168.20.10

host (192.168.10.1) not reachable

PC1>
```

Observe no broadcast packets in the capture:
![Wireshark Capture](https://github.com/deep5050/knowledge-dump/assets/27947066/546e9139-ab1e-4db7-8922-7600fd2de84e)




## Verify the trunk concept


## Extra commands
 
 - clear VLAN tags from interfaces  `ovs-vsctl clear port eth2 tag`
 - remove TRUNK from interfaces `ovs-vsctl clear port eth2 trunck`
