# CSE 150 – Lecture 24 & 25  
**Topic: Networking and Distributed Systems**  

---

## Concepts

- Centralized vs. Distributed Systems  
- Network protocols, packets, and architecture  
- Layered network design: OSI vs Internet  
- Internet Protocol (IP), TCP, UDP, Sockets  
- Wireless networking challenges (CPS, MAC, collisions)  
- Cyber Physical Systems (CPS) and modulation

---

## Lecture Notes

### Centralized vs Distributed Systems
- **Centralized**: Single physical machine runs all functions
- **Distributed**: Multiple systems coordinate to perform a task
  - Can be a **cluster** (local) or wide-area peer-to-peer systems

### Networking Basics
- **Network**: Physical link for communication  
- **Packet**: Unit of transfer; a sequence of bits  
- **Protocol**: Rules for transmitting data

### Broadcasting Media
- Uses **packet headers** for routing
- Devices discard packets not addressed to them
- Ethernet does filtering in hardware (no interrupt to CPU unless matched)

### Multiple Access & Arbitration
- Problem: **Collisions** when multiple nodes send simultaneously
- **ALOHA Network**: Simple protocol, resends on failure, inefficient under load
- **Random Backoff**: Helps avoid repeated collisions

### Point-to-Point Networks
- Modern systems use **switches** and **routers**
- More scalable and less prone to collisions
- **Switch**: Converts shared bus to point-to-point
- **Router**: Forwards packets between networks

### Hierarchical Internet Design
- Use **subnets** and **prefix-based routing**
- Not every host talks directly to others
- Routers route by matching prefixes bit-by-bit

### Intermediate Layers
- Abstracts hardware details from applications
- New hardware/software only needs to adapt to the neighboring layer

### 5-Layer Internet Architecture
- **Application**
- **Transport** (TCP/UDP)
- **Network** (IP)
- **Data Link**
- **Physical**

### Hourglass Model
- Narrow "waist" = IP
- Allows innovation above (apps) and below (hardware)
- Only **one protocol** at network layer (IP), but many at transport and data link

### Packet Wrapping ("Packets in Envelopes")
- Every layer **adds a header**
- Data is wrapped at each layer and unwrapped on receiving side
- Layer interactions are with **peer layers**

---

## Internet Protocols

### IP (Internet Protocol)
- **Best-effort delivery** – No guarantee of correctness
- Allows **interoperability** across networks
- Does **not** provide bandwidth or latency guarantees

### TCP (Transmission Control Protocol)
- Provides:
  - Reliable, in-order delivery
  - Congestion & flow control
  - Connection setup and teardown
- Used for:
  - Web (HTTP), email (SMTP), file transfer, etc.

### TCP Connection Lifecycle
- **3-Way Handshake**:
  1. Client sends SYN
  2. Server replies with SYN+ACK
  3. Client replies with ACK
- **4-Way Teardown**:
  1. FIN
  2. FIN+ACK
  3. FIN
  4. FIN+ACK

### Sockets
- **Socket API**: Interface between apps and transport protocols
- Same API across platforms: Linux, Windows, OS X, Java, Python, etc.
- Functions: `connect()`, `listen()`, `accept()`, `read()`, `write()`, `close()`

---

## Physical & Wireless Networking

### Cyber Physical Systems (CPS)
- Sensors in roads, buildings, water systems, etc.
- Feed data to an identical digital world
- Wireless networks are crucial

### Wireless Challenges
- **Broadcasting** (anyone can listen)
- **Interference** (omnidirectional)
- **Attenuation** (weaker signal over distance)

### Medium Access Control (MAC)
#### Contention-Free:
- **TDMA**: Time-division
- **FDMA**: Frequency-division

#### Contention-Based:
- **ALOHA**: Fire-and-forget + backoff
- **CSMA**: Listen before transmit, retry if busy

---

## Hidden vs Exposed Terminal Problems

### Hidden Terminal
- Two nodes can’t sense each other but interfere at a common receiver
- Causes **collisions**

### Exposed Terminal
- One node unnecessarily refrains from sending due to hearing a nearby transmission that wouldn’t cause interference

### RTS/CTS (Request to Send / Clear to Send)
- **Small control packets** to reserve channel
- Prevents both hidden and exposed terminal issues

---

## Instructor Notes
- Physical layer uses **modulation** to encode digital data
- **Modularity** across layers helps scale & simplify
- Know how each layer operates and communicates with peers
- Wireless is fundamental to **CPS research** and emerging tech

---

## Exam Tips

- Know **how TCP ensures reliability**
- Understand **3-way handshake and teardown**
- Be able to draw and label **5-layer architecture**
- Explain **hidden/exposed terminals** and how RTS/CTS helps
- Compare **TCP vs UDP**
- Describe **CSMA vs ALOHA**
- Clarify how layering supports network modularity

---

## Key Takeaways

- Layers simplify development and isolate responsibilities
- IP is the **glue** between all network tech and all apps
- TCP is reliable but complex; UDP is simple and fast
- Wireless introduces **collisions, interference**, and needs special protocols
- Modern networks are **distributed**, **layered**, and **modular**