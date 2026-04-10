## ![[Pasted image 20260106150931.png]]

https://deepwiki.com/sonic-net/sonic-gnmi/1-overview
## 🌐 What is gNMI?

- **gNMI** is a protocol defined by the OpenConfig working group.

- It uses **gRPC** (Google’s Remote Procedure Call framework) to provide efficient, secure, and streaming communication between network devices and management systems.

- It is designed specifically for **network configuration and telemetry** using YANG models.

## 📡 gNMI as a Northbound Interface in SONiC

In SONiC’s management framework, gNMI acts as one of the **northbound interfaces**—the entry points through which external controllers or automation systems interact with SONiC.

- **Configuration**: gNMI allows external systems to push configuration changes (modeled in YANG) into SONiC.
    
- **Telemetry/Streaming**: gNMI supports **Subscribe RPCs**, enabling real-time streaming of operational data and state from SONiC to controllers.
    
- **Unified access**: Instead of relying only on REST or CLI, gNMI provides a modern, scalable way to manage SONiC devices programmatically.
    
- **Integration with TransLib**: gNMI requests are passed into **TransLib**, which translates them into Redis DB operations after validation.
## 🔑 Why gNMI Matters

- **Efficiency**: Uses gRPC, which is faster and more lightweight than traditional HTTP/REST.
    
- **Streaming telemetry**: Provides continuous updates rather than polling, reducing overhead.
    
- **Standardization**: Aligns SONiC with industry-wide OpenConfig/YANG models.
    
- **Automation-friendly**: Ideal for SDN controllers, orchestration platforms, and large-scale deployments.
- 
- ## 📘 Example Flow

1. A network controller sends a **gNMI Set RPC** to configure BGP neighbors.
    
2. SONiC’s gNMI server receives the request.
    
3. The request is passed into **TransLib**, which validates it against YANG schemas using CVL.
    
4. TransLib writes the configuration into SONiC’s Redis DB.
    
5. SONiC apps (like BGP) pick up the change and apply it.
    
6. Telemetry data can be streamed back via **gNMI Subscribe RPCs**.


![[Pasted image 20260106152219.png]]



- gNMI is vendor neutral
- show logging -f
- 