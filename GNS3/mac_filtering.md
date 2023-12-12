# MAC address filtering

The test network is below
![image](https://github.com/deep5050/knowledge-dump/assets/27947066/bfcc63d6-615e-456b-97a8-959dd473748f)

Let's block PC2 MAC on SW.

```bash
ovs-ofctl -O OpenFlow13 add-flow br0 priority=100,dl_src=00:50:79:66:68:01,actions=drop
```
try pinging PC2 from PC1

```bash
PC1> ping 192.168.10.20

192.168.10.20 icmp_seq=1 timeout
192.168.10.20 icmp_seq=2 timeout
192.168.10.20 icmp_seq=3 timeout
192.168.10.20 icmp_seq=4 timeout
192.168.10.20 icmp_seq=5 timeout

# pc2 ping fails

PC1>
PC1> ping 192.168.10.30

# PC3 ping succeeded
84 bytes from 192.168.10.30 icmp_seq=1 ttl=64 time=2.671 ms
84 bytes from 192.168.10.30 icmp_seq=2 ttl=64 time=3.495 ms
^C
PC1>

```
also all the traffics from PC2 is blocked

```bash
PC2> ping 192.168.10.10

host (192.168.10.10) not reachable

PC2> ping 192.168.10.30

host (192.168.10.30) not reachable

PC2>


```


