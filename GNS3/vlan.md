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

As we have not introduced trunks on eth0 of both switches all the traffic from switch 1 to switch2 and vice versa happens.
1. let's assign eth0 of both/either switches to carry traffic for VLAN 10 only and see what happens!

```bash
ovs-vsctl set port eth0 trunk=10
```
result 

```bash
.....
Port eth0
            trunks: [10]
            Interface eth0

....
```
2. open a wireshark between two switches
3. Ping from any PC from one switch to another (say PC1 to PC5)

result 

```bash
PC1> ping 192.168.10.30

84 bytes from 192.168.10.30 icmp_seq=1 ttl=64 time=5.619 ms
84 bytes from 192.168.10.30 icmp_seq=2 ttl=64 time=4.237 ms
84 bytes from 192.168.10.30 icmp_seq=3 ttl=64 time=4.213 ms
84 bytes from 192.168.10.30 icmp_seq=4 ttl=64 time=6.439 ms
84 bytes from 192.168.10.30 icmp_seq=5 ttl=64 time=3.220 ms

PC1>
```

![image](https://github.com/deep5050/knowledge-dump/assets/27947066/02ef4eba-e5e9-4010-b958-fd6912b7a1c9)

now ping PC2 to PC3

```bash
PC3> ping 192.168.20.10

host (192.168.20.10) not reachable

```


See!

### Now let us do a small experiment

we assign VLAN #10 only on switch 1 eth0 port, but assign both VLAN #10,#20 on swutch 2 eth0 interface.

on switch 1

```bash
ovs-vsctl set port eth0 trunk=10
```

on switch 2

```bash
ovs-vsctl set port eth= trunk=10,20
```

This should let VLAN #20 packets from Switch 2 but block on Switch 1

let's verify by pinging PC2 from PC3. we should see ARP packets on the trunk line.

```bash
PC3> ping 192.168.20.10

host (192.168.20.10) not reachable
```

![image](https://github.com/deep5050/knowledge-dump/assets/27947066/5f11bb89-6bee-4928-bbe2-daf196865009)

see! the packets come to the switch 1 but it rejects.


## Inspect the packets

One important thing that needs to be cleared is that when a PC sends out a packet it does not know anything about the VLAN. It's a switch's responsibility to put the VLAN info before it passes it to other ends.

below is a side-by-side comparison of an ICMP packet. on the left it's from PC2, on the right side, it is towards switch2 from switch1.

![image](https://github.com/deep5050/knowledge-dump/assets/27947066/ce5a9139-8864-46af-88b8-a68955c8c28d)




## Native VLAN
Let us now understand the concept of native vlan on the below network
---->

PC6 and PC7 are not under any VLAN. let's convert the trunk line to an access line temporarily and see what is the content of the packets while we try to ping pC7 from PC6. we start a Wireshark capture between SW1 and SW2.


on both switches

```bash
ovs-vsctl clear port eth0 trunk
```
----> 

see the ICMP request packets from PC6.

there is no VLAN as usual.


## Extra commands
 
 - clear VLAN tags from interfaces  `ovs-vsctl clear port eth2 tag`
 - remove TRUNK from interfaces `ovs-vsctl clear port eth2 trunk`
