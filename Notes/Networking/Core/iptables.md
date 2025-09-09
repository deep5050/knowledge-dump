<img width="800" height="600" alt="image" src="https://github.com/user-attachments/assets/303912d3-e885-4f7c-bd0d-e0e366c45d5a" />

<img width="1000" height="555" alt="image" src="https://github.com/user-attachments/assets/b64a2dc1-7895-47a5-8c50-a2279762bd50" />

**IPTables** is a Linux firewall utility that uses multiple tables to organize different types of packet processing rules. Each table serves a specific purpose in the packet filtering and manipulation process.

## **The Five Main Tables**

### **1. FILTER Table (Default)**
**Purpose:** Primary packet filtering and access control

**Built-in Chains:**
- **INPUT**: Packets destined for local system
- **OUTPUT**: Packets originating from local system  
- **FORWARD**: Packets being routed through the system

**Common Uses:**
- Allow/deny specific traffic
- Port-based filtering
- IP address blocking
- Basic firewall functionality

**Example:**
```bash
iptables -t filter -A INPUT -p tcp --dport 22 -j ACCEPT
```

### **2. NAT Table**
**Purpose:** Network Address Translation and port redirection

**Built-in Chains:**
- **PREROUTING**: Modify packets as they arrive (DNAT)
- **POSTROUTING**: Modify packets as they leave (SNAT/Masquerading)
- **OUTPUT**: Modify locally generated packets before routing

**Common Uses:**
- Internet connection sharing (masquerading)
- Port forwarding
- Load balancing
- Destination NAT (DNAT)

**Example:**
```bash
iptables -t nat -A POSTROUTING -o eth0 -j MASQUERADE
```

### **3. MANGLE Table**
**Purpose:** Packet alteration and Quality of Service (QoS)

**Built-in Chains:**
- **PREROUTING**: Before routing decisions
- **INPUT**: For local delivery
- **FORWARD**: For routed packets
- **OUTPUT**: For local packets
- **POSTROUTING**: After routing decisions

**Common Uses:**
- Modify packet headers (TTL, TOS, DSCP)
- Traffic shaping preparation
- Marking packets for QoS
- Advanced routing decisions

**Example:**
```bash
iptables -t mangle -A PREROUTING -p tcp --dport 80 -j MARK --set-mark 1
```

### **4. RAW Table**
**Purpose:** Connection tracking exemption and early packet processing

**Built-in Chains:**
- **PREROUTING**: Before connection tracking
- **OUTPUT**: For local packets before tracking

**Common Uses:**
- Disable connection tracking for specific traffic
- Performance optimization for high-volume traffic
- Bypass connection tracking overhead
- Handle stateless protocols

**Example:**
```bash
iptables -t raw -A PREROUTING -p tcp --dport 80 -j NOTRACK
```

### **5. SECURITY Table**
**Purpose:** SELinux and Mandatory Access Control (MAC)

**Built-in Chains:**
- **INPUT**: Incoming packets
- **OUTPUT**: Outgoing packets
- **FORWARD**: Forwarded packets

**Common Uses:**
- SELinux security context labeling
- Mandatory access control enforcement
- Security policy implementation
- Works with SELinux-enabled systems

## **Table Processing Order**

**Incoming Packets:**
1. **RAW** (PREROUTING)
2. **MANGLE** (PREROUTING)
3. **NAT** (PREROUTING)
4. **MANGLE** (INPUT)
5. **FILTER** (INPUT)
6. **SECURITY** (INPUT)

**Outgoing Packets:**
1. **RAW** (OUTPUT)
2. **MANGLE** (OUTPUT)
3. **NAT** (OUTPUT)
4. **FILTER** (OUTPUT)
5. **SECURITY** (OUTPUT)
6. **MANGLE** (POSTROUTING)
7. **NAT** (POSTROUTING)

**Forwarded Packets:**
1. **RAW** (PREROUTING)
2. **MANGLE** (PREROUTING)
3. **NAT** (PREROUTING)
4. **MANGLE** (FORWARD)
5. **FILTER** (FORWARD)
6. **SECURITY** (FORWARD)
7. **MANGLE** (POSTROUTING)
8. **NAT** (POSTROUTING)

## **Important Concepts**

**Chain Traversal:**
- Packets traverse chains based on their path through the system
- Rules processed in order within each chain
- First matching rule determines action

**Table Selection:**
- Default table is FILTER if not specified
- Use `-t` flag to specify different table
- Each table has specific capabilities and purposes

**Performance Considerations:**
- RAW table processed first for performance-critical rules
- Connection tracking can be bypassed using RAW table
- Mangle table useful for QoS marking before filtering

**Common Workflow:**
1. **RAW**: Decide on connection tracking
2. **MANGLE**: Modify packet headers/marks
3. **NAT**: Translate addresses/ports
4. **FILTER**: Allow or deny traffic
5. **SECURITY**: Apply security policies

Understanding these tables and their processing order is crucial for creating effective and efficient firewall rules in Linux systems.
