# CSE 150 - Operating Systems  
### Lecture 14: Address Translation (Cont.)  
**Date:** March 19, 2025  
**Professor:** Wan Du  
**Topic:** Memory Management — Paging, Page Tables, MMU, and Multi-Level Translation  

---


## Key Concepts

- **Paging** is introduced as a finer-granularity solution to memory fragmentation.
- **Segmentation** breaks memory into logical units (code, stack, heap, etc.).
- Paging divides **physical memory** into **fixed-size chunks (pages)**.
- Uses **virtual-to-physical memory mapping** via **page tables**.
- Goal: Efficiently manage memory, reduce overhead of swapping, and improve access performance.

---

## Lecture Walkthrough (Concepts + Professor Commentary)

### Motivation for Paging

- **Why not just use segmentation?**
  - Segmentation causes **external fragmentation**, making it hard to fit variable-sized chunks.
  - Limited flexibility with **resizing** (e.g., stack or heap growth).
  - Moving segments to fit new processes becomes inefficient.
  - Shared memory in segmentation is limited to adjacent segments.

- **Paging solves this by:**
  - Using **equal-sized** fixed blocks of memory.
  - Avoiding both internal and external fragmentation.
  - Allowing processes to be broken into **multiple pages**.

---

## Paging Basics

- Each process has its own **Page Table**.
- **Virtual Address** is split into:
  - **Page Number** (high bits)
  - **Offset** (low bits)

> Example:  
> For a 16-bit address with 10-bit offset  
> → Offset = 10 bits → Page Size = 2^10 = **1024 bytes (1 KB)**  
> → Page Number = 6 bits → Page Table has 2^6 = **64 entries**

---

## Paging: Address Translation Solution

1. **Convert Virtual Address to Binary**
2. **Separate bits** into:
   - Page Number
   - Offset
3. **Use Page Number** as index in page table (verify within bounds)
4. Get **Physical Page Number** from table
5. Concatenate Physical Page + Offset
6. **Convert back to Hex (optional)**

> Example:  
> Virtual address `0x1122` → `0001 0001 0010 0010`  
> - Page Number (6 bits) = `000100` = 4  
> - Offset (10 bits) = `010000100010`  
> - Access Page Table at index 4 → Get physical page  
> - Concatenate with offset to get physical address

---

## Memory Management Unit (MMU)

- MMU is a hardware component that **performs address translation**.
- Takes virtual addresses from CPU and maps them to physical addresses using:
  - **Page tables**
  - **Segment tables (in combined models)**
- Stores page permissions (valid, readable, writable, etc.)

---

## Page Table Details

- **Each entry** (PTE = Page Table Entry) contains:
  - Physical Page Number
  - **Permissions**: Valid, Read/Write, User-Mode
- Located in **physical memory**
- Page Table is indexed by **Virtual Page Number**

---

## Implementation Enhancements

### Page Table Size
- Size of the Page Table = `2^(number of virtual page bits)`
- Large address spaces → **very large page tables**
- Need methods to reduce size

### Multi-Level Paging

- Solution: **Two-Level Paging**
- Break Page Table into **segments**
  - Only load the **active** segments into memory
  - **Inactive ones** stay in disk

> Virtual address format (example):  
> - 10 bits → First-level index  
> - 10 bits → Second-level index  
> - 12 bits → Offset

- Benefits:
  - Efficient for sparse address spaces
  - Smaller memory footprint for page tables
- Costs:
  - Multiple memory accesses for one translation
  - Slower without TLB (Translation Lookaside Buffer)

---

## Examples to Understand

### 1st Example:

> From Slide 21:

```text
Virtual address: 0b00000000  
- Virtual Segment: 000  
- Virtual Page: 00  
- Offset: 000  

First-level page table → index 000  
→ Points to second-level table  
→ Second-level index 00 → entry = 0b00010  
→ Final Physical Address = 0b00010000
```

### 2nd Example:
Virtual address: 0b01000000  
- Segment = 010  
- Page = 00  
- Offset = 000  
→ Final Physical Address = 0b01010000

---

## Sharing Pages
- Page tables for **different processes** can point to the **same physical page**.
- Enables **shared memory**, e.g., for IPC (inter-process communication)

---

## Inverted Page Tables (Advanced)
- **Hash table-based** solution
- Each physical page keeps track of its virtual page mapping
- Benefits:
    - Efficient for large address spaces (e.g., 64-bit systems)
    - Compact size: proportional to **physical memory** (not virtual)
- Drawbacks:
    - More comples to implement
    - Can be slow w/o hardware support

---

## Summary Table

...

---

## Professor's Remarks & Key Emphasis
- Understand **step-by-step** how to calculte physical address:
    - Break virtual address
    - Lookup in page tables
    - Append offset
- Professor emphasized that **multi-level paging** will show up on the final
- Make sure you can **explain the process**, not just compute the result
- Exam may ask to **convert a given virtual address into a physical one** using multi-level translation
- Know the difference between **segmentation vs paging**

**Remember: Inactive page tables stay on disk, only active tables reside in memory**

---

## Key Takeaways
- Paging allows fine-grained memory control and prevents fragmentation.
- Page tables translate virtual page numbers into physical addresses.
- Multi-level translation reduces table size and supports sparse memory usage.
- MMU controls this process doing all the calculations.
- Be comfortable walking through binary -> decimal -> address resolution steps.

## Diagrams to Draw
1. Page Table Lookup flowchart
2. virtual &rarr physical mapping diagram
    - show virtual address breakdown &rarr page table lookup -> physical addr
3. two-level page table
4. shared page table between two processes
5. inverted page table structure
6. paged segementation and segmentation vs paging comparison chart