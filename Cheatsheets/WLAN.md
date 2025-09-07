
# WLAN (Wireless Local Area Network)

is a network that uses radio waves instead of cables to connect devices within a limited area, typically extending a wired LAN wirelessly.

**Core Components:**

**Access Point (AP):** The central hub that connects wireless devices to the wired network. Broadcasts wireless signals and manages client connections.

**Wireless Network Interface Card (WNIC):** Hardware component in client devices (laptops, phones, tablets) that enables wireless communication with the AP.

**Wireless LAN Controller (WLC):** Centralized device that manages multiple APs, handles authentication, security policies, and traffic management in enterprise deployments.

**Antenna Systems:** Directional or omnidirectional antennas that transmit and receive radio signals, determining coverage area and signal strength.

**Authentication Server:** Typically a RADIUS server that handles user authentication and authorization for secure network access.

**WLAN operates using IEEE 802.11 standards** (Wi-Fi) on unlicensed frequency bands, primarily 2.4 GHz and 5 GHz, with newer deployments using 6 GHz. The network creates coverage areas called Basic Service Sets (BSS), which can be extended through multiple APs forming an Extended Service Set (ESS).

**Key characteristics:** Mobility support, shared medium access, security through encryption (WPA2/WPA3), and automatic connection management for seamless roaming between access points.

## Protocols

| Protocol         | Frequency Band | Maximum Data Rate | Range         | Key Features                                      |
|------------------|----------------|-------------------|---------------|---------------------------------------------------|
| **802.11a**      | 5 GHz          | Up to 54 Mbps     | 30 meters     | Uses OFDM modulation; less interference but shorter range. |
| **802.11b**      | 2.4 GHz        | Up to 11 Mbps     | 100 meters    | Uses DSSS modulation; longer range but more interference. |
| **802.11g**      | 2.4 GHz        | Up to 54 Mbps     | 100 meters    | Backward compatible with 802.11b; uses OFDM for higher speeds. |
| **802.11n**      | 2.4/5 GHz      | Up to 600 Mbps    | 250 meters    | MIMO technology for multiple data streams; improved range and speed. |
| **802.11ac**     | 5 GHz          | Up to 3.46 Gbps   | 100 meters    | Wider channels (up to 160 MHz); advanced MIMO and beamforming. |
| **802.11ax (Wi-Fi 6)** | 2.4/5 GHz | Up to 9.6 Gbps    | 100 meters    | Improved efficiency with OFDMA; better performance in crowded environments. |

---

The **802.11 WLAN protocols** are a set of standards developed by the IEEE for wireless local area networks (WLANs). Here's a basic overview of the key protocols:

### 802.11a
- **Frequency Band**: Operates in the **5 GHz** band.
- **Maximum Data Rate**: Up to **54 Mbps**.
- **Range**: Approximately **30 meters** indoors.
- **Key Features**: Utilizes **Orthogonal Frequency Division Multiplexing (OFDM)**, which allows for higher data rates and less interference compared to lower frequency bands.

### 802.11b
- **Frequency Band**: Operates in the **2.4 GHz** band.
- **Maximum Data Rate**: Up to **11 Mbps**.
- **Range**: Approximately **100 meters** indoors.
- **Key Features**: Uses **Direct Sequence Spread Spectrum (DSSS)**, which provides a longer range but is more susceptible to interference from other devices operating in the same frequency band.

### 802.11g
- **Frequency Band**: Operates in the **2.4 GHz** band.
- **Maximum Data Rate**: Up to **54 Mbps**.
- **Range**: Approximately **100 meters** indoors.
- **Key Features**: Backward compatible with 802.11b and uses **OFDM** for higher speeds, combining the benefits of both 802.11a and 802.11b.

### 802.11n
- **Frequency Band**: Operates in both **2.4 GHz and 5 GHz** bands.
- **Maximum Data Rate**: Up to **600 Mbps**.
- **Range**: Approximately **250 meters** indoors.
- **Key Features**: Introduces **Multiple Input Multiple Output (MIMO)** technology, allowing multiple data streams to be transmitted simultaneously, improving both range and speed.

### 802.11ac
- **Frequency Band**: Operates in the **5 GHz** band.
- **Maximum Data Rate**: Up to **3.46 Gbps**.
- **Range**: Approximately **100 meters** indoors.
- **Key Features**: Supports wider channels (up to **160 MHz**), advanced MIMO, and **beamforming** technology, which directs signals toward specific devices for better performance.

### 802.11ax (Wi-Fi 6)
- **Frequency Band**: Operates in both **2.4 GHz and 5 GHz** bands.
- **Maximum Data Rate**: Up to **9.6 Gbps**.
- **Range**: Approximately **100 meters** indoors.
- **Key Features**: Improves efficiency with **Orthogonal Frequency Division Multiple Access (OFDMA)**, allowing multiple users to share channels simultaneously, enhancing performance in crowded environments.

These protocols have evolved to meet the increasing demand for faster and more reliable wireless communication. If you have specific questions about any of these protocols or their applications, feel free to ask!
