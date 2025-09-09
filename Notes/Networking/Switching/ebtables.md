**ebtables** is a Linux firewall utility that operates at Layer 2 (Data Link Layer) to filter Ethernet frames. It's the Ethernet bridge equivalent of iptables, designed specifically for bridging environments.

## **Key Concepts**

**Layer 2 Filtering:**
- Operates on Ethernet frames, not IP packets
- Filters based on MAC addresses, VLAN tags, Ethernet types
- Works before IP processing occurs
- Essential for bridge/switch functionality

**Bridge Integration:**
- Primarily used with Linux bridge interfaces
- Filters traffic passing through bridge ports
- Can filter both bridged and routed traffic
- Integrates with kernel bridge code

## **ebtables Tables**

### **1. FILTER Table (Default)**
**Purpose:** Basic frame filtering and access control

**Built-in Chains:**
- **INPUT**: Frames destined for bridge itself
- **OUTPUT**: Frames originating from bridge
- **FORWARD**: Frames being bridged between ports

**Example:**
```bash
ebtables -t filter -A INPUT -s 00:11:22:33:44:55 -j DROP
```

### **2. NAT Table**
**Purpose:** MAC address translation and frame modification

**Built-in Chains:**
- **PREROUTING**: Modify frames before bridging decision
- **OUTPUT**: Modify outgoing frames
- **POSTROUTING**: Modify frames after bridging decision

**Example:**
```bash
ebtables -t nat -A OUTPUT -s 00:11:22:33:44:55 --to-source 00:aa:bb:cc:dd:ee
```

### **3. BROUTE Table**
**Purpose:** Bridge/route decision making

**Built-in Chains:**
- **BROUTING**: Decide whether to bridge or route frames

**Example:**
```bash
ebtables -t broute -A BROUTING -p IPv4 --ip-dst 192.168.1.1 -j redirect --redirect-target DROP
```

## **Common Match Criteria**

**MAC Addresses:**
- Source MAC (`-s` or `--source`)
- Destination MAC (`-d` or `--destination`)
- MAC address ranges and wildcards

**Protocol Types:**
- Ethernet type (`-p` or `--protocol`)
- Common protocols: IPv4, IPv6, ARP, 802.1Q

**VLAN Information:**
- VLAN ID matching
- VLAN priority
- 802.1Q tag presence

**Interface Matching:**
- Input interface (`-i`)
- Output interface (`-o`)
- Logical interface (`--logical-in`, `--logical-out`)

## **Practical Use Cases**

### **1. MAC Address Filtering**
```bash
# Block specific MAC address
ebtables -A FORWARD -s 00:11:22:33:44:55 -j DROP

# Allow only known MAC addresses
ebtables -A FORWARD -s ! 00:aa:bb:cc:dd:ee -j DROP
```

### **2. VLAN Security**
```bash
# Drop frames with specific VLAN ID
ebtables -A FORWARD -p 802_1Q --vlan-id 100 -j DROP

# Limit VLAN access by MAC
ebtables -A FORWARD -p 802_1Q --vlan-id 200 -s 00:11:22:33:44:55 -j ACCEPT
```

### **3. ARP Protection**
```bash
# Prevent ARP spoofing
ebtables -A FORWARD -p ARP --arp-ip-src 192.168.1.1 -s ! 00:aa:bb:cc:dd:ee -j DROP
```

### **4. Broadcast Control**
```bash
# Limit broadcast traffic
ebtables -A FORWARD -d Broadcast -j DROP
```

## **Integration with iptables**

**Processing Order:**
1. **ebtables** (Layer 2 filtering)
2. **iptables** (Layer 3/4 filtering)

**Bridge-netfilter:**
- Allows iptables to filter bridged traffic
- Can cause conflicts with ebtables
- Controlled via `/proc/sys/net/bridge/bridge-nf-call-*`

## **Key Differences from iptables**

**Operating Layer:**
- **ebtables**: Layer 2 (Ethernet frames)
- **iptables**: Layer 3/4 (IP packets)

**Matching Criteria:**
- **ebtables**: MAC addresses, Ethernet types, VLAN tags
- **iptables**: IP addresses, ports, protocols

**Use Cases:**
- **ebtables**: Switch-like filtering, VLAN security, MAC control
- **iptables**: Router-like filtering, NAT, port-based rules

## **Common Commands**

**View Rules:**
```bash
ebtables -L                    # List all rules
ebtables -t nat -L            # List NAT table rules
ebtables -L --Ln              # Show line numbers
```

**Add Rules:**
```bash
ebtables -A FORWARD -s MAC -j DROP     # Append rule
ebtables -I INPUT 1 -d MAC -j ACCEPT   # Insert at position 1
```

**Delete Rules:**
```bash
ebtables -D FORWARD 1         # Delete rule by number
ebtables -F                   # Flush all rules
```

**Save/Restore:**
```bash
ebtables-save > /etc/ebtables.rules
ebtables-restore < /etc/ebtables.rules
```

## **Performance Considerations**

**Efficiency:**
- Processes frames before IP layer
- Can drop unwanted traffic early
- Less CPU intensive than deep packet inspection

**Bridge Performance:**
- Minimal impact on bridge forwarding
- Hardware offloading possible on some platforms
- Important for high-throughput environments

ebtables is essential for implementing Layer 2 security policies in bridged environments, complementing iptables for comprehensive network filtering.
