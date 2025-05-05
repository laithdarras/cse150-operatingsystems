# Chapter 9 - Virtual Memory

## Practice Exercises

### 9.1:
- A page fault occurs when an access to a page that has not been brought into physical memory takes place. The operating system then has a specific procedure in handling a page fault. That is, the operating system first verifies the memory access and terminating the process if it is invalid. If it is valid, a free frame is located and I/O is requested to read the needed page into the free frame. Once that had been completed, the process table and page table are then updated. The instruction is then restarted.

### 9.2:
- For any page-replacement algorithm, the lower bound on the number of page faults is 'n' -- which is the number of distinct pages in it.
- For any page-replacement algorithm, the upper bound on the number of page faults is 'p' -- which is the page reference string containing all the references to be eventually brought into memory.

### 9.3:
- A stack is a "good" structure for a demand-paged environment because you can access a page from the top easily meaning nearby memory pages are likely to be used soon. The LRU policy is good to be implemented with a stack. 
- A hash table is not a "good" structure for a demand-paged environment because they jump around memory a lot depending on the key, so you might need a whole new page every time you look something up. 
- A sequential search is a "good" technique for a demand-paged environment because it goes step-by-step through memory. It is quite slow, but good for avoiding page faults.
- A binary search algorithm is not a "good" structure for a demand-paged environment because it skips around the memory, looking at the middle, then quarter, then eighth, etc. This causes it to jump across pages and miss the benefits of loading nearby data.
- A pure code approach is a "good" technique for a demand-paged environment because code that never changes can be shared and reused. 
- A vector operations approach is a "good" technique for a demand-paged environment because these work on large chunks of data stored right next to each other making it more likely the data you need is already in the same page, hence reducing page faults. 
- An indirection approach is not a "good" technique for a demand-paged environment because using pointers means memory access jumps to totally different spots, hence increasing page faults. 

### 9.4:
- Ranking these page replacement algorithms from 1 being the best and 4 being the worst according to their page fault rate. The list is:
    1. Optimal
    2. LRU
    3. Second-chance
    4. FIFO
- Which of these suffer from Belady's anomaly?
    - Belady's anomaly is the counterintuitive situation where increasing the number of page frames results in more page faults, not fewer. The algorithms that suffer from it are:
        - FIFO:
            - It replaces the oldest page in memory, regardless of whether it's still being used. It suffers from it bc it doesn't care if the page is still useful. Increasing the number of frames might cause a useful page to be pushed out later, leading to more faults when it's needed again.
        - Second-chance (Clock):
            - Like FIFO, but it gives a page a "second chance" if its use bit is set to 1. It still suffers from it bc it still fundamentally behaves like FIFO where it can still evict pages that are frequently reused but weren't recently accessed at the right time. It is better than FIFO, but it doesn't fully track usage patterns like LRU, which avoids Belady's anomaly.

### 9.5:
- Virtual memory has benefits like increased memory capacity and efficient CPU utilization, but also comes with slower performance and thrashing. The costs includes more hardware and more complex. 

### 9.6:
- Effective Access Time - Paging Device Example
    - System Specs:
        - CPU cycle time: 1 microsecond
        - Page size: 1000 words
        - Paging device: drum
            - rotational speed: 3000 rpm
            - transfer rate: 1000000 words/sec
        - 1% of instructions access a different page
            - 80% hit
            - 20% miss
                - 50% of faults require dirty page write-back
- EAT Calculations:
    1. No page access (99% of instructions):
        - 0.99 * 1 = 0.99
    2. Page hit (0.008 probability):
        - 0.008 * (1 + 1) = 0.016
    3. Page fault, clean page (0.001 probability):
        - Average rotation latency: 16,667 microseconds
        - transfer time: 1000 microseconds
        - total: 0.001 * 18000 = 18 microseconds
    4. Page fault, dirty page (0.001 probability):
        - Write old page: 1000 + 16,667
        - Read new page: 1000 + 16,667
        - total: 0.001 * 36000 = 36 microseconds
    - Total EAT = 0.99 + 0.016 + 18 + 36 = 55.006 microseconds

### 9.8:
- How many page faults would the following replacement algorithms incur?
    - Reference string: `1, 2, 3, 4, 2, 1, 5, 6, 2, 1, 2, 3, 7, 6, 3, 2, 1, 2, 3, 6`
    - Number of frames: 4
- LRU: 10 page faults
- FIFO: 14 page faults
- Optimal: 8 page faults

### 9.9:
- A paging algorithm that requires a reference bit can use the valid/invalid (0/1) bit scheme supported in hardware to simulate the reference bit. The bit is initially set to invalid. On first reference, a trap to the OS is generated. The OS will set a bit to 1 and reset the valid/invalid bit to valid. 

### 9.10:
- My newly devised page-replacement algorithm is NOT optimal if it suffers from Belady's anomaly in any test cases. By definition, an optimal algorithm replaces the page that will not be used for the longest time. Belady's anomaly occurs when an algorithm evicts a page that will be needed in the near future. An optimal algorithm would not have selected such a page.

### 9.12:
- a. CPU utilization: 13%; disk utilization: 97%
    - Low cpu and high disk utilization means that there way more page faults than processes running which means thrashing is occuring.
- b. CPU utilization: 87%; disk utilization: 3%
    - very high cpu utilization to leave things alone. you need to increase the degree of multiprogramming.
- c. CPU utilization: 13%; disk utilization: 3%
    - Increase the degree of multiprogramming.

### 9.13:
- The page table can be set up to simulate base and limit registers only if the memory is allocated in fixed-size segments. In this way, the base of a segment can be entered into the page table and the valid/invalid bit used to indicate the portion of the segment whether it's in memory or not. However, there will be some issues regarding internal fragmentation.

