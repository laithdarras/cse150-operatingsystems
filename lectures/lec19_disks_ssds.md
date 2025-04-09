# CSE 150 – Lecture 19: Disks and SSDs

---

## Key Concepts

- **Disk vs SSD vs DRAM vs RAM**: Characteristics, performance, and trade-offs  
- **SSDs (Solid State Drives)**: Faster, non-volatile storage without moving parts  
- **Hard Disk Drives (HDDs)**: Traditional, mechanical storage with platters  
- **Disk latency breakdown**: Seek time, rotational delay, transfer time  
- **SSD Architecture**: Read, write, erase behaviors  
- **Error detection and correction** (ECC)  
- **Garbage collection** and **write amplification** in SSDs  
- **I/O performance metrics**: Throughput vs latency  
- **Block-level vs Byte-level access**  
- **Why writing is more complex and expensive than reading in SSDs**  

---

## Lecture Notes

### Standard Device Interfaces

| Device Type       | Examples                        | Access | Notes                                                                 |
|------------------|----------------------------------|--------|-----------------------------------------------------------------------|
| Block Devices     | HDDs, SSDs, USB Drives, DVD-ROM | Block  | Read/write large blocks, supports `read()`, `write()`, `seek()`       |
| Character Devices | Keyboards, Mice, Serial Ports    | Byte   | Accessed one char at a time using `get()`, `put()`                    |
| Network Devices   | Ethernet, Bluetooth, Wi-Fi       | Stream | Handled separately using socket interface, e.g. `select()`, TCP/IP    |

---

### Disk Architecture: HDD

- **Hard Disk Drive (HDD)**: Mechanical device with platters, read/write head
- **Latency Breakdown**:
  - **Seek time**: Moving head to the correct track
  - **Rotational latency**: Wait for correct sector to rotate under head
  - **Transfer time**: Reading/writing bits from/to the spinning disk
- **Zoned Bit Recording**:
  - Outer tracks contain more sectors (higher density)
  - Speeds vary by disk location

> **Total Latency =** Queuing Time + Controller Overhead + Seek Time + Rotational Delay + Transfer Time

---

### I/O Performance

- **Response Time** = Time spent waiting in queue + Device service time
- **Throughput**: Total amount of data processed in a given time
- As **utilization approaches 100%**, queue grows → **exponential increase in response time**

**Solutions to bottlenecks**:
- Make hardware faster  
- **Decouple systems** using multi-bus or tree structure buses  
- **Buffering/Spooling**: Preload data to reduce wait time  

---

### SSD Architecture

#### What is an SSD?

- **Solid State Drive (SSD)** = Flash memory with **no moving parts**
- First appeared in 1995 with battery-backed DRAM  
- 2009 → Flash-based SSDs with **NAND memory**  
- Sectors called **pages** (typically 4KB) grouped into **blocks**  

---

### SSD: Read Path

- Works similarly to RAM:
  - **No seek or rotation latency**
  - **~25 microseconds** access time
- High throughput for both sequential and random reads  
- **Latency = Queuing Time + Controller Overhead + Transfer Time**

---

### SSD: Write Path

- **Writes are way more complex and slower**:
  - Can only write to **empty pages**
  - If data must be updated:
    - Read → Erase block → Write updated page
  - Erase takes ~1.5 ms (very expensive!)

> **Rule of thumb**:  
> Writes = 10× more expensive than reads  
> Erase = 10× more expensive than writes

---

### SSD Write Example

- Write A, B, C, D to one block  
- Later write A’, B’, C’, D’ (updated versions) → **Old ones marked obsolete**  
- **Garbage collection** triggered by controller:
  - Valid pages copied elsewhere
  - Entire block is erased and reused

---

### SSD Summary

| Feature              | SSDs                                 | HDDs                                 |
|----------------------|---------------------------------------|--------------------------------------|
| Latency              | Low (<0.1ms)                          | Higher (Seek + Rotate = ~10ms)       |
| Moving Parts         | None                                  | Yes (motor, head, platter)           |
| Noise/Shock          | Silent, shock-resistant               | Noisy, sensitive to shock            |
| Power Consumption    | Low                                   | Higher                               |
| Storage Size         | Smaller capacity (0.5x HDD)           | Larger (more economical)             |
| Price                | Expensive (7–10× HDD)                 | Cheap                                |
| Lifespan             | Limited due to write/erase cycles     | Longer (mechanically robust)         |
| Update Capability    | Cannot update a single page in block  | Can update specific sector directly  |

---

## Instructor Notes

- Know that **SSD = flash memory**, not RAM  
- Writes are **slower** because SSDs can’t just overwrite — they must erase whole blocks  
- Reads are fast because they behave like memory reads  
- **Error Correction**: ECC bits are added to each page to detect and fix errors  
- **Not tested on the exam**, but useful to know for hardware-focused roles like firmware development and such.

---

## Key Takeaways

- SSDs offer **high-speed, low-latency** storage but are **more expensive**
- **Erasing and rewriting** data is complex → leads to garbage collection overhead
- SSD performance depends on **controller efficiency**, **free block availability**, and **usage pattern**
- **No moving parts** = more robust and portable
- Although they outperform HDDs in almost every way, SSDs **have limited write cycles**

---

## Diagrams to Draw

- HDD Architecture Diagram: Platter, Track, Sector, Head  
- SSD Read Path: Buffer Manager, Controller, DRAM, NAND grid  
- SSD Write Cycle: Original write, update, invalidation, garbage collection  
- Latency comparison graph (HDD vs SSD)  
- SSD Lifecycle diagram: Write → Erase → Write → GC  