Reference: https://www.linkedin.com/pulse/napi-new-api-linux-kernel-networking-david-zhu-wcz6c/

## NAPI
**NAPI (New API)** is the event handling mechanism used by the Linux networking stack for efficient packet processing. Originally designed to **reduce interrupt overhead during high network traffic**, NAPI implements a hybrid approach that **combines interrupts and polling** to optimize network performance.

Note: The name NAPI no longer stands for anything in particular, though it was originally an acronym for "New API" when it was introduced to the Linux kernel.

### The Problem NAPI Solves
In traditional network processing, each incoming packet generates an interrupt, forcing the CPU to stop its current work and handle the packet. This approach works well for low traffic scenarios but becomes inefficient under high network loads for several reasons:

- **Interrupt Storms**: When thousands of packets arrive per second, the constant stream of interrupts can overwhelm the CPU
- **Context Switching Overhead**: Each interrupt requires saving and restoring CPU state
- **Cache Thrashing:** Frequent interrupts disrupt CPU cache efficiency
- **Wasted Resources:** The kernel must handle every incoming packet even if it will be dropped due to overload.

  <img width="1531" height="609" alt="image" src="https://github.com/user-attachments/assets/28822966-4b90-428f-b8e5-226c49184e78" />

### How NAPI Works
NAPI addresses these issues by implementing a hybrid approach:

- **Interrupt-Driven at Low Traffic:** During low traffic periods, the system operates in traditional interrupt-driven mode
- **Polling at High Traffic**: When traffic increases beyond a threshold, the system switches to polling mode
- **Adaptive Behavior:** The system automatically switches between these modes based on traffic conditions.
- 
  <img width="1399" height="1000" alt="image" src="https://github.com/user-attachments/assets/50122fe6-085a-4fd3-b9da-e8e9bcab0508" />

### NAPI Implementation in the Linux Kernel

Key Components
- `struct napi_struct`: The core data structure representing a NAPI instance
- `netif_napi_add()`: Function to register a NAPI instance with the networking subsystem
- `napi_schedule()`: Function to schedule NAPI processing
- `napi_complete_done()`: Function to mark NAPI processing as complete
- 

### Driver Integration

```c
/* 1. Initialize and register NAPI during device probe */
netif_napi_add(dev, &tp->napi, rtl8169_poll);

/* 2. Implement an interrupt handler */
static irqreturn_t rtl8169_interrupt(int irq, void *dev_instance)
{
    struct net_device *dev = dev_instance;
    struct rtl8169_private *tp = netdev_priv(dev);
    u16 status;
    
    /* Read and validate interrupt status */
    status = RTL_R16(tp, IntrStatus);
    if (unlikely(!status || status == 0xFFFF))
        return IRQ_NONE;
    
    /* Acknowledge the interrupt */
    RTL_W16(tp, IntrStatus, status);
    
    /* Disable further interrupts and schedule NAPI */
    rtl_irq_disable(tp);
    napi_schedule(&tp->napi);
    
    return IRQ_HANDLED;
}

/* 3. Implement a poll function */
static int rtl8169_poll(struct napi_struct *napi, int budget)
{
    struct rtl8169_private *tp = container_of(napi, struct rtl8169_private, napi);
    struct net_device *dev = tp->dev;
    int work_done;
    
    /* Process TX completions */
    rtl_tx(dev, tp, budget);
    
    /* Process RX packets (limited by budget) */
    work_done = rtl_rx(dev, tp, budget);
    
    /* If we processed all packets, exit polling mode and re-enable interrupts */
    if (work_done < budget && napi_complete_done(napi, work_done))
        rtl_irq_enable(tp);
    
    return work_done;
}

```

### The Budget Parameter
The budget parameter is crucial to NAPI's operation:

- It limits the number of packets processed in a single poll cycle
- Prevents a single network interface from monopolizing CPU time
- Allows the kernel to fairly distribute processing time among multiple interfaces
- Typical values range from 64 to 300 packets per poll cycle

  <img width="1100" height="1000" alt="image" src="https://github.com/user-attachments/assets/1d1f0ea1-ef95-4bbd-ad3b-6a06d1d441a0" />

### NAPI Processing Steps
- **Initial Interrupt:** When packets arrive, the NIC generates an interrupt
- **Interrupt Handler:** The driver's interrupt handler: 1. Acknowledges the interrupt 2. Disables further interrupts from the device 3. Calls napi_schedule() to schedule the NAPI poll function
- **NAPI Poll:** The kernel's softirq mechanism calls the driver's poll function, which: 1. Processes completed TX packets 2. Processes RX packets up to the budget limit 3. Returns the number of packets processed
- **Completion Decision:**  1. If work_done < budget: All packets have been processed, so call napi_complete_done() and re-enable interrupts 2. If work_done == budget: There may be more packets to process, so NAPI remains scheduled and interrupts remain disabled

### Registration

```c
netif_napi_add(dev, &tp->napi, rtl8169_poll);
```

### Interrupt Handler

```c
static irqreturn_t rtl8169_interrupt(int irq, void *dev_instance)
{
    /* ... interrupt validation ... */
    
    /* Disable further interrupts and schedule NAPI */
    rtl_irq_disable(tp);
    napi_schedule(&tp->napi);
    
    return IRQ_HANDLED;
}
```

### NAPI Poll Function

```c
static int rtl8169_poll(struct napi_struct *napi, int budget)
{
    struct rtl8169_private *tp = container_of(napi, struct rtl8169_private, napi);
    struct net_device *dev = tp->dev;
    int work_done;

    rtl_tx(dev, tp, budget);
    work_done = rtl_rx(dev, tp, budget);

    if (work_done < budget && napi_complete_done(napi, work_done))
        rtl_irq_enable(tp);

    return work_done;
}
```

### Advantages of NAPI
- **Reduced Interrupt Overhead**
During high traffic, the driver stays in polling mode, significantly reducing the number of interrupts and associated CPU overhead.

- **Better CPU Utilization**
Batch processing of packets is more efficient, allowing better use of CPU cache and reducing context switching.

- **Adaptive Behavior**
Automatically switches between interrupt-driven and polling modes based on traffic conditions, providing optimal performance in all scenarios.

- **Improved Latency Under Load**
Prevents interrupt storms during high traffic, maintaining system responsiveness even under heavy network load.

- **Efficient Packet Dropping**
When the system is overloaded, packets can be dropped at the hardware level without consuming CPU resources for processing.

- **Driver Simplification**
Provides a standardized framework for network drivers, simplifying driver development and maintenance.

### Conclusion

NAPI represents a significant advancement in Linux network processing, providing an elegant solution to the challenges of high-speed networking. By combining the responsiveness of interrupts with the efficiency of polling, NAPI delivers optimal performance across varying traffic conditions.


The hybrid approach allows Linux to handle everything from low-latency applications to high-throughput server workloads efficiently. As network speeds continue to increase, NAPI's importance in the Linux networking stack will only grow, with ongoing enhancements like IRQ suppression mechanisms further improving its capabilities.


Understanding NAPI is essential for network driver developers, system administrators managing high-performance networks, and anyone interested in the inner workings of the Linux networking stack.

