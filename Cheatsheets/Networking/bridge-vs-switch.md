In networking, bridges and switches are both Layer 2 devices that forward data based on MAC addresses, but they differ significantly in their design and capabilities:

**Bridge:**
- Typically has only 2-4 ports
- Uses software-based switching with a single collision domain per port
- Processes frames sequentially, which can create bottlenecks
- Older technology, largely replaced by switches
- All ports share the same bandwidth
- Creates separate collision domains but maintains one broadcast domain per bridge

**Switch:**
- Usually has many ports (8, 16, 24, 48, or more)
- Uses hardware-based switching with dedicated ASICs (Application-Specific Integrated Circuits)
- Can process multiple frames simultaneously (parallel processing)
- Each port operates at full bandwidth (full-duplex communication)
- Each port is its own collision domain
- More advanced features like VLANs, port mirroring, and quality of service

**Key Technical Differences:**
- **Performance**: Switches offer much higher throughput due to hardware-based forwarding and parallel processing
- **Scalability**: Switches can handle many more ports and higher data rates
- **Intelligence**: Modern switches include advanced features for network management and security
- **Cost**: Switches have become cost-effective enough to replace bridges in most applications

Today, the term "bridge" is mostly used in wireless networking (wireless bridges) or in specific protocol contexts. What we commonly call "switches" in modern networks are technically "multiport bridges," but they've evolved far beyond the capabilities of traditional bridges.
