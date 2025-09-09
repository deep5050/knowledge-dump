https://www.networkacademy.io/ccna/spanning-tree/how-stp-works

https://www.networkacademy.io/ccna/spanning-tree/the-spanning-tree-algorithm

## What is STP (Spanning Tree Protocol)?

<img width="1000" height="500" alt="image" src="https://github.com/user-attachments/assets/35e0fef2-a9e6-4a9a-823c-04d5b88418c4" />

> We nedd physical connectivity loop for redundant path and reliability, but need to avoid logical loop, STP solves this !!

**Spanning Tree Protocol (STP)** is a network protocol that ensures a loop-free topology for computer networks. Developed by Dr. Radia Perlman in 1985, STP is used primarily in Ethernet networks to prevent broadcast storms and ensure reliable data transmission.

## Need for STP

The need for STP arises from the inherent characteristics of Ethernet networks, where multiple paths can exist between network devices. While redundancy is beneficial for network reliability, it can also lead to problems such as:

- **Network Loops**: When there are multiple active paths between switches, data packets can circulate endlessly, causing network congestion and making it impossible for devices to communicate effectively.
- **Broadcast Storms**: Continuous looping of broadcast packets can overwhelm the network, leading to degraded performance or complete network failure.
- **Inconsistent Network States**: Without a mechanism to manage multiple paths, different switches may have different views of the network, leading to inconsistent data transmission.

## Problems Solved by STP

STP addresses these issues by:

- **Loop Prevention**: STP identifies and disables redundant paths in the network, ensuring that there is only one active path between any two network devices.
- **Redundancy Management**: While it disables certain paths to prevent loops, **STP allows for backup paths to be available**. **If the primary path fails, STP can re-enable a previously disabled path**, maintaining network connectivity.
- **Dynamic Topology Changes**: STP can **adapt to changes in the network topology**, such as the addition or removal of switches, by recalculating the best paths and reconfiguring the network accordingly.


<img width="759" height="442" alt="image" src="https://github.com/user-attachments/assets/7e059805-75e0-4c64-9cf3-be875b50e3d7" />




## Methodologies in Common Spanning Tree Protocol (STP)

Spanning Tree Protocol (STP) employs several methodologies to ensure a loop-free network topology. These methodologies include the following key concepts and processes:

### 1. Bridge Protocol Data Units (BPDUs)

- **Definition**: BPDUs are messages exchanged between switches to share information about the network topology.
- **Function**: They help in the election of the root bridge and in determining the best paths through the network.

### 2. Root Bridge Election

- **Process**: All switches in the network participate in an election to determine the root bridge, which serves as the central point of reference.
- **Criteria**: The switch with the lowest Bridge ID (a combination of the switch's priority and MAC address) is elected as the root bridge.

### 3. Path Cost Calculation

- **Definition**: Each switch calculates the cost of paths to the root bridge based on the speed of the links.
- **Function**: The path with the lowest cost is selected as the preferred route for data transmission.

### 4. Port Roles

STP assigns different roles to ports on switches to manage traffic effectively:

- **Root Port**: The port on a non-root bridge that has the lowest cost path to the root bridge.
- **Designated Port**: The port on a network segment that has the lowest cost to the root bridge and is responsible for forwarding traffic to and from that segment.
- **Blocked Port**: Ports that are disabled to prevent loops. They do not forward traffic but can be activated if the network topology changes.

### 5. State of Ports

Ports in STP can be in one of several states, which dictate their behavior:

- **Listening**: The port is preparing to forward data but is not yet forwarding.
- **Learning**: The port is learning MAC addresses but is not forwarding data.
- **Forwarding**: The port is actively forwarding data and learning MAC addresses.
- **Blocking**: The port is not forwarding data to prevent loops.

### 6. Convergence

- **Definition**: Convergence is the process by which the network stabilizes after a change in topology (e.g., a switch failure).
- **Function**: STP recalculates the best paths and reconfigures the network to ensure that all switches have a consistent view of the topology.

