![image](https://github.com/deep5050/knowledge-dump/assets/27947066/2a0dfb77-b979-4f29-a59f-ee475c02c7f9)



# Configure switches

I have created a test network to learn MSTP. for this porpose i took 3 openvswitch switches and creared a loop.
now lets see how things work.

Setting an IP address on an Open vSwitch (OVS) is a common task in networking, and it involves configuring the OVS bridge. Here are the steps to set an IP address on an Open vSwitch-based switch:

1. **Identify the OVS Bridge:**
   - Use the `ovs-vsctl` command to list the existing bridges:
     ```bash
     ovs-vsctl show
     ```
   - Identify the bridge you want to configure.

2. **Set IP Address:**
   - Use the `ovs-vsctl` command to set the IP address on the bridge. Replace `BRIDGE_NAME` with the actual name of your bridge, and `IP_ADDRESS/MASK` with the desired IP address and subnet mask:
     ```bash
     ovs-vsctl set Bridge BRIDGE_NAME other_config:hwaddr=MAC_ADDRESS
     ovs-vsctl set Bridge BRIDGE_NAME other_config:datapath-id=DPID
     ovs-vsctl set Bridge BRIDGE_NAME other-config:hwaddr="aa:bb:cc:dd:ee:ff"
     ovs-vsctl set Bridge BRIDGE_NAME other-config:datapath-id="0000ffffffffffff"
     ```

3. **Bring Up the Bridge:**
   - Use the `ifconfig` or `ip` command to bring up the OVS bridge interface and assign the IP address:
     ```bash
     sudo ifconfig BRIDGE_NAME IP_ADDRESS netmask MASK up
     # OR
     sudo ip addr add IP_ADDRESS/MASK dev BRIDGE_NAME
     sudo ip link set dev BRIDGE_NAME up
     ```

4. **Verify Configuration:**
   - Double-check the configuration to ensure the IP address is set correctly:
     ```bash
     ovs-vsctl show
     ifconfig BRIDGE_NAME
     ```

   Make sure the bridge interface now has the assigned IP address.

5. **Persistent Configuration (Optional):**
   - To make the configuration persistent across reboots, you may need to add the relevant commands to your system's startup scripts or use network configuration tools specific to your Linux distribution.

Remember to replace placeholder values such as `BRIDGE_NAME`, `IP_ADDRESS`, `MASK`, `MAC_ADDRESS`, and `DPID` with your actual configuration details. If you encounter any issues or need more specific guidance, feel free to provide additional details about your setup.


## Configure PCs

```bash
ip 192.168.10.10/24 192.168.10.1       # asssign your ip accordingly
ip dns 192.168.10.1                    # assign DNS accordingly
```
verify the settings with the `show` command.

# Configure MSTP on switches
Running Multiple Spanning Tree Protocol (MSTP) on Open vSwitch (OVS) involves configuring the MSTP settings for the bridge. Here are the steps to enable MSTP on Open vSwitch:

1. **Configure MSTP on Open vSwitch:**
   - Use the `ovs-vsctl` command to set the spanning tree protocol for the bridge. Replace `BRIDGE_NAME` with the actual name of your bridge:
     ```bash
     ovs-vsctl set Bridge BRIDGE_NAME stp_enable=true
     ovs-vsctl set Bridge BRIDGE_NAME other_config:stp-config="mode=mstp"
     ```

2. **Set the MSTP Region Configuration:**
   - MSTP divides the network into regions. Set the region name and revision to uniquely identify your MSTP domain. Replace `BRIDGE_NAME`, `REGION_NAME`, and `REVISION_NUMBER` accordingly:
     ```bash
     ovs-vsctl set Bridge BRIDGE_NAME other_config:mstp_config="name=REGION_NAME,revision=REVISION_NUMBER"
     ```
3. **Check status**

```bash
ovs-appctl stp/show BRIDGE_NAME
```

Please replace `BRIDGE_NAME`, `REGION_NAME`, and `REVISION_NUMBER` with your actual bridge name, MSTP region name, and revision number.

Remember that your Open vSwitch version needs to support MSTP for these commands to work correctly.

# A sample result

## Switch 1

```bash
# ovs-appctl stp/show br0
---- br0 ----
Root ID:
  stp-priority  32768
  stp-system-id   aa:bb:cc:dd:ee:ff
  stp-hello-time  2s
  stp-max-age     20s
  stp-fwd-delay   15s
  This bridge is the root

Bridge ID:
  stp-priority  32768
  stp-system-id   aa:bb:cc:dd:ee:ff
  stp-hello-time  2s
  stp-max-age     20s
  stp-fwd-delay   15s

  Interface  Role       State      Cost  Pri.Nbr
  ---------- ---------- ---------- ----- -------
  eth8       designated forwarding 100   128.1
  eth11      designated forwarding 100   128.2
  eth4       designated forwarding 100   128.3
  eth10      designated forwarding 100   128.4
  eth9       designated forwarding 100   128.5
  eth7       designated forwarding 100   128.6
  eth0       designated forwarding 100   128.7
  eth13      designated forwarding 100   128.8
  eth5       designated forwarding 100   128.9
  eth3       designated forwarding 100   128.10
  eth1       designated forwarding 100   128.11
  eth6       designated forwarding 100   128.12
  eth12      designated forwarding 100   128.13
  eth14      designated forwarding 100   128.14
  eth2       designated forwarding 100   128.15
  eth15      designated forwarding 100   128.16

/ #

```

All the ports are "designated" means it's the root switch.

now looks for the alternate path (the path that caused the loop)

## switch 2

```bash
/ # ovs-appctl stp/show br0
---- br0 ----
Root ID:
  stp-priority  32768
  stp-system-id   aa:bb:cc:dd:ee:ff
  stp-hello-time  2s
  stp-max-age     20s
  stp-fwd-delay   15s
  root-port       eth1
  root-path-cost  100

Bridge ID:
  stp-priority  32768
  stp-system-id   ae:e3:d7:3b:e6:44
  stp-hello-time  2s
  stp-max-age     20s
  stp-fwd-delay   15s

  Interface  Role       State      Cost  Pri.Nbr
  ---------- ---------- ---------- ----- -------
  eth8       designated forwarding 100   128.1
  eth11      designated forwarding 100   128.2
  eth4       designated forwarding 100   128.3
  eth10      designated forwarding 100   128.4
  eth9       designated forwarding 100   128.5
  eth7       designated forwarding 100   128.6
  eth0       designated forwarding 100   128.7
  eth13      designated forwarding 100   128.8
  eth5       designated forwarding 100   128.9
  eth1       root       forwarding 100   128.10  <--------------- Port towards the switch 1 (ROOT)
  eth3       designated forwarding 100   128.11
  eth6       designated forwarding 100   128.12
  eth12      designated forwarding 100   128.13
  eth14      designated forwarding 100   128.14
  eth2       designated forwarding 100   128.15
  eth15      designated forwarding 100   128.16

/ #
```

## switch 3

```bash
/ # ovs-appctl stp/show  br0
---- br0 ----
Root ID:
  stp-priority  32768
  stp-system-id   aa:bb:cc:dd:ee:ff
  stp-hello-time  2s
  stp-max-age     20s
  stp-fwd-delay   15s
  root-port       eth0
  root-path-cost  100

Bridge ID:
  stp-priority  32768
  stp-system-id   e2:95:53:91:0c:41
  stp-hello-time  2s
  stp-max-age     20s
  stp-fwd-delay   15s

  Interface  Role       State      Cost  Pri.Nbr
  ---------- ---------- ---------- ----- -------
  eth11      designated forwarding 100   128.1
  eth8       designated forwarding 100   128.2
  eth4       designated forwarding 100   128.3
  eth10      designated forwarding 100   128.4
  eth7       designated forwarding 100   128.5
  eth9       designated forwarding 100   128.6
  eth0       root       forwarding 100   128.7      <--- towards the root bridge (switch1)
  eth13      designated forwarding 100   128.8
  eth5       designated forwarding 100   128.9
  eth1       alternate  blocking   100   128.10     <---- blocking path (towards the switch2)
  eth3       designated forwarding 100   128.11
  eth6       designated forwarding 100   128.12
  eth12      designated forwarding 100   128.13
  eth2       designated forwarding 100   128.14
  eth14      designated forwarding 100   128.15
  eth15      designated forwarding 100   128.16

/ #

# Result

```

![Screenshot 2023-11-24 221136](https://github.com/deep5050/knowledge-dump/assets/27947066/9d7fde2f-d9bb-42c3-b662-744aa317fdfe)




# Let's introduce a redundant path and see

![image](https://github.com/deep5050/knowledge-dump/assets/27947066/534d652d-3b96-48d3-a639-430bc02926b2)

I have introdued two new path ( switch3 <-> switch1, switch1 <-> switch2)

now check the results
## switch 1

```bash
/ # ovs-appctl stp/show
---- br0 ----
Root ID:
  stp-priority  32768
  stp-system-id   aa:bb:cc:dd:ee:ff
  stp-hello-time  2s
  stp-max-age     20s
  stp-fwd-delay   15s
  This bridge is the root                      <----------------------------

Bridge ID:
  stp-priority  32768
  stp-system-id   aa:bb:cc:dd:ee:ff
  stp-hello-time  2s
  stp-max-age     20s
  stp-fwd-delay   15s

  Interface  Role       State      Cost  Pri.Nbr
  ---------- ---------- ---------- ----- -------
  eth8       designated forwarding 100   128.1
  eth11      designated forwarding 100   128.2
  eth4       designated forwarding 100   128.3
  eth10      designated forwarding 100   128.4
  eth9       designated forwarding 100   128.5
  eth7       designated forwarding 100   128.6
  eth0       designated forwarding 100   128.7
  eth13      designated forwarding 100   128.8
  eth5       designated forwarding 100   128.9
  eth3       designated forwarding 100   128.10
  eth1       designated forwarding 100   128.11
  eth6       designated forwarding 100   128.12
  eth12      designated forwarding 100   128.13
  eth14      designated forwarding 100   128.14
  eth2       designated forwarding 100   128.15
  eth15      designated forwarding 100   128.16

```

## Switch 2

```bash
/ # ovs-appctl stp/show
---- br0 ----
Root ID:
  stp-priority  32768
  stp-system-id   aa:bb:cc:dd:ee:ff
  stp-hello-time  2s
  stp-max-age     20s
  stp-fwd-delay   15s
  root-port       eth1
  root-path-cost  100

Bridge ID:
  stp-priority  32768
  stp-system-id   ae:e3:d7:3b:e6:44
  stp-hello-time  2s
  stp-max-age     20s
  stp-fwd-delay   15s

  Interface  Role       State      Cost  Pri.Nbr
  ---------- ---------- ---------- ----- -------
  eth8       designated forwarding 100   128.1
  eth11      designated forwarding 100   128.2
  eth4       designated forwarding 100   128.3
  eth10      designated forwarding 100   128.4
  eth9       designated forwarding 100   128.5
  eth7       designated forwarding 100   128.6
  eth0       designated forwarding 100   128.7
  eth13      designated forwarding 100   128.8
  eth5       designated forwarding 100   128.9
  eth1       root       forwarding 100   128.10
  eth3       alternate  blocking   100   128.11      <--- switch2 <-> switch1
  eth6       designated forwarding 100   128.12
  eth12      designated forwarding 100   128.13
  eth14      designated forwarding 100   128.14
  eth2       designated forwarding 100   128.15
  eth15      designated forwarding 100   128.16

/ #
```


## switch 3

```bash
/ # ovs-appctl stp/show
---- br0 ----
Root ID:
  stp-priority  32768
  stp-system-id   aa:bb:cc:dd:ee:ff
  stp-hello-time  2s
  stp-max-age     20s
  stp-fwd-delay   15s
  root-port       eth0
  root-path-cost  100

Bridge ID:
  stp-priority  32768
  stp-system-id   e2:95:53:91:0c:41
  stp-hello-time  2s
  stp-max-age     20s
  stp-fwd-delay   15s

  Interface  Role       State      Cost  Pri.Nbr
  ---------- ---------- ---------- ----- -------
  eth11      designated forwarding 100   128.1
  eth8       designated forwarding 100   128.2
  eth4       designated forwarding 100   128.3
  eth10      designated forwarding 100   128.4
  eth7       designated forwarding 100   128.5
  eth9       designated forwarding 100   128.6
  eth0       root       forwarding 100   128.7
  eth13      designated forwarding 100   128.8
  eth5       designated forwarding 100   128.9
  eth1       alternate  blocking   100   128.10   <----- switch3 <-> switch2
  eth3       alternate  blocking   100   128.11   < ---- switch3 <-> switch1
  eth6       designated forwarding 100   128.12
  eth12      designated forwarding 100   128.13
  eth2       designated forwarding 100   128.14
  eth14      designated forwarding 100   128.15
  eth15      designated forwarding 100   128.16

/ #

```

![hhhh](https://github.com/deep5050/knowledge-dump/assets/27947066/d51b21d6-c827-4257-8114-d88dced0a1d4)


# Extra

you will get a topology change packet when there is a change

![Screenshot 2023-11-24 225912](https://github.com/deep5050/knowledge-dump/assets/27947066/77b1655c-c2cc-417d-8b28-2510fa7faa0a)

# Introduce link speed to see what happens when MSTP decides the costs

Let's see the current link speed of the connected ports of the switches

## switch 1
```bash


/ #  ovs-ofctl show br0
OFPT_FEATURES_REPLY (xid=0x2): dpid:0000ffffffffffff
n_tables:254, n_buffers:0
capabilities: FLOW_STATS TABLE_STATS PORT_STATS QUEUE_STATS ARP_MATCH_IP
actions: output enqueue set_vlan_vid set_vlan_pcp strip_vlan mod_dl_src mod_dl_dst mod_nw_src mod_nw_dst mod_nw_tos mod_tp_src mod_tp_dst
 1(eth0): addr:4e:ee:1c:a6:77:b7
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 2(eth1): addr:5a:b7:74:ac:d3:49
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 3(eth2): addr:d2:cb:ff:45:eb:35
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 4(eth3): addr:82:e3:cb:bb:a3:0f
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 5(eth4): addr:7a:b2:65:ea:cf:11
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 6(eth5): addr:22:5d:91:96:76:15
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 7(eth6): addr:42:21:cd:87:79:ba
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 8(eth7): addr:ce:2d:f3:ad:82:9c
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 9(eth8): addr:c6:ba:69:f4:f4:db
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 10(eth9): addr:ca:c9:de:91:57:6b
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 11(eth10): addr:de:cd:d6:71:07:12
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 12(eth11): addr:06:38:0b:b2:68:90
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 13(eth12): addr:ba:f4:7d:5d:dc:21
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 14(eth13): addr:1e:1f:81:6e:91:b7
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 15(eth14): addr:2a:7d:01:11:35:50
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 16(eth15): addr:c6:56:d3:46:b8:73
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 LOCAL(br0): addr:aa:bb:cc:dd:ee:ff
     config:     0
     state:      0
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
OFPT_GET_CONFIG_REPLY (xid=0x4): frags=normal miss_send_len=0


```
```bash
/ # cat /sys/class/net/eth4/speed  < --- switch1 <-> swith3
10
/ # cat /sys/class/net/eth6/speed   <--- switch1 <-> switch 2
10
```
## switch 2

```bash

/ # ovs-ofctl show br0
OFPT_FEATURES_REPLY (xid=0x2): dpid:0000aee3d73be644
n_tables:254, n_buffers:0
capabilities: FLOW_STATS TABLE_STATS PORT_STATS QUEUE_STATS ARP_MATCH_IP
actions: output enqueue set_vlan_vid set_vlan_pcp strip_vlan mod_dl_src mod_dl_dst mod_nw_src mod_nw_dst mod_nw_tos mod_tp_src mod_tp_dst
 1(eth0): addr:6a:c4:5d:ef:bb:f5
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 2(eth1): addr:02:4b:0a:d0:d0:4f
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 3(eth2): addr:3a:b0:d9:57:b5:92
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 4(eth3): addr:ce:fc:f1:67:a6:19
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 5(eth4): addr:7e:c9:b1:a8:77:27
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 6(eth5): addr:b2:07:c3:ca:5f:83
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 7(eth6): addr:6e:8a:ad:b9:70:b7
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 8(eth7): addr:6e:e1:50:fc:c7:ca
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 9(eth8): addr:6e:c2:2c:15:e7:4e
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 10(eth9): addr:92:32:0d:73:03:7a
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 11(eth10): addr:76:d4:4e:00:59:fe
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 12(eth11): addr:b2:b2:bc:6a:f4:6b
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 13(eth12): addr:e6:2e:db:29:9e:e5
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 14(eth13): addr:f2:6b:8f:de:c1:52
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 15(eth14): addr:b6:7b:5e:1a:85:e3
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 16(eth15): addr:1e:08:fa:73:8f:44
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 LOCAL(br0): addr:ae:e3:d7:3b:e6:44
     config:     0
     state:      0
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
OFPT_GET_CONFIG_REPLY (xid=0x4): frags=normal miss_send_len=0


```
```bash
/ # cat /sys/class/net/eth3/speed    < ---- swith2 <-> switch1 
10
/ # cat /sys/class/net/eth5/speed  < ---- swith2 <-> switch3
10

```

## switch 3


```bash

/ # ovs-ofctl show br0
OFPT_FEATURES_REPLY (xid=0x2): dpid:0000e29553910c41
n_tables:254, n_buffers:0
capabilities: FLOW_STATS TABLE_STATS PORT_STATS QUEUE_STATS ARP_MATCH_IP
actions: output enqueue set_vlan_vid set_vlan_pcp strip_vlan mod_dl_src mod_dl_dst mod_nw_src mod_nw_dst mod_nw_tos mod_tp_src mod_tp_dst
 1(eth0): addr:1a:29:5b:ab:ef:b9
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 2(eth1): addr:66:a9:99:45:26:94
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 3(eth2): addr:06:bd:bd:78:89:0a
     config:     0
     state:      STP_BLOCK
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 4(eth3): addr:06:12:99:76:18:96
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 5(eth4): addr:0e:9d:6c:e0:d8:51
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 6(eth5): addr:9e:0f:73:15:c6:7d
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 7(eth6): addr:02:a6:d2:59:d7:00
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 8(eth7): addr:6a:fe:ff:dc:58:5c
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 9(eth8): addr:6a:c1:14:76:4e:2c
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 10(eth9): addr:86:a5:34:3e:b5:4a
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 11(eth10): addr:a6:77:56:6a:04:31
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 12(eth11): addr:4a:ee:39:3a:7c:5e
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 13(eth12): addr:9e:85:18:fa:e9:5b
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 14(eth13): addr:fa:5d:a6:8b:e9:7a
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 15(eth14): addr:06:7e:95:da:40:30
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 16(eth15): addr:1e:2b:b4:d6:5b:9c
     config:     0
     state:      STP_FORWARD
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
 LOCAL(br0): addr:e2:95:53:91:0c:41
     config:     0
     state:      0
     current:    10MB-FD COPPER
     speed: 10 Mbps now, 0 Mbps max
OFPT_GET_CONFIG_REPLY (xid=0x4): frags=normal miss_send_len=0
/ #


```

```bash
/ # cat /sys/class/net/eth0/speed  <--- swith3 <-> swith1
10
/ # cat /sys/class/net/eth2/speed   <--- swith3 <-> switch2
10
/ #


```
> ovs-vsctl list Bridge br0
```bash

/ # ovs-vsctl list Interface eth2
_uuid               : 2379b2cd-4e64-4d95-a1d4-a7bb05a7d5e1
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
ifindex             : 43
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
mac_in_use          : "06:bd:bd:78:89:0a"
mtu                 : 1500
mtu_request         : []
name                : eth2
ofport              : 3
ofport_request      : []
options             : {}
other_config        : {}
statistics          : {collisions=0, rx_bytes=95050, rx_crc_err=0, rx_dropped=0, rx_errors=0, rx_frame_err=0, rx_missed_errors=0, rx_multicast_packets=0, rx_over_err=0, rx_packets=1795, tx_bytes=53611, tx_dropped=755, tx_errors=0, tx_packets=1009}
status              : {driver_name=tun, driver_version="1.6", firmware_version=""}
type                : ""
/ #

```

## current topology

1.  swith1 is still the root switch
2.  `eth2` of switch3 is in block mode  (same as the first example)


## Let's now upgrade the `eth2` of switch3 to a 10 Gig link and see what happens

```bash
ovs-vsctl set Interface eth2 link_speed=10000

```


# some other scenario

![image](https://github.com/deep5050/knowledge-dump/assets/27947066/a5480339-f174-4819-82fc-9b606a877a52)

# MSTP regions and revisions

 Now we are gonna take a look at mstp regions. below is the test network
 ![image](https://github.com/deep5050/knowledge-dump/assets/27947066/78ce57aa-8313-42fd-91f4-f6dc4e10c9fc)


 
## Other scenario, modify the cost of a path

consider the below scenario where VLANs are configured. `eth0` of both the switches is configured as a trunk port for (vlan #10,#20)
The other `eth10` port of the two switches is just an access port. 

![image](https://github.com/deep5050/knowledge-dump/assets/27947066/bf6a1a44-f8bf-4b99-8907-6c0a7a5c6865)


Running MSTP on both switches leaves trunk ports to be blocking.

see the side-by-side comparison of the Wireshark capture. (when we try to ping from PC6 which is not on any vlan to any other PC)
 
![image](https://github.com/deep5050/knowledge-dump/assets/27947066/09b9fd8c-871e-45d3-b1e2-9c2c8858b632)

see there are no ARP packets on the right side (block path)!

One important thing to know is that "blocking" does not mean the path is totally deactivated or down. we still can see STP packets on the blocking path.

Now let us manually set the cost of the trunk line to high so that MSTP blocks the access ports instead of the trunk ports.


on switch 1

```bash
/ # ovs-appctl stp/show
---- br0 ----
Root ID:
  stp-priority  32768
  stp-system-id   1e:1f:59:ea:d8:4a
  stp-hello-time  2s
  stp-max-age     20s
  stp-fwd-delay   15s
  This bridge is the root

Bridge ID:
  stp-priority  32768
  stp-system-id   1e:1f:59:ea:d8:4a
  stp-hello-time  2s
  stp-max-age     20s
  stp-fwd-delay   15s

  Interface  Role       State      Cost  Pri.Nbr
  ---------- ---------- ---------- ----- -------
  eth8       designated forwarding 100   128.1
  eth11      designated forwarding 100   128.2
  eth4       designated forwarding 100   128.3
  eth10      designated forwarding 100   128.4
  eth7       designated forwarding 100   128.5
  eth9       designated forwarding 100   128.6
  eth0       designated forwarding 100   128.7
  eth13      designated forwarding 100   128.8
  eth5       designated forwarding 100   128.9
  eth3       designated forwarding 100   128.10
  eth1       designated forwarding 100   128.11
  eth6       designated forwarding 100   128.12
  eth12      designated forwarding 100   128.13
  eth14      designated forwarding 100   128.14
  eth2       designated forwarding 100   128.15
  eth15      designated forwarding 100   128.16



```

on switch 2

```bash
 # ovs-appctl stp/show
---- br0 ----
Root ID:
  stp-priority  32768
  stp-system-id   1e:1f:59:ea:d8:4a
  stp-hello-time  2s
  stp-max-age     20s
  stp-fwd-delay   15s
  root-port       eth10
  root-path-cost  100

Bridge ID:
  stp-priority  32768
  stp-system-id   7a:c3:33:11:c5:44
  stp-hello-time  2s
  stp-max-age     20s
  stp-fwd-delay   15s

  Interface  Role       State      Cost  Pri.Nbr
  ---------- ---------- ---------- ----- -------
  eth11      designated forwarding 100   128.1
  eth8       designated forwarding 100   128.2
  eth4       designated forwarding 100   128.3
  eth10      root       forwarding 100   128.4
  eth7       designated forwarding 100   128.5
  eth9       designated forwarding 100   128.6
  eth0       alternate  blocking   100   128.7      <-- trunk port is blocked
  eth13      designated forwarding 100   128.8
  eth5       designated forwarding 100   128.9
  eth3       designated forwarding 100   128.10
  eth1       designated forwarding 100   128.11
  eth6       designated forwarding 100   128.12
  eth12      designated forwarding 100   128.13
  eth14      designated forwarding 100   128.14
  eth2       designated forwarding 100   128.15
  eth15      designated forwarding 100   128.16


```

## Decrease path cost for the trunk ports

On both switches

```bash
ovs-vsctl set Port eth1 other_config:stp-path-cost=10
```

This command sets a path cost of 10 for the trunk port. Lower path costs are preferred by MSTP.

Let's see the MSTP status on both switches now

on switch 1

```bash
/ # ovs-appctl stp/show
---- br0 ----
Root ID:
  stp-priority  32768
  stp-system-id   1e:1f:59:ea:d8:4a
  stp-hello-time  2s
  stp-max-age     20s
  stp-fwd-delay   15s
  This bridge is the root

Bridge ID:
  stp-priority  32768
  stp-system-id   1e:1f:59:ea:d8:4a
  stp-hello-time  2s
  stp-max-age     20s
  stp-fwd-delay   15s

  Interface  Role       State      Cost  Pri.Nbr
  ---------- ---------- ---------- ----- -------
  eth8       designated forwarding 100   128.1
  eth11      designated forwarding 100   128.2
  eth4       designated forwarding 100   128.3
  eth10      designated forwarding 100   128.4
  eth7       designated forwarding 100   128.5
  eth9       designated forwarding 100   128.6
  eth0       designated forwarding 10    128.7
  eth13      designated forwarding 100   128.8
  eth5       designated forwarding 100   128.9
  eth3       designated forwarding 100   128.10
  eth1       designated forwarding 100   128.11
  eth6       designated forwarding 100   128.12
  eth12      designated forwarding 100   128.13
  eth14      designated forwarding 100   128.14
  eth2       designated forwarding 100   128.15
  eth15      designated forwarding 100   128.16

```
on switch 2

```bash

/ # ovs-appctl stp/show
---- br0 ----
Root ID:
  stp-priority  32768
  stp-system-id   1e:1f:59:ea:d8:4a
  stp-hello-time  2s
  stp-max-age     20s
  stp-fwd-delay   15s
  root-port       eth0
  root-path-cost  10

Bridge ID:
  stp-priority  32768
  stp-system-id   7a:c3:33:11:c5:44
  stp-hello-time  2s
  stp-max-age     20s
  stp-fwd-delay   15s

  Interface  Role       State      Cost  Pri.Nbr
  ---------- ---------- ---------- ----- -------
  eth11      designated forwarding 100   128.1
  eth8       designated forwarding 100   128.2
  eth4       designated forwarding 100   128.3
  eth10      alternate  blocking   100   128.4    <------- access port is blocked
  eth7       designated forwarding 100   128.5
  eth9       designated forwarding 100   128.6
  eth0       root       listening  10    128.7
  eth13      designated forwarding 100   128.8
  eth5       designated forwarding 100   128.9
  eth3       designated forwarding 100   128.10
  eth1       designated forwarding 100   128.11
  eth6       designated forwarding 100   128.12
  eth12      designated forwarding 100   128.13
  eth14      designated forwarding 100   128.14
  eth2       designated forwarding 100   128.15
  eth15      designated forwarding 100   128.16

```

we have successfully managed to influence MSTP to choose the trunk port over the access port!

## Influence MSTP to set a switch as Root

Introducing Priority to a bridge we can select a switch as a root externally!
we choose Switch 2 to be the root bridge, so web run the below command on switch 2 only!

```bash
ovs-vsctl set Bridge br0 other_config:stp-priority=4096

```
This command sets a priority of 4096 for the OVS bridge. Lower priority values make a bridge more likely to be selected as the root bridge.

Now check the MSTP status of switch 1 

```bash
/ # ovs-appctl stp/show
---- br0 ----
Root ID:
  stp-priority  4096
  stp-system-id   7a:c3:33:11:c5:44
  stp-hello-time  2s
  stp-max-age     20s
  stp-fwd-delay   15s
  root-port       eth0
  root-path-cost  10

Bridge ID:
  stp-priority  32768            
  stp-system-id   1e:1f:59:ea:d8:4a
  stp-hello-time  2s
  stp-max-age     20s
  stp-fwd-delay   15s

  Interface  Role       State      Cost  Pri.Nbr
  ---------- ---------- ---------- ----- -------
  eth8       designated forwarding 100   128.1
  eth11      designated forwarding 100   128.2
  eth4       designated forwarding 100   128.3
  eth10      alternate  blocking   100   128.4  <-- access port on block mode
  eth7       designated forwarding 100   128.5
  eth9       designated forwarding 100   128.6
  eth0       root       forwarding 10    128.7  <-- trunk port is active !
  eth13      designated forwarding 100   128.8
  eth5       designated forwarding 100   128.9
  eth3       designated forwarding 100   128.10
  eth1       designated forwarding 100   128.11
  eth6       designated forwarding 100   128.12
  eth12      designated forwarding 100   128.13
  eth14      designated forwarding 100   128.14
  eth2       designated forwarding 100   128.15
  eth15      designated forwarding 100   128.16

```
and the output for switch 2

```bash

/ # ovs-appctl stp/show
---- br0 ----
Root ID:
  stp-priority  4096
  stp-system-id   7a:c3:33:11:c5:44
  stp-hello-time  2s
  stp-max-age     20s
  stp-fwd-delay   15s
  This bridge is the root           <----------- see!!

Bridge ID:
  stp-priority  4096                < -- updated priority
  stp-system-id   7a:c3:33:11:c5:44
  stp-hello-time  2s
  stp-max-age     20s
  stp-fwd-delay   15s

  Interface  Role       State      Cost  Pri.Nbr
  ---------- ---------- ---------- ----- -------
  eth11      designated forwarding 100   128.1
  eth8       designated forwarding 100   128.2
  eth4       designated forwarding 100   128.3
  eth10      designated listening  100   128.4
  eth7       designated forwarding 100   128.5
  eth9       designated forwarding 100   128.6
  eth0       designated forwarding 10    128.7
  eth13      designated forwarding 100   128.8
  eth5       designated forwarding 100   128.9
  eth3       designated forwarding 100   128.10
  eth1       designated forwarding 100   128.11
  eth6       designated forwarding 100   128.12
  eth12      designated forwarding 100   128.13
  eth14      designated forwarding 100   128.14
  eth2       designated forwarding 100   128.15
  eth15      designated forwarding 100   128.16

/ #

```

see the packet info

![image](https://github.com/deep5050/knowledge-dump/assets/27947066/0f3678d6-f329-4351-bd04-af4a43a5315f)


## Influence MSTP to select root bridge with port priority

okay, as per our previous commands access line(eth10) between two switches is blocked because we have assigned a low path cost for the trunk line (eth0). 

now, we  are gonna set the priority of the access ports on both switches in a way that it reverts back to the access port i.e. blocks the trunk line and enables access line on(eth10)

on both switches

```bash
ovs-vsctl set Port eth10 other_config:stp-port-priority=10
```
This command sets a port priority of 128 for the trunk port. Lower port priority values make a port more likely to be selected as the designated port.


Result:


Unfortunately nothing has changed

on switch 1

```bash
/ # ovs-appctl stp/show
---- br0 ----
Root ID:
  stp-priority  4096
  stp-system-id   7a:c3:33:11:c5:44
  stp-hello-time  2s
  stp-max-age     20s
  stp-fwd-delay   15s
  root-port       eth0
  root-path-cost  10

Bridge ID:
  stp-priority  32768
  stp-system-id   1e:1f:59:ea:d8:4a
  stp-hello-time  2s
  stp-max-age     20s
  stp-fwd-delay   15s

  Interface  Role       State      Cost  Pri.Nbr
  ---------- ---------- ---------- ----- -------
  eth8       designated forwarding 100   128.1
  eth11      designated forwarding 100   128.2
  eth4       designated forwarding 100   128.3
  eth10      alternate  blocking   100   10.4     <---- new priority
  eth7       designated forwarding 100   128.5
  eth9       designated forwarding 100   128.6
  eth0       root       forwarding 10    128.7   <---- low cost for trunk line
  eth13      designated forwarding 100   128.8
  eth5       designated forwarding 100   128.9
  eth3       designated forwarding 100   128.10
  eth1       designated forwarding 100   128.11
  eth6       designated forwarding 100   128.12
  eth12      designated forwarding 100   128.13
  eth14      designated forwarding 100   128.14
  eth2       designated forwarding 100   128.15
  eth15      designated forwarding 100   128.16


```
on switch 2

```bash

/ # ovs-appctl stp/show
---- br0 ----
Root ID:
  stp-priority  4096
  stp-system-id   7a:c3:33:11:c5:44
  stp-hello-time  2s
  stp-max-age     20s
  stp-fwd-delay   15s
  This bridge is the root

Bridge ID:
  stp-priority  4096
  stp-system-id   7a:c3:33:11:c5:44
  stp-hello-time  2s
  stp-max-age     20s
  stp-fwd-delay   15s

  Interface  Role       State      Cost  Pri.Nbr
  ---------- ---------- ---------- ----- -------
  eth11      designated forwarding 100   128.1
  eth8       designated forwarding 100   128.2
  eth4       designated forwarding 100   128.3
  eth10      designated forwarding 100   10.4   <----- priority of access port
  eth7       designated forwarding 100   128.5
  eth9       designated forwarding 100   128.6
  eth0       designated forwarding 10    128.7 <---- cost of trunk line
  eth13      designated forwarding 100   128.8
  eth5       designated forwarding 100   128.9
  eth3       designated forwarding 100   128.10
  eth1       designated forwarding 100   128.11
  eth6       designated forwarding 100   128.12
  eth12      designated forwarding 100   128.13
  eth14      designated forwarding 100   128.14
  eth2       designated forwarding 100   128.15
  eth15      designated forwarding 100   128.16

```

now the question is why! **does MSTP give the "cost" greater priority over the "port priority"?**

let's verify.

revert the cost of the trunk ports to 100 again.

on both switches running,

```bash
ovs-vsctl set Port eth0 other_config:stp-path-cost=100
``

and see the results


on switch 1
```bash
/ # ovs-appctl stp/show
---- br0 ----
Root ID:
  stp-priority  4096
  stp-system-id   7a:c3:33:11:c5:44
  stp-hello-time  2s
  stp-max-age     20s
  stp-fwd-delay   15s
  root-port       eth10
  root-path-cost  100

Bridge ID:
  stp-priority  32768
  stp-system-id   1e:1f:59:ea:d8:4a
  stp-hello-time  2s
  stp-max-age     20s
  stp-fwd-delay   15s

  Interface  Role       State      Cost  Pri.Nbr
  ---------- ---------- ---------- ----- -------
  eth8       designated forwarding 100   128.1
  eth11      designated forwarding 100   128.2
  eth4       designated forwarding 100   128.3
  eth10      root       forwarding 100   10.4   <-- access line is active now!! hurray!!
  eth7       designated forwarding 100   128.5
  eth9       designated forwarding 100   128.6
  eth0       alternate  blocking   100   128.7   <---- trunk line blocked
  eth13      designated forwarding 100   128.8
  eth5       designated forwarding 100   128.9
  eth3       designated forwarding 100   128.10
  eth1       designated forwarding 100   128.11
  eth6       designated forwarding 100   128.12
  eth12      designated forwarding 100   128.13
  eth14      designated forwarding 100   128.14
  eth2       designated forwarding 100   128.15
  eth15      designated forwarding 100   128.16


```


on switch 2

```bash
/ # ovs-appctl stp/show
---- br0 ----
Root ID:
  stp-priority  4096
  stp-system-id   7a:c3:33:11:c5:44
  stp-hello-time  2s
  stp-max-age     20s
  stp-fwd-delay   15s
  This bridge is the root

Bridge ID:
  stp-priority  4096
  stp-system-id   7a:c3:33:11:c5:44
  stp-hello-time  2s
  stp-max-age     20s
  stp-fwd-delay   15s

  Interface  Role       State      Cost  Pri.Nbr
  ---------- ---------- ---------- ----- -------
  eth11      designated forwarding 100   128.1
  eth8       designated forwarding 100   128.2
  eth4       designated forwarding 100   128.3
  eth10      designated forwarding 100   10.4
  eth7       designated forwarding 100   128.5
  eth9       designated forwarding 100   128.6
  eth0       designated forwarding 100   128.7
  eth13      designated forwarding 100   128.8
  eth5       designated forwarding 100   128.9
  eth3       designated forwarding 100   128.10
  eth1       designated forwarding 100   128.11
  eth6       designated forwarding 100   128.12
  eth12      designated forwarding 100   128.13
  eth14      designated forwarding 100   128.14
  eth2       designated forwarding 100   128.15
  eth15      designated forwarding 100   128.16

/ #

```

so yes its verified!





