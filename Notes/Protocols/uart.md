## UART Overview

![UART-Basic-Connection-1 jpg](https://github.com/user-attachments/assets/20db1782-43be-424d-822c-0599b8af949d)
![UART-Frame jpg](https://github.com/user-attachments/assets/d53c8d27-5f05-45ba-aa93-08ba9a57407e)

UART (Universal Asynchronous Receiver/Transmitter) is a hardware module that converts parallel data from a microcontroller or processor into a serial bit stream (and vice‑versa) for communication over a single‑ended wire pair.

### Key Characteristics
| Aspect | Details |
|--------|---------|
| **Transmission type** | Asynchronous – no separate clock line; timing is derived from a shared baud rate. |
| **Signal lines** | **TX** (transmit), **RX** (receive); optional **RTS/CTS** for hardware flow control. |
| **Data frame** | Typically **1 start bit**, **5‑9 data bits**, optional **parity bit**, and **1‑2 stop bits**. |
| **Baud rates** | Common values: 9600, 19200, 38400, 115200 bps; any rate up to several Mbps depending on hardware. |
| **Voltage levels** | TTL (0 V / 3.3 V or 5 V) or RS‑232 (±12 V) with level‑shifter transceivers. |
| **Full‑duplex** | Separate TX and RX lines allow simultaneous send/receive. |
| **Error detection** | Parity bit (even/odd) and framing error detection (missing stop bit). |

### How UART Works
1. **Idle state** – TX line stays high (logic 1).  
2. **Start bit** – Line pulled low for one bit period, signaling the start of a frame.  
3. **Data bits** – Sent LSB first; each bit sampled at the middle of its period.  
4. **Parity (optional)** – Single bit for simple error checking.  
5. **Stop bits** – One or two high bits indicate the end of the frame and allow the receiver to resynchronize.  

Both sides must agree on **baud rate**, **data bits**, **parity**, and **stop bits**; otherwise frames will be misinterpreted.

### Typical Uses
- Debug consoles (e.g., serial terminals).  
- Communication with GPS modules, Bluetooth modules, modems.  
- Inter‑processor links in embedded systems.  

### Example Configuration (Linux)
```bash
# Set /dev/ttyS0 to 115200 8N1 (8 data bits, No parity, 1 stop bit)
stty -F /dev/ttyS0 115200 cs8 -cstopb -parenb
```

### Advantages & Limitations
| Advantage | Limitation |
|-----------|------------|
| Simple hardware, low pin count | No built‑in addressing – only point‑to‑point |
| Wide support across devices | Limited to relatively low speeds compared to high‑speed serial protocols |
| Easy to debug with terminal programs | Susceptible to noise on long cables without proper shielding or RS‑232 conversion |

UART remains a ubiquitous, low‑cost solution for serial communication in virtually all embedded and PC environments.
