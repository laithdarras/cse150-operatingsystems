# CSE 150 – Lecture: Caches and TLBs

---

## Key Concepts

- **Cache**: A small, fast memory layer that stores frequently accessed data for quicker retrieval
- **Cache Misses**: When data is not found in cache → go to lower memory (DRAM)
- **Locality of Reference**:
  - **Temporal locality**: recently accessed = likely to be accessed again soon
  - **Spatial locality**: accessing data near other recently accessed data
- **Cache Mapping Types**:
  - Direct-Mapped
  - Fully Associative
  - Set-Associative
- **Replacement Policies**: LRU (Least Recently Used), Random
- **Write Strategies**: Write-through, Write-back
- **Translation Lookaside Buffer (TLB)**: A cache for memory address translations
- **TLB Miss Handling**: Hardware or software page table traversal
- **Context Switches**: Flush or use ProcessID tagging

---

## Memory Hierarchy & Caching Motivation

- Goal: Make memory **appear large, cheap, and fast**
- Based on **principle of locality**
- Memory Hierarchy:

| Level           | Speed (ns) | Size       | Notes               |
|----------------|------------|------------|---------------------|
| Registers      | ~1         | <1KB       | In CPU              |
| L1 Cache       | ~10        | ~32KB      | Closest to CPU      |
| L2/L3 Cache    | ~100       | MBs        | Intermediate cache  |
| Main Memory    | ~100ns     | GBs        | DRAM                |
| SSD            | 0.1 ms     | 100s GBs   | Flash-based storage |
| HDD            | 10 ms      | TBs        | Mechanical disk     |

---

## Caching Basics

- **Average Access Time**:  
  `AAT = (Hit Rate × Hit Time) + (Miss Rate × Miss Time)`
- **Cache is only effective** if:
  - Frequent case is truly frequent
  - Infrequent case is not overly expensive

---

## Types of Cache Misses

| Miss Type     | Description                                                    |
|---------------|----------------------------------------------------------------|
| Compulsory    | Cold start – first time a block is accessed                    |
| Capacity      | Cache too small to hold all required blocks                    |
| Conflict      | Two blocks map to the same cache index in direct-mapped caches |
| Coherence     | Data updated externally (e.g., DMA, multi-core updates)        |
| Policy        | Poor replacement policy evicts useful data                    |

---

## Cache Organizations

### Direct-Mapped
- Each block in memory maps to **exactly one cache slot**
- **Index** bits used to determine position in cache
- **Tag** used to identify if correct block is cached

### Fully Associative
- Memory blocks can be placed **anywhere in cache**
- All tags must be compared (expensive hardware)

### Set-Associative
- Cache is divided into **sets**, each with **N blocks**
- Block maps to a set → compare N tags in that set
- Common configurations: 2-way, 4-way, 8-way

---

## Address Breakdown (Typical)

- **Byte Offset**: Select byte within a block
- **Index/Set**: Select cache set
- **Tag**: Uniquely identifies block

---

## Replacement Policies

| Policy | Description                                      | Pros                      | Cons                     |
|--------|--------------------------------------------------|---------------------------|--------------------------|
| Random | Replace any line randomly                       | Simple                    | May evict useful block   |
| LRU    | Least Recently Used                             | Good temporal locality    | Needs tracking overhead  |

---

## Write Policies

| Strategy       | Description                                                                  | Pros                          | Cons                         |
|----------------|------------------------------------------------------------------------------|-------------------------------|------------------------------|
| Write-Through  | Immediately writes to lower memory when cache is written                     | Simple, consistent            | Slower, more memory writes   |
| Write-Back     | Delays write to memory until cache line is evicted (dirty bit)               | Faster, reduces memory writes | Requires dirty bit management|

---

## TLB (Translation Lookaside Buffer)

- A **cache for address translations**
- Avoids looking up full page table every memory access
- TLB is **fully associative** (any entry can hold any page translation)
- Stores: virtual page # → physical page # + permission bits

### TLB Miss Handling

| Type         | Description                                                  |
|--------------|--------------------------------------------------------------|
| Hardware     | MMU walks page table automatically                           |
| Software     | OS handles fault, looks up page table, inserts into TLB      |

---

## TLB + Cache in Address Translation
- CPU --> TLB --> Physical Address --> Cache --> Data (if TLB miss, use page table)
    - TLB hit → get physical address fast
    - TLB miss → walk page table → fill TLB → continue
    - **Caching applies at two levels**: 
        - Address translations (TLB)
        - Data access (Cache)

---

## Context Switch and TLB

- On **context switch**, TLB must be cleared unless:
  - Hardware supports **ProcessID (PID)** tagging
- TLB must be kept consistent with current process’ address space

---

## Caching Summary

| Concept         | Purpose                                           |
|-----------------|--------------------------------------------------|
| Caching         | Speed up access by storing frequently used data  |
| Locality        | Leverage patterns in data access                 |
| Cache Types     | Direct-Mapped, Set-Associative, Fully-Associative|
| Cache Misses    | Compulsory, Capacity, Conflict, Coherence, Policy|
| Write Policies  | Write-through (safe), Write-back (efficient)     |
| TLB             | Speeds up address translation                    |
| TLB Miss        | Can be hardware- or software-handled             |

---

## Instructor Notes

- **Understand cache mapping and policies**
- Practice **calculating average access time**
- TLB and Cache can be confused—**they serve different purposes**
- Know **how write-through vs write-back behaves**
- HW3: segmentation + paging + cache examples
  - Draw virtual → physical steps
  - Practice load/store with access permission checks