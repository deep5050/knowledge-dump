![image](https://github.com/deep5050/knowledge-dump/assets/27947066/4a57a347-19e8-4452-af5e-7fcfc4e6e426)

Check out the test network above! It's a cool setup where any device can ping any other device. The PCs on switch1 can even chat with those on switch2.

Now, let's spice things up by introducing VLANs. PC1 and PC4 are now BFFs on VLAN #10, while PC2 and PC3 are rocking VLAN #20.
on switch1 

```bash
ovs-vsctl set port eth1 tag=10 #pc1
ovs-vsctl set port eth2 tag=20 #pc2

```
result:

```bash

/ # ovs-vsctl list interface eth1 eth2
_uuid               : 25e203e7-611f-446b-8d76-a1cf7460ee51
admin_state         : up
bfd                 : {}
bfd_status          : {}
cfm_fault           : []
cfm_fault_status    : []
cfm_flap_count      : []
cfm_health          : []
cfm_mpid            : []
cfm_remote_mpids    : []
cfm_remote_opstate  : []
duplex              : full
error               : []
external_ids        : {}
ifindex             : 10
ingress_policing_burst: 0
ingress_policing_kpkts_burst: 0
ingress_policing_kpkts_rate: 0
ingress_policing_rate: 0
lacp_current        : []
link_resets         : 0
link_speed          : 10000000
link_state          : up
lldp                : {}
mac                 : []
mac_in_use          : "0a:17:da:34:45:84"
mtu                 : 1500
mtu_request         : []
name                : eth1
ofport              : 2
ofport_request      : []
options             : {}
other_config        : {}
statistics          : {collisions=0, rx_bytes=3700, rx_crc_err=0, rx_dropped=0, rx_errors=0, rx_frame_err=0, rx_missed_errors=0, rx_multicast_packets=0, rx_over_err=0, rx_packets=47, tx_bytes=7744, tx_dropped=0, tx_errors=0, tx_packets=102}
status              : {driver_name=tun, driver_version="1.6", firmware_version=""}
type                : ""

_uuid               : 728c7c15-0484-4dde-9d17-f0186edd6a76
admin_state         : up
bfd                 : {}
bfd_status          : {}
cfm_fault           : []
cfm_fault_status    : []
cfm_flap_count      : []
cfm_health          : []
cfm_mpid            : []
cfm_remote_mpids    : []
cfm_remote_opstate  : []
duplex              : full
error               : []
external_ids        : {}
ifindex             : 11
ingress_policing_burst: 0
ingress_policing_kpkts_burst: 0
ingress_policing_kpkts_rate: 0
ingress_policing_rate: 0
lacp_current        : []
link_resets         : 0
link_speed          : 10000000
link_state          : up
lldp                : {}
mac                 : []
mac_in_use          : "ea:38:f8:5e:5b:8c"
mtu                 : 1500
mtu_request         : []
name                : eth2
ofport              : 3
ofport_request      : []
options             : {}
other_config        : {}
statistics          : {collisions=0, rx_bytes=1082, rx_crc_err=0, rx_dropped=0, rx_errors=0, rx_frame_err=0, rx_missed_errors=0, rx_multicast_packets=0, rx_over_err=0, rx_packets=13, tx_bytes=7002, tx_dropped=0, tx_errors=0, tx_packets=96}
status              : {driver_name=tun, driver_version="1.6", firmware_version=""}
type                : ""
/ #


```

on switch2 
```bash
ovs-vsctl set port eth3 tag=20
ovs-vsctl set port eth4 tag=10
```

result:

```bash

/ # ovs-vsctl list eth3 eth4
ovs-vsctl: unknown table "eth3"
/ # ovs-vsctl list interfaceeth3 eth4
ovs-vsctl: unknown table "interfaceeth3"
/ # ovs-vsctl list interface eth3 eth4
_uuid               : b51e1640-114f-4d16-8e3c-a1f9b8dd51df
admin_state         : up
bfd                 : {}
bfd_status          : {}
cfm_fault           : []
cfm_fault_status    : []
cfm_flap_count      : []
cfm_health          : []
cfm_mpid            : []
cfm_remote_mpids    : []
cfm_remote_opstate  : []
duplex              : full
error               : []
external_ids        : {}
ifindex             : 28
ingress_policing_burst: 0
ingress_policing_kpkts_burst: 0
ingress_policing_kpkts_rate: 0
ingress_policing_rate: 0
lacp_current        : []
link_resets         : 0
link_speed          : 10000000
link_state          : up
lldp                : {}
mac                 : []
mac_in_use          : "9a:a4:93:bd:de:41"
mtu                 : 1500
mtu_request         : []
name                : eth3
ofport              : 4
ofport_request      : []
options             : {}
other_config        : {}
statistics          : {collisions=0, rx_bytes=430, rx_crc_err=0, rx_dropped=0, rx_errors=0, rx_frame_err=0, rx_missed_errors=0, rx_multicast_packets=0, rx_over_err=0, rx_packets=6, tx_bytes=5242, tx_dropped=0, tx_errors=0, tx_packets=76}
status              : {driver_name=tun, driver_version="1.6", firmware_version=""}
type                : ""

_uuid               : 95dc81e5-bc3d-4372-9585-dedd05f38239
admin_state         : up
bfd                 : {}
bfd_status          : {}
cfm_fault           : []
cfm_fault_status    : []
cfm_flap_count      : []
cfm_health          : []
cfm_mpid            : []
cfm_remote_mpids    : []
cfm_remote_opstate  : []
duplex              : full
error               : []
external_ids        : {}
ifindex             : 29
ingress_policing_burst: 0
ingress_policing_kpkts_burst: 0
ingress_policing_kpkts_rate: 0
ingress_policing_rate: 0
lacp_current        : []
link_resets         : 0
link_speed          : 10000000
link_state          : up
lldp                : {}
mac                 : []
mac_in_use          : "9a:6f:b8:a1:3e:f0"
mtu                 : 1500
mtu_request         : []
name                : eth4
ofport              : 5
ofport_request      : []
options             : {}
other_config        : {}
statistics          : {collisions=0, rx_bytes=528, rx_crc_err=0, rx_dropped=0, rx_errors=0, rx_frame_err=0, rx_missed_errors=0, rx_multicast_packets=0, rx_over_err=0, rx_packets=7, tx_bytes=5410, tx_dropped=0, tx_errors=0, tx_packets=78}
status              : {driver_name=tun, driver_version="1.6", firmware_version=""}
type                : ""
/ #

```


now let us ping other PCs from PC1
```bash
PC1>
PC1>
PC1>
PC1> ping 192.168.10.21 # ping PC4 on VLAN #10 works

84 bytes from 192.168.10.21 icmp_seq=1 ttl=64 time=17.738 ms
84 bytes from 192.168.10.21 icmp_seq=2 ttl=64 time=17.265 ms
^C
PC1> ping 192.168.10.20 # Pc3 on VLAN #20

host (192.168.10.20) not reachable

PC1> ping 192.168.10.11 # PC2 on VLAN #20
host (192.168.10.11) not reachable

PC1>

```

![image](https://github.com/deep5050/knowledge-dump/assets/27947066/b4bd64e6-cd17-479e-b60f-fa7ff44ac32e)
