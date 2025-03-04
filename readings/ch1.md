# Chapter 1: Introduction

---

## 1.1 What Operating Systems Do
- An **operating system (OS)** is software that manages hardware and acts as an intermediary between the user and the hardware.
- Different OSes have different goals (efficiency, convenience, usability).
- A computer system consists of four components:
  1. Hardware (CPU, memory, I/O devices)
  2. Operating System
  3. Application Programs
  4. Users
- The OS is like a **government**—it doesn't do useful work by itself but creates an environment for programs to run.
- **Resource Allocator:** Manages CPU time, memory space, file storage, and I/O devices.
- **Primary Goal of OS:** Execute user programs and make solving user problems easier.
- Two types of programs in an OS:
  - **Kernel programs**
  - **Application programs**
- Modern computer systems have one or more CPUs and multiple device controllers connected via a shared bus and memory.
- **Interrupts**:
  - Hardware: Triggered by signals from devices.
  - Software: Triggered via system calls (syscalls).
  - The CPU stops its current task and jumps to an interrupt handler stored at a fixed address (via the **interrupt vector**).

---

## 1.2 Computer Organization
- **RAM (main memory)** is volatile and loses its contents when power is off.
- Memory interaction uses **load** and **store** instructions.
- **Von Neumann architecture**:  
  Fetch → Decode → Execute → Store Result
- Storage hierarchy (from fastest/most expensive to slowest/cheapest):
  - Registers → Cache → RAM → Electronic Disk → Magnetic Disk → Optical Disk → Magnetic Tapes
- **Device Drivers**: Translate OS requests into device-specific commands.
- **I/O Operations**: Driver loads controller registers → controller performs operation → interrupt signals completion → driver returns control to OS.

---

## 1.3 Computer Architecture
### Single-Processor Systems
- One general-purpose CPU executes all system instructions.

### Multiprocessor Systems (2+ CPUs)
- **Advantages**:
  - Increased throughput.
  - Economy of scale.
  - Improved reliability (if one CPU fails, others can continue).
- **Types**:
  - **Asymmetric Multiprocessing**: Master-slave relationship.
  - **Symmetric Multiprocessing (SMP)**: All processors are equals.
- **Memory Access Models**:
  - **UMA (Uniform Memory Access)**: Equal access time for all CPUs.
  - **NUMA (Non-Uniform Memory Access)**: Some memory areas take longer to access.
- **Multiprocessor Chips**: Multiple CPU cores on one chip; faster communication and lower power consumption.
- **Clustered Systems**: Multiple computers linked via LAN to provide high availability.
  - **Asymmetric Clustering**: One machine is on standby.
  - **Symmetric Clustering**: All machines are active.

---

## 1.4 Operating System Structure
- **Multiprogramming** increases CPU utilization by organizing jobs so the CPU always has something to execute.
  - Jobs waiting for CPU are stored in the **job pool** (disk).
- **Time-sharing (Multitasking)**:
  - Allows multiple users to interact with a system by rapidly switching between tasks.
  - Requires **interactive systems** with short response times.
- **Scheduling**:
  - **Job Scheduling**: Which jobs enter memory.
  - **CPU Scheduling**: Which job gets the CPU next.

---

## 1.5 Operating System Operations
- OSes are **interrupt-driven** (hardware interrupts and software traps/exceptions).
- **Dual-Mode Operation**:
  - **Kernel Mode (privileged)** vs. **User Mode** (restricted).
  - **Mode Bit** indicates the current mode.
- **System Calls (syscalls)**: Allow user programs to request services from the OS.
- **Timers**:
  - Ensure no process monopolizes the CPU.
  - Can be **fixed** or **variable** based on the system design.

---

## 1.6 Process Management
- A **process** is a program in execution.
- Processes require resources: CPU time, memory, I/O devices, files.
- OS Responsibilities:
  - Process creation/deletion.
  - Scheduling and suspension/resumption.
  - Synchronization and communication.

---

## 1.7 Memory Management
- OS Responsibilities:
  - Track which memory is in use and by whom.
  - Decide which processes are loaded into memory.
  - Allocate and deallocate memory as needed.

---

## 1.8 Storage Management
- A **file** is a logical storage unit.
- OS Responsibilities:
  - File creation, deletion, reading, writing, and management.
  - Disk management (free space, storage allocation, scheduling).
  - **Caching** to improve performance by storing frequently accessed data.
- RAM acts as a cache for secondary storage.

---

## 1.9 Protection and Security
- **Protection**: Controls access between processes and system resources.
- **Security**: Defends against external and internal attacks.
- Both work together to maintain system reliability and privacy.

---

## 1.10 Distributed Systems
- A **distributed system** is a network of independent computers working together.
- **Network Types**:
  - **LAN (Local Area Network)**: Small area.
  - **MAN (Metropolitan Area Network)**: City-wide.
  - **WAN (Wide Area Network)**: Country/worldwide.
- **Network OS**: Manages file sharing and process communication over the network.
- **Communication Protocols**: Most common is TCP/IP.

---

## 1.11 Special-Purpose Systems
- **Embedded Systems**: Run on dedicated hardware (like IoT devices) and often use **Real-Time Operating Systems (RTOS)** with strict timing requirements.

---

## 1.12 Computing Environments
- **Network Computers (NCs)**: Rely heavily on web-based applications.
- **Client-Server Model**:
  - **Compute Server**: Handles computation requests.
  - **File Server**: Manages file storage and retrieval.

---

## 1.13 Open-Source Operating Systems
- **Open-source OS**es (like Linux) provide source code for public use and contribution.
- **Closed-source OS**es (like Windows) do not share their source code.
- Open-source is often more secure due to widespread community review.
- Studying OS source code is extremely valuable for understanding how systems work.
