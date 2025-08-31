# Lecture 13 - Address Translation & Memory Management  
Date: March 17, 2025  
Prof. Wan Du | CSE 150 – Operating Systems

---

## Topics Covered:
- Memory Hierarchy and Characteristics
- Virtualization and Multiplexing
- Address Translation
- Segmentation and Fragmentation
- Segmentation Table Calculations
- Swapping and Finer Granularity

---

## Memory Hierarchy

- **Why we need a hierarchy**:
  - Cost, speed, and size vary significantly across types of memory.
  - Volatile vs. Non-volatile:
    - **Memory (RAM)** is **volatile** - loses contents on power-off.
    - **SSD, HDD** are **non-volatile** - retains data after power-off.

- **Closer to the CPU = faster but smaller & more expensive**:
  - Registers < Cache < Main Memory < SSD < HDD < Optical/Tape

### Characteristics:

| Storage | Speed | Cost | Volatility |
|---------|-------|------|------------|
| Registers | Fastest | Very High | Volatile |
| Cache | Very Fast | High | Volatile |
| RAM | Fast | Medium | Volatile |
| SSD | Medium | Low | Non-Volatile |
| HDD | Slower | Lower | Non-Volatile |
| Tape | Very Slow | Cheapest | Non-Volatile |

---

## Virtualizing Memory & Multiplexing

- **Multiplexing**: Multiple processes share the same memory but not at the same time.
- **Solution**: OS virtualizes memory for each process -> translates **virtual addresses** into **physical addresses**.
- Every program thinks it starts at **address 0x00000000**.
- Virtual memory is an illusion that simplifies programming and improves isolation.

---

## Multi-Step Program Execution Pipeline

1. **Compile**: Convert `.c → .o`
2. **Link**: Combine objects to `.exe`
3. **Load**: Program placed in memory
4. **Execution**: OS begins execution and manages memory

> Best time to do **address translation** = **at loader phase**  
> Once translated and mapped into physical memory, **cannot be undone**.

---

## Multiprogramming: Base & Limit

- **Early address translation**: Use **Base Address** and **Limit Register**:
  - Virtual address + base = Physical address
  - Limit used to **check if address is valid**
- If violation -> **hardware traps to OS**
- Helps prevent one process from corrupting another.

### Drawbacks:
- **Fragmentation**: Gaps in memory due to different process sizes.
- Stack & heap **grow/shrink dynamically** - difficult to preallocate correctly.
- **Processes can only share adjacent memory** -> limited flexibility.

---

## Fragmentation Problem

- Caused when completed processes leave gaps in memory.
- New processes may not fit exactly -> leads to wasted space.
- OS needs to reclaim or compact memory -> overhead!

---

## Solution: More Flexible Segmentation

- Divide memory into **logical segments**:
  - Code, Stack, Heap, Data - each segment is independent.
- Segments can be:
  - Shared across processes
  - Moved independently
  - Allocated non-contiguously
- Easier to grow/shrink stack & heap
- Improves modularity, sharing, and protection

---

## Segment Table Translation

Each process has a **Segment Table** that maps:
- **Segment Index** -> (Base, Limit, Valid Bit)

### Translation Steps:
1. Break virtual address into:
   - **Segment ID** (e.g., first 2 bits)
   - **Offset** (remaining bits)
2. Use Segment ID to look up Base & Limit
3. **Check offset < limit** -> if invalid -> raise exception
4. Calculate: **Physical Address = Base + Offset**

### Example:
- Virtual Address: `0xC000` -> `0b1100000000000000`
- Segment ID = `11` (binary), Offset = 0s
- Segment Table entry 3 used

---

## Valid Bit in Segment Table

- Used to **invalidate** or **protect** segments.
- OS can prevent access to certain regions (e.g., freed memory).
- **Reduces overhead** by catching invalid access early.

---

## Swapping

- **Swapping** = Moving inactive processes from memory to **disk** to make room.
- Only the **active portion** of a process is in RAM.
- Extreme version of context switching at the memory level.

### Problem:
- Multi-segment model assumes **entire segment is in memory**
- Can’t always afford that -> need to divide further

### Solution: **Finer Granularity**
- **Paging** (coming up next): break memory into small **pages**
- Allows partial loading of a process
- Maximizes number of runnable processes in RAM

---

## Final Notes:
- OS must manage:
  - **Virtual → Physical Address Translation**
  - **Protection** via segmentation
  - **Swapping** via dynamic memory use
- Understanding segmentation table is essential (used in HW/exams)

---

## Summary of Key Concepts

| Concept                | Description                                                                 |
|------------------------|-----------------------------------------------------------------------------|
| Memory Hierarchy       | Registers → Cache → RAM → SSD → HDD → Tape                                  |
| Virtual Memory         | Each process gets its own logical memory space                              |
| Base & Limit           | Simple translation mechanism with bounds checking                           |
| Segmentation           | Divide memory into logical parts (Code, Stack, Heap, Data)                  |
| Fragmentation          | Wasted memory from process allocation issues                                |
| Segmentation Table     | Stores base, limit, valid bits for each segment                             |
| Swapping               | Move inactive processes to disk to free up RAM                              |
| Granularity            | Finer divisions (paging) to load partial memory of processes                |