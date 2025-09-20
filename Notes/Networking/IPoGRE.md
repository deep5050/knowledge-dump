## IP over GRE (IPoGRE) Tunnel Overview

IPoGRE is a method of encapsulating IP packets inside GRE (Generic Routing Encapsulation) tunnels, allowing the creation of virtual point‑to‑point links over an IP network. It is commonly used to interconnect separate routing domains, transport non‑routable protocols, or provide a simple overlay network.

### How It Works
1. **Encapsulation** – An original IP packet (the *inner* packet) is wrapped with a GRE header and a new outer IP header.  
2. **Transport** – The outer IP header routes the GRE‑encapsulated packet across the underlying IP network (the *tunnel‑core*).  
3. **Decapsulation** – At the tunnel endpoint, the outer IP and GRE headers are stripped, delivering the original inner IP packet to its destination.

### Key Components
| Component | Role |
|-----------|------|
| **GRE Header** | Carries protocol type (e.g., IPv4, IPv6) and optional fields (checksum, key, sequence number). |
| **Outer IP Header** | Determines the path through the underlying network; source and destination are the tunnel endpoints. |
| **Inner IP Packet** | The actual payload that the tunnel is meant to transport. |

### Typical Use Cases
- **Connecting Disparate Networks** – Link two sites that cannot share a direct routing protocol (e.g., two private LANs behind NAT).  
- **Transporting Non‑Routable Protocols** – Carry protocols like IPv6 over an IPv4‑only backbone.  
- **Simplified VPNs** – Provide a lightweight VPN‑like overlay without the overhead of IPsec.  

### Configuration Basics (Cisco‑style example)

```bash
interface Tunnel0
 ip address 10.0.0.1 255.255.255.252   ! Tunnel endpoint address
 tunnel source 192.0.2.1               ! Physical interface IP
 tunnel destination 198.51.100.1      ! Remote tunnel endpoint IP
 tunnel mode gre ip                    ! GRE encapsulating IPv4
```

- The **source** and **destination** IPs belong to the underlying network.  
- The **tunnel IP** (10.0.0.1/30) is used for routing traffic through the tunnel.  

### Advantages
- **Simplicity** – Minimal configuration compared to IPsec.  
- **Protocol Agnostic** – Can carry any protocol identified by the GRE protocol field.  
- **Flexibility** – Works over any IP network, including the public Internet.

- ------------------------
## Configuring an IP‑over‑GRE Tunnel on Linux

### Prerequisites
- Two Linux hosts (A and B) with routable IP addresses on the underlying network.  
- `iproute2` package (standard on most distributions).  
- Root or sudo privileges.

### 1. Create the GRE Tunnel Interface

On **Host A** (replace the example addresses with your own):

```bash
sudo ip tunnel add gre0 mode gre \
    local 192.0.2.10 \      # Host A’s outer IP
    remote 198.51.100.20 \   # Host B’s outer IP
    ttl 255
```

On **Host B**:

```bash
sudo ip tunnel add gre0 mode gre \
    local 198.51.100.20 \
    remote 192.0.2.10 \
    ttl 255
```

### 2. Assign Tunnel‑Endpoint IP Addresses

These addresses are used for routing traffic **inside** the tunnel.

```bash
# Host A
sudo ip addr add 10.0.0.1/30 dev gre0

# Host B
sudo ip addr add 10.0.0.2/30 dev gre0
```

### 3. Bring the Tunnel Interface Up

```bash
sudo ip link set gre0 up
```

Run the command on both hosts.

### 4. Verify Connectivity

```bash
ping -c 3 10.0.0.2   # From Host A to Host B’s tunnel IP
```

A successful ping confirms that the GRE tunnel is operational.

### 5. Optional: Adjust MTU

GRE adds ~24 bytes of overhead. Reduce the tunnel MTU to avoid fragmentation:

```bash
sudo ip link set dev gre0 mtu 1472   # 1500 – 28 (IP) – 24 (GRE)
```

### 6. Make the Configuration Persistent

#### Debian/Ubuntu (using `/etc/network/interfaces`)

Add to `/etc/network/interfaces` on each host:

```ini
auto gre0
iface gre0 inet static
    address 10.0.0.1      # or 10.0.0.2 on Host B
    netmask 255.255.255.252
    pre-up ip tunnel add gre0 mode gre local 192.0.2.10 remote 198.51.100.20 ttl 255
    post-down ip tunnel del gre0
    mtu 1472
```

#### RHEL/CentOS (using NetworkManager)

Create `/etc/sysconfig/network-scripts/ifcfg-gre0`:

```ini
DEVICE=gre0
BOOTPROTO=none
ONBOOT=yes
IPADDR=10.0.0.1          # or 10.0.0.2 on Host B
NETMASK=255.255.255.252
MTU=1472
TYPE=GRE
GRE_LOCAL=192.0.2.10
GRE_REMOTE=198.51.100.20
GRE_TTL=255
```

Restart the network service or bring the interface up with `nmcli`.

### 7. Routing Traffic Through the Tunnel (example)

If you want all traffic to a remote subnet (e.g., 172.16.0.0/16) to travel via the GRE tunnel:

```bash
# On Host A
sudo ip route add 172.16.0.0/16 via 10.0.0.2 dev gre0

# On Host B
sudo ip route add 172.16.0.0/16 via 10.0.0.1 dev gre0
```
### Limitations
- **No Built‑in Security** – GRE provides no encryption or authentication; additional mechanisms (e.g., IPsec) are needed for confidentiality.  
- **Potential MTU Issues** – Encapsulation adds overhead (typically 24 bytes), requiring MTU adjustments to avoid fragmentation.  
- **Limited QoS Support** – GRE does not carry QoS markings from the inner packet unless explicitly configured.
