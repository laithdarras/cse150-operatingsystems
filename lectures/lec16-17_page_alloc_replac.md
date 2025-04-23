# CSE 150 – Lecture 16 & 17: Page Replacement and Allocation

---

## Key Concepts

- **Demand Paging** treats main memory as a cache for disk.
- **Page Table Entry (PTE)**: holds physical page address and control bits (valid, dirty, etc.)
- **Page Replacement Policies**:
  - FIFO
  - MIN (Optimal)
  - RANDOM
- **Page Replacement Algorithms**:
  - LRU
  - Second Chance
  - Clock
  - Nth-Chance Clock
- **Page Allocation Policies**:
  - Fixed (equal/proportional)
  - Priority-based
  - Page-fault frequency-based
- **Thrashing**: High page-fault rate due to insufficient memory
- **Working Set Model**: Define active set of pages; swap out processes to avoid thrashing

---

## Lecture Notes

### Review: Cache Concepts Recap

- Cache organization (direct-mapped, set-associative, fully-associative) affects replacement flexibility.
- Temporal locality: recently used → likely to be used again.
- Spatial locality: nearby addresses → likely to be used soon.
- **Average access time** = `(Hit Rate × Hit Time) + (Miss Rate × Miss Time)`
- TLB: Caches virtual-to-physical address translations.

---

### Demand Paging = Caching

- **Goal**: Illusion of infinite memory using disk.
- **Pages** act as cache blocks.
- **Cache Characteristics**:
  - Block size: 1 page
  - Fully-associative (any virtual page → any physical page)
  - Miss = page fault → read from disk
  - Write = write-back strategy (use dirty bit)

### What’s in a PTE?

- Bits for:
  - Valid
  - Writeable
  - User access
  - Dirty
  - Accessed
- If invalid → OS must handle page fault.

---

## Handling a Page Fault

1. OS traps into kernel
2. Select victim page to evict
3. If dirty, write back to disk
4. Mark victim PTE invalid
5. Load required page from disk
6. Update page table and TLB
7. Restart instruction

---

## Effective Access Time (EAT) Formula

```math
EAT = (1 - p) × Memory Access Time + p × Page Fault Service Time
```
- Example: 1 in 1,000 faults → slowdown by 40×
- To limit to <10% slowdown → need fault rate < 1 in 400,000

---

## Page Replacement Policies

### FIFO (First-In, First-Out)
- Replace oldest loaded page.
- Easy and fair but dangerous.
- Can evict frequently used pages.

### MIN (Optimal)
- Replace page used farthest in the future.
- Not implementable, but used for comparison of other algorithms.

### RANDOM
- Pick a page at random.
- Unpredictable, used in hardware TLBs.

### LRU (Least Recently Used)
- Replace page not used for longest time.
- Good approximation of MIN.
- Costly to implement:
    - Need timestamp on every access.

---

## Page Replacement Algorithms

### Second Chance Algorithm
- FIFO + use bit (u)
- On replacement:
    - If u = 1: clear and move to back of queue (give second chance)
    - If u = 0: evict

### Clock Algorithm
- More efficient second-chance variant.
- Circular buffer + single clock hand (pointer).
- On page fault:
    - If use bit = 0 → evict
    - If use bit = 1 → clear bit and move hand

### Nth-Chance Clock
- Track how many times a page has been passed over
- Dirty pages → given extra chances
    - e.g., clean: N = 1, dirty: N = 2

---

## Page Allocation Policies

### Equal Allocation
- All processes get the same # of pages.

### Proportional Allocation
- Based on process size or priority.
    - Use formula seen in Slide #17 to calculate the proportion for a process

### Priority-Based Allocation
- Based on priority weight instead of size.

---

### Page-Fault Frequency Allocation
- Dynamically adjust # pages per process based on actual fault rate:
    - Too low → remove page
    - Too high → add page

### Thrashing & Working Set Model
- **Thrashing** = process stuck in loop of page faults.
- **Working Set**: pages needed to avoid thrashing

---

## Examples
- Ref stream: A B C A B D A D B C B

### FIFO:
- 7 faults

### MIN:
- 5 faults

### LRU:
- Same as MIN in this case

> Belady’s Anomaly: Adding memory can increase faults in FIFO. This does not happen in LRU or MIN.

---

## Instructor Notes
- LRU is theoretically better, but too expensive in practice.
- Real systems implement approximate LRU (e.g., clock).
- Belady’s anomaly: FIFO can perform worse with more memory!
- You must know how to:
    - Identify faults
    - Step through algorithms (FIFO, LRU, MIN)
    - Count number of faults
    - Understand TLB and PTE interactions

---

## Key Takeaways
- The choice of a page replacement policy is critical for performance.
- LRU ≈ MIN, but expensive.
- Clock and Nth-Chance Clock are practical alternatives.
- Know how to trace page fault handling process.
- Allocation strategies affect fault frequency and thrashing risk.