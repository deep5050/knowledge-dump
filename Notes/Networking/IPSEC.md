
![217432-understand-ipsec-ikev1-protocol-00-2259919632](https://github.com/user-attachments/assets/182afb54-8167-4649-9840-6f8ad51cfe40)

## What an IPsec Tunnel Is

IPsec (Internet Protocol Security) creates a **secure, encrypted connection** between two networks or endpoints over an untrusted IP network (typically the Internet). The tunnel encapsulates original IP packets, protecting them from eavesdropping, tampering, and replay attacks.

## Core Components

| Component | Role |
|-----------|------|
| **Security Associations (SAs)** | Define the parameters (encryption algorithm, keys, lifetimes) for each direction of traffic. |
| **IKE (Internet Key Exchange)** | Negotiates and establishes SAs automatically; IKEv1 and IKEv2 are the two versions. |
| **ESP (Encapsulating Security Payload)** | Provides confidentiality (encryption) and optional integrity/authentication for the payload. |
| **AH (Authentication Header)** | Supplies integrity and authentication only (no encryption); rarely used alone. |
| **Tunnel Mode vs. Transport Mode** | *Tunnel mode* encrypts the entire original IP packet and adds a new outer IP header (used for site‑to‑site VPNs). *Transport mode* encrypts only the payload, leaving the original IP header intact (used for host‑to‑host communication). |

## How It Works (Step‑by‑Step)

1. **Negotiation** – The two peers run IKE to agree on cryptographic algorithms, exchange keys, and create SAs.  
2. **Key Derivation** – From the exchanged Diffie‑Hellman values, each side derives symmetric keys for ESP/AH.  
3. **Encapsulation** – Outbound packets are wrapped in ESP (or ESP+AH) headers, encrypted, and then placed inside a new IP packet (tunnel mode).  
4. **Transmission** – The encapsulated packet travels across the public network.  
5. **Decapsulation** – The receiving peer validates integrity, decrypts the payload, and extracts the original packet for delivery to the internal network.  

## Typical Use Cases

- **Site‑to‑site VPN**: Connects two corporate LANs over the Internet, making them appear as a single private network.  
- **Remote‑access VPN**: Allows individual users to securely reach a corporate network from anywhere.  
- **Hybrid cloud**: Secures traffic between on‑premises data centers and cloud environments.  

## Security Considerations

- **Strong Algorithms**: Use AES‑256 for encryption and SHA‑2/256 for integrity.  
- **Perfect Forward Secrecy**: Ensure IKE uses Diffie‑Hellman groups that provide PFS (e.g., group 14 or higher).  
- **Key Lifetimes**: Rotate SAs regularly (e.g., every 8 hours) to limit exposure if a key is compromised.  
- **Access Controls**: Pair IPsec with firewall rules to restrict which subnets may communicate.  

---  

## Quick Checklist for Deploying an IPsec Tunnel

1. Define the **local and remote subnets** to be protected.  
2. Choose **IKE version** (IKEv2 is recommended).  
3. Select **encryption/authentication algorithms** (AES‑256/SHA‑256).  
4. Configure **pre‑shared key** or **certificate‑based authentication**.  
5. Set **SA lifetimes** and enable **PFS**.  
6. Apply **firewall rules** to allow UDP 500/4500 (IKE) and ESP (protocol 50).  
7. Test connectivity and verify that traffic is encrypted (e.g., using packet captures).


## Prerequisites

| Item | Why it matters |
|------|----------------|
| **Linux distribution** | Example uses Ubuntu 22.04; other distros have similar packages (`strongswan`, `ipsec-tools`). |
| **Root / sudo access** | Required to modify network interfaces and install packages. |
| **Two endpoints** | You need the public IP (or DNS) of the remote router and the internal subnets on each side. |
| **Shared secret or certificates** | Determines how the peers authenticate each other. |

---

## 1. Install the IPsec stack (StrongSwan)

```bash
sudo apt update
sudo apt install strongswan strongswan-pki libstrongswan-extra-plugins
```

*`strongswan`* provides a full IKEv2 implementation and supports both tunnel‑mode ESP and AH.

---

## 2. Create /etc/ipsec.conf

```bash
sudo nano /etc/ipsec.conf
```

```conf
config setup
    charondebug="ike 2, cfg 2, net 2"   # optional, for troubleshooting
    uniqueids=no                       # allow multiple connections from same ID

conn SITE_TO_SITE
    authby=secret                      # use PSK; change to "pubkey" for certs
    left=%any                          # local side (router)
    leftid=@routerA                    # any identifier you like
    leftsubnet=10.0.1.0/24             # LAN behind this router
    leftfirewall=yes                   # let StrongSwan manage iptables rules
    right=203.0.113.5                  # public IP of remote router
    rightid=@routerB
    rightsubnet=10.0.2.0/24            # LAN behind remote router
    ike=aes256-sha256-modp2048        # IKE SA proposal
    esp=aes256-sha256                  # ESP SA proposal
    keyexchange=ikev2
    type=tunnel
    auto=add                           # load at startup; use "start" to bring up immediately
```

*Adjust `leftsubnet`, `rightsubnet`, and the remote IP (`right`) to match your network.*

---

## 3. Define the pre‑shared key (PSK)

```bash
sudo nano /etc/ipsec.secrets
```

```conf
@routerA @routerB : PSK "YourStrongPresharedKeyHere"
```

*If you prefer certificates, replace the `authby=secret` line with `authby=pubkey` and configure the PKI (see StrongSwan docs).*

---

## 4. Enable IP forwarding and adjust sysctl

```bash
sudo sysctl -w net.ipv4.ip_forward=1
```

To make it permanent, edit `/etc/sysctl.conf` and ensure the line exists:

```conf
net.ipv4.ip_forward=1
```

Apply changes:

```bash
sudo sysctl -p
```

---

## 5. Start and enable the StrongSwan service

```bash
sudo systemctl restart strongswan
sudo systemctl enable strongswan
```

Check status:

```bash
sudo systemctl status strongswan
```

---

## 6. Bring the connection up (optional immediate start)

```bash
sudo ipsec up SITE_TO_SITE
```

You should see logs like:

```
... IKE_SA established, ESP SA established
```

To verify the tunnel:

```bash
sudo ipsec statusall
```

Look for `INSTALLED` SAs for both directions.

---

## 7. Firewall considerations

If you run a separate firewall (e.g., `ufw` or `iptables`), allow the necessary ports and protocols:

```bash
# IKE (UDP 500) and NAT‑Traversal (UDP 4500)
sudo ufw allow 500/udp
sudo ufw allow 4500/udp

# ESP protocol (IP protocol 50)
sudo ufw allow proto esp
```

If you rely on `iptables` directly:

```bash
sudo iptables -A INPUT -p udp --dport 500 -j ACCEPT
sudo iptables -A INPUT -p udp --dport 4500 -j ACCEPT
sudo iptables -A INPUT -p esp -j ACCEPT
```

---

## 8. Testing the tunnel

From a host in the local LAN (e.g., 10.0.1.10), ping a host in the remote LAN (e.g., 10.0.2.20):

```bash
ping 10.0.2.20
```

If the ping succeeds, the IPsec tunnel is operational. You can also capture traffic on the router to confirm ESP encapsulation:

```bash
sudo tcpdump -i any esp
```

You should see ESP packets flowing between the two public IPs.

---

## 9. Troubleshooting tips

| Symptom | Quick check |
|---------|-------------|
| **Tunnel never comes up** | `sudo journalctl -u strongswan -f` for real‑time logs; verify PSK matches on both ends. |
| **ESP packets not seen** | Ensure UDP 500/4500 and protocol 50 are allowed through any external firewall. |
| **One‑way traffic only** | Verify `leftsubnet`/`rightsubnet` are correct and that NAT isn’t stripping ESP (use NAT‑Traversal). |
| **SA expires quickly** | Adjust `ikelifetime` and `keylife` in the `conn` section if needed. |

---
