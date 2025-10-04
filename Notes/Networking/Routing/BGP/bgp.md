## **1. What is BGP?**

* BGP is the **routing protocol of the internet**.
* It is a **path-vector protocol** that exchanges routing information between **Autonomous Systems (AS)** (large networks under a single administrative domain).
* Defined in **RFC 4271** (with many extensions like BGP-4, BGP-LU, BGP-MP).

---

## **2. Types of BGP**

* **eBGP (External BGP):** Runs **between different ASes**, e.g., between two ISPs or an ISP and an enterprise.
* **iBGP (Internal BGP):** Runs **within the same AS** between routers for consistent route distribution.

---

## **3. Characteristics**

* **Path-vector protocol:** Uses AS-PATH to avoid loops.
* **Policy-based routing:** Admins can control route selection using attributes.
* **Incremental updates:** Sends updates only when something changes (not full table every time).
* **Runs over TCP (port 179):** Provides reliability compared to protocols like OSPF or RIP.

---

## **4. BGP Attributes (key to route selection)**

BGP decides the **best path** using attributes, in order of preference:

1. **Local Preference (LOCAL_PREF)** – Highest wins (used inside AS).
2. **AS Path** – Shorter is preferred.
3. **Origin Type** – IGP > EGP > Incomplete.
4. **Multi-Exit Discriminator (MED)** – Lower is better (between ASes).
5. **eBGP over iBGP** – eBGP-learned routes preferred.
6. **IGP metric to next-hop** – Shorter IGP path to next-hop wins.
7. **Router ID** tie-breaker.

---

## **5. BGP Route Advertisement**

* A router **advertises the full path (AS-PATH)** it knows to reach a network.
* Ensures **loop prevention** since a router will reject a route if it already sees its own AS in the path.

---

## **6. BGP Tables**

* **Adj-RIB-In:** Routes received from neighbors.
* **Loc-RIB:** Routes selected as best by BGP decision process.
* **Adj-RIB-Out:** Routes to advertise to neighbors.

---

## **7. Where is BGP used?**

* **Internet routing (ISP to ISP).**
* **Enterprise edge networks** (for multi-homing to ISPs).
* **Datacenter fabrics** (e.g., EVPN with BGP for overlays).
* **Cloud networking** (AWS, Azure, GCP all use BGP peering).

---

## **8. Strengths & Weaknesses**

✅ **Strengths:**

* Scalable (internet has ~1M+ routes, handled by BGP).
* Highly controllable with routing policies.
* Stable (TCP-based, incremental updates).

❌ **Weaknesses:**

* Convergence is **slower** than OSPF/ISIS.
* Complex to configure and secure.
* Vulnerable to **route hijacking** if not secured (needs RPKI/ROA for validation).

---

Do you want me to also create a **diagrammatic flow** showing how routes propagate in BGP (from eBGP → iBGP → route selection)?
