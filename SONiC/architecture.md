<img width="1112" height="796" alt="image" src="https://github.com/user-attachments/assets/15cd35b5-6a24-420b-913e-3618f8a46956" />

---

## 🧱 **SONiC Architecture Overview**

SONiC (Software for Open Networking in the Cloud) is a modular, container-based network OS built on Linux. It uses a **central Redis database** for inter-process communication and state management, and each major function runs in its own **Docker container**.

---

## 🧩 **Key Components (Docker Containers)**

### 1. **Database**
- Hosts the **Redis engine**.
- Provides multiple databases:
  - `APPL_DB`: Application state (routes, neighbors, etc.)
  - `CONFIG_DB`: Configuration data (ports, VLANs, etc.)
  - `STATE_DB`: Operational state (used for dependency resolution)
  - `ASIC_DB`: Hardware-specific state
  - `COUNTERS_DB`: Port statistics

---

### 2. **Swss (Switch State Service)**
- Manages communication between SONiC modules.
- Hosts daemons like:
  - `portsyncd`, `intfsyncd`, `neighsyncd`: Listen to kernel events and push state to Redis.
  - `orchagent`: Core logic to process state and push to ASIC_DB.
  - `intfmgrd`, `vlanmgrd`: Configure interfaces and VLANs based on DB state.

---

### 3. **Syncd**
- Interfaces with the **ASIC hardware**.
- Uses **SAI API** and vendor-provided **ASIC SDK**.
- Subscribes to `ASIC_DB` and pushes state to hardware.

---

### 4. **Teamd**
- Manages **Link Aggregation (LAG)**.
- Uses `teamd` and `teamsyncd` to interact with lower layers and Redis.

---

### 5. **Pmon**
- Monitors hardware sensors and fans.
- Runs `sensord` and `fancontrol`.

---

### 6. **Snmp**
- Provides SNMP support.
- Includes:
  - `snmpd`: Main SNMP server.
  - `snmp-agent`: SONiC-specific AgentX subagent that reads from Redis.

---

### 7. **Dhcp-relay**
- Relays DHCP requests between subnets.

---

### 8. **Lldp**
- Handles **Link Layer Discovery Protocol**.
- Includes:
  - `lldp`: Main daemon.
  - `lldp_syncd`: Pushes LLDP state to Redis.
  - `lldpmgr`: Subscribes to `STATE_DB` for incremental config.

---

### 9. **Bgp**
- Runs routing protocols (BGP, OSPF, etc.) using **FRR** or **Quagga**.
- Key processes:
  - `bgpd`: Handles BGP sessions.
  - `zebra`: Manages routing tables and kernel updates.
  - `fpmsyncd`: Pushes FIB state to Redis.

---

## 🖥️ **Host-Level Components**

- **CLI**: Built using Python’s Click library.
- **sonic-cfggen**: Generates configuration files and applies changes.

---

## 🔄 **Inter-Component Communication**

- **Redis** is the central message bus.
- Components act as **publishers** or **subscribers** to various DBs.
- Blue arrows in diagrams represent Redis-based communication; black arrows represent other methods (e.g., netlink, filesystem).
