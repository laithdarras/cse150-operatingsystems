# CSE 150 – Lectures 2 & 3: Processes, Threads, and Address Spaces

---

## Key Concepts

- **Thread**: Single execution context (Program Counter, Registers, Stack)
- **Address Space**: Virtual memory view of a program; separated from physical memory
- **Process**: An executing program (includes address space + threads)
- **Dual Mode Operation**: Kernel mode vs. User mode (hardware support for protection)
- **Base & Bound Address Translation**
- **Context Switch**: Mechanism to switch between processes
- **Mode Transfers**: `syscall`, `interrupt`, `trap`

---

## Lecture Notes

### Four Fundamental OS Concepts

| Concept         | Description |
|----------------|-------------|
| **Thread**      | Describes a program's current state and execution context (PC, registers, stack) |
| **Address Space** | The virtual memory in which a thread executes, abstracted from physical memory |
| **Process**     | A program in execution: contains an address space and one or more threads |
| **Dual Mode**   | Distinguishes user and kernel access, enforced by hardware |

---

## Threads

- **Thread = Singular Execution Context**
  - **PC (Program Counter)**: tracks current instruction
  - **Stack Pointer**, registers, execution state
- **Concurrency** = multiple threads or processes active at once
- Threads are **lightweight** and more efficient than full processes

---

## Concurrency Models

- **Uniprogramming**: Only one thread runs at a time
- **Multiprogramming**: Multiple threads run concurrently, possibly on the same CPU
- **Multitasking/Multiprocessing**: OS switches between threads via **context switching**

---

### Illusion of Multiple CPUs (Virtual CPUs)
- **Virtualization via context switching**
  - Store current thread’s context (PC, SP, registers)
  - Load next thread’s context
- Triggered by:
  - **Timer interrupts**
  - **Voluntary yield**
  - **I/O operations**

---

## Protection Mechanisms

- OS must protect itself and user processes:
  - From each other
  - From crashing the system
- Enforced by:
  - **Memory isolation**
  - **I/O access limits**
  - **Mode switching control**

---

## Address Spaces

- Each process sees a unique **virtual address space**
  - Easier for programming
  - Prevents unwanted access
- Memory actions may:
  - Do nothing
  - Cause I/O (memory-mapped I/O)
  - Cause exceptions (e.g. segmentation fault)

---

### Base and Bound (B&B) Address Translation

- **Simple protection technique**:
  - **Base**: starting physical address
  - **Bound**: maximum size
- Checks:
  - Is the address in range?
  - If yes → `physical = virtual + base`
- Translation can be:
  - **Static**: On program load
  - **Dynamic**: During execution

---

## Processes

- **Process** = Address Space + Threads
- Also holds:
  - **Open file descriptors**
  - **Memory state (heap, stack)**
  - **Process Control Block (PCB)** = metadata for OS

---

### Process Control Block (PCB)
- Stores:
  - CPU state (registers, PC)
  - Scheduling info
  - Memory mappings
  - I/O state

---

## Multiprogramming and Context Switching

- Only **one process active at a time per CPU**
- Context switch:
  - Save current PCB
  - Load next process’s PCB
  - Done in kernel mode (overhead!)

---

## Dual Mode Operation

| Mode     | Capabilities                         |
|----------|--------------------------------------|
| **Kernel** | Full access to memory, I/O, privileged instructions |
| **User**   | Limited access; must request privileged ops via syscalls |

---

### Transitions Between Modes

| Type        | Trigger                              | Notes |
|-------------|--------------------------------------|-------|
| **Syscall**   | User calls a system function         | e.g., `exit`, `read`, `write` |
| **Interrupt** | External event (e.g. timer, I/O)     | Switch to kernel mode |
| **Trap**      | Internal error (e.g. divide by zero) | Caught by the OS |

- Controlled via **Interrupt Vector Table**
- OS saves PC, mode, and other state

---

## Memory Isolation via Translation Maps

- Each process has its own **translation map**
  - Prevents one process from accessing another’s memory
- Also prevents access to OS memory
- On context switch:
  - OS loads new translation map

---

## Instructor Notes

- Know the **4 OS Concepts** very well: Thread, Address Space, Process, Dual Mode
- Understand **mode switching** and how syscalls/interrupts work
- Draw out **Base & Bound translation** to practice address protection logic
- Remember: modern systems use more complex translation (paging, TLB), but this is the foundation

---

## Key Takeaways

- **Threads** are the minimal execution unit
- **Processes** encapsulate threads + protected memory space
- OS **multiplexes** CPU using context switching
- **Dual mode** ensures system security and control
- **Base & Bound** is a simple but powerful memory protection mechanism