## SAI

In SAI, there are two distinct ways hardware resources are represented: **Objects** and **Entries**. 

Understanding the difference between them is the most common "gotcha" for new ASIC developers.

---

## 1. SAI Objects (The "Things")
Objects represent physical or logical hardware entities. They are identified by a **SAI Object ID (OID)**, which is a 64-bit handle.

* **Lifecycle:** You use `create_xxx`, `remove_xxx`, `set_xxx_attribute`, and `get_xxx_attribute`.
* **The OID:** The OID is vendor-specific. The SDK generates it and gives it back to the OS.
* **Examples:**
    * **Port:** A physical front-panel port.
    * **VLAN:** A logical broadcast domain.
    * **Virtual Router (VR):** A container for L3 routing tables.
    * **Router Interface (RIF):** A port or VLAN that has been assigned an IP.
    * **Next Hop:** A destination (IP + Interface) where traffic should go.



---

## 2. SAI Entries (The "Rules")
Entries are not identified by a 64-bit OID. Instead, they are identified by a **Key** (a C-struct). Think of entries as the rows in a table.

* **Lifecycle:** You use `create_xxx_entry`, `remove_xxx_entry`, etc.
* **The Key:** Because entries don't have OIDs, you must provide the exact same "Key" to remove them as you did to create them.
* **Why no OID?** Because ASICs often have millions of these (like routes). Generating and storing 8 bytes of OID for every single route would waste too much CPU memory.
* **Examples:**
    * **Route Entry:** Key = `{Destination IP/Mask, Virtual Router OID}`.
    * **FDB Entry:** Key = `{MAC Address, VLAN OID}`.
    * **Neighbor Entry:** Key = `{Neighbor IP, RIF OID}`.

---

## 3. The "Attribute" System
Every Object and Entry is managed through **Attributes**. This is how you change settings without needing new functions for every feature.

Each attribute has:
1.  **ID:** An enum (e.g., `SAI_PORT_ATTR_ADMIN_STATE`).
2.  **Value:** A union (`sai_attribute_value_t`) that can hold an `int`, `bool`, `oid`, etc.

> **Cheat Sheet for your Notes:**
> * **Object (OID):** Use when the thing is a standalone entity (Switch, Port, Queue).
> * **Entry (Key):** Use when the thing is a lookup rule in a table (Route, FDB, Neighbor).

---

## Common Object Workflow (Example: L3 Forwarding)
To route a packet, the ASIC developer must link these objects in a chain. If one link is missing (like the error you saw earlier), the pipeline breaks:

1.  **Switch Object** (The ASIC itself)
2.  **Virtual Router Object** (The routing context)
3.  **Router Interface Object** (Attaches the VR to a physical port)
4.  **Neighbor Entry** (Maps the Next-Hop IP to a MAC address)
5.  **Next Hop Object** (Points to the Neighbor)
6.  **Route Entry** (The final rule: "For IP X, use Next Hop Y")

If you are prepping for a lab or an interview, would you like to see the specific C-struct for a **Route Entry Key** so you can see how it differs from a standard Object?
