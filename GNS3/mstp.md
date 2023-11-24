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
