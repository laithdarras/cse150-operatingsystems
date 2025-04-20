# CSE 150 – Lectures 20 & 21: File Systems

---

## Key Concepts

- **Disk Scheduling**: Strategies to decide in what order disk I/O requests should be serviced.
- **Building a File System**: Converting the raw block storage into usable files and directories.
- **File System Abstractions**: Files, inodes, directories, etc.
- **File Access Methods**: Sequential, Random, and Content-based.
- **Disk Allocation Techniques**: Contiguous, Linked, FAT, Indexed, Multilevel Indexed.
- **Directory Structures**: Hierarchical, hard/soft links.
- **Caching and Buffering**: Kernel file caches, read-ahead, LRU.
- **Durability and Reliability**: Journaling, RAID, replication.

---

## Lecture Notes

### Disk Scheduling
- **Disk can only process one I/O request at a time**, so we must choose the order of queued requests wisely.
- **Algorithms**:
  - **FIFO**: Simple and fair, but leads to long seeks.
  - **SSTF**: Shortest Seek Time First — faster on average, but may starve requests.
  - **SCAN**: Elevator-style — sweeps in one direction answering requests from either direction.
  - **C-SCAN**: Circular SCAN — resets to start after sweep, fairer than SCAN.

---

### SSD and Disk Performance
- **SSD Writes**: More complex than reads; erasing a block is expensive.
- **SSD Read Latency**: `Queue + Controller + Transfer`
- **SSD Write Latency**: `Queue + Find Free Block + Transfer`
- **Hard Disk Latency**: `Queue + Controller + Seek + Rotational Delay + Transfer`
- **SSDs have limited lifespan** due to block wear.

---

### What is a File System?
- **Purpose**: Transforms raw disk blocks into named, structured files.
- **Responsibilities**:
  - **Disk Management**: Track and allocate space.
  - **Naming**: Human-readable file names mapped to storage locations.
  - **Protection**: Enforce permissions.
  - **Durability**: Survive crashes and disk failures.

---

## System vs User View of Files

| Layer | Description |
|-------|-------------|
| **User** | Durable, structured data (e.g. documents, images) |
| **System Call Layer** | Collection of bytes (UNIX view) |
| **Inside OS** | Collection of blocks |
- **Block**: Logical transfer unit (e.g. 4KB in UNIX)
- **Sector**: Physical transfer unit

---

### Disk Management Policies

- **Files** are user-visible, sequential blocks.
- **Directories** map names → files.
- **Disk Blocks** addressed via LBA (Logical Block Addressing)
- **Free Space Tracking**: Bitmaps (efficient), not linked lists
- **File Header**: Tracks block locations per file

---

## File Access and Usage Patterns

- **Access Patterns**:
  - **Sequential**: Most common. Fast.
  - **Random**: e.g. paging from swap. Needs fast seeks.
  - **Content-based**: e.g. "Find record with name Alice". Usually done by databases.

- **Usage Patterns**:
  - Most **files are small**, but **large files dominate storage usage**.
  - Optimize for frequent patterns.

---

## Goals of a File System
- Fast **sequential** and **random** access
- Support **file growth/removal**
- Manage free space
- Minimize fragmentation

---

## Disk Allocation Techniques

### 1. Continuous Allocation

| Feature | Description |
|--------|-------------|
| Idea | Allocate continuous range of blocks |
| Pros | Fast access |
| Cons | External fragmentation, hard to grow |
| Use | IBM 360 |

### 2. Linked List Allocation

- Each block has a pointer to the next.
- Pros: Simple, supports file growth.
- Cons: Terrible random access; lose one block = lose all next blocks.

### 3. File Allocation Table (FAT)
- Links stored in a FAT instead of in blocks.
- Still expensive for random access unless FAT cached.

### 4. Indexed Allocation
- A file header (or inode {index node}) contains a list of all block pointers.
- Efficient random access.
- Clunky if file grows beyond index table.

### 5. Multilevel Indexed (UNIX 4.1)
- Inode has:
  - 10 direct pointers
  - 1 single indirect pointer (256 blocks)
  - 1 double indirect (256² blocks)
  - 1 triple indirect (256³ blocks)
- Allows efficient support for small and large files.
- Limit ~16GB.
- Cost of access grows with block index:
  - Block 5: 1 access
  - Block 340: 3 accesses (triple indirection)

---

## Naming and Directories

### Naming
- Translates user-visible names → inodes

### Directories
- Table of `(filename, inumber)` pairs
- Stored as files themselves
- Organized as:
  - **Flat list**
  - **Hash table**
  - **Hierarchical paths**: `/user/docs/report.txt`
  - **Hard Links**: Multiple names point to same inode
  - **Soft Links**: Shortcut that stores a pathname

### Where Are Inodes Stored?
- **Early UNIX**: Outer cylinders, fixed array (bad locality)
- **Modern UNIX**: Stored close to parent directory's blocks
  - Improves locality
  - Reliability: Easier recovery after crash

---

## File System Caching

### Buffer Cache
- Stores:
  - Disk blocks
  - Path-to-inode mappings
- Can hold **dirty blocks** (not yet written to disk)

### Policies
- **LRU** (Least Recently Used): Used for block replacement
- **Read-Ahead**: Prefetch sequential blocks
- **Tradeoff**: How much memory to assign to cache vs VM

---

## Durability & Reliability

### “Ilities”:

| Term | Meaning |
|------|---------|
| **Availability** | System can accept requests (measured in "nines") |
| **Durability** | Data can survive crashes |
| **Reliability** | System performs required functions under given conditions |

---

## Journaling File Systems

- **Write-ahead logging**:
  - All changes logged first
  - System crash? → Replay log to restore state

- **Transactions**:
  - All-or-nothing
  - Reduce corruption from crashes

- **Examples**: ext3 (Linux), XFS (Unix)

---

## RAID and Redundancy

- **RAID** = Redundant Array of Inexpensive Disks
  - Redundant copies across disks
  - Hardware/software managed
- ECC (Reed-Solomon) handles small disk defects

---

## Instructor Notes

- Understand all **allocation techniques**
- Be able to draw and explain **multilevel indexing**
- Know **inode structure** and how to locate a file
- **Durability & Journaling** are core OS design principles
- For Project 2, caching, naming, and I/O strategies matter!

---

## Diagrams to Draw

- Disk head scheduling examples (SCAN, C-SCAN)
- Block layouts: continuous, linked, FAT, indexed
- Multilevel inode structure
- Directory hierarchy and symlinks
- File caching architecture
- Journaling flow: log + commit + replay

---

## Key Takeaways

- File system bridges disk blocks → usable abstractions
- Different allocation strategies have tradeoffs
- Inodes store block maps and metadata
- Directories map names to inodes
- Caching + Journaling = performance + safety