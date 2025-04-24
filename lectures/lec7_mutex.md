# CSE 150 – Lecture 7: Mutual Exclusion

---

## Key Concepts

- **Critical Section**: A part of the code where shared resources are accessed and thus need mutual exclusion.
- **Atomic Operation**: An operation that always runs to completion or not at all. It’s indivisible.
- **Locks**: Mechanism for synchronizing access to shared resources.
- **Busy Waiting vs. Sleeping**: Two styles of waiting for a lock.
- **Interrupt Control**: Used in early lock implementations, but problematic in multiprocessors or user-level code.
- **Test-and-Set** and **Compare-and-Swap**: Atomic instructions used to build spinlocks.
- **Too Much Milk Problem**: Illustrates challenges in ensuring mutual exclusion.

---

## Lecture Notes

### Synchronization Problem
- Example with two threads incrementing a balance –> causes **race condition**.
- Need for **atomicity** to avoid interleaved execution.

---

### Too Much Milk Solutions

#### Solution #2 (Not Good)
- Each thread leaves a note, then checks for other’s note.
- Unsafe -> possible interleaving can cause two purchases.

#### Solution #2.5 (Also Not Good)
- Leaves note **after** check.
- Still flawed –> concurrent milk purchase possible.

#### Solution #3 (Better)
- Each thread waits if it sees the other’s note.
- Works, but:
  - Code is asymmetric.
  - Uses **busy waiting**.
  - Doesn’t scale to many threads.

#### Solution #4 – Using Locks (Even Better)

```c
milklock.Acquire();
if (noMilk) buyMilk();
milklock.Release();
```
- Simple and elegant using a lock abstraction.
- Critical section is between Acquire() and Release().

---

### Why Use Threads?
- Enable parallelism, shared resources, modularity.
- Threads must sometimes wait on others (ThreadJoin).
- OS manages these threads via scheduling and queues.

---

## Implementing Locks

### Naive Approach (Disabling Interrupts)
```c
LockAcquire() {
    disable interrupts;
}
LockRelease() {
    enable interrupts;
}
```
- Prevents preemption during critical section.
- Dangerous: a user thread can disable interrupts and hog the CPU.

### Improved Lock  (Disable Interrupts Only Around Lock Access)
- Puts thread to sleep if lock is unavailable.
- Leaves the critical section interruptible, improving performance.

### Hardware-based Lock Instructions
```c
test&set(&addr) {
    result = *addr;
    *addr = 1;
    return result;
}
```
- Examples: test&set, swap, compare&swap
- Work in multi-core settings where disabling interrupts doesn’t help.

### Spinlocks
```c
while (test&set(value));  // busy wait
```
- Good for short waits
- Wastes CPU cycles

### Sleeping Locks
- Use test&set to acquire a lock.
- Sleep if already taken instead of spinning forever.

---

### Professor's Notes
- Locks are foundational – critical for safe multithreading.
- Use ThreadFork() and ThreadJoin() to coordinate threads.
- Yield() allows a thread to voluntarily give up the CPU.
- Always call ThreadHouseKeeping() when switching threads.
- OS can disable or mask interrupts to manage concurrency.
- Understand differences between user/kernel level locking strategies.

---

### Key Takeaways
- Atomicity is essential for correct concurrent execution.
- Busy waiting wastes CPU – use accordingly.
- Sleeping locks are more efficient but involve context switching.
- test&set allows scalable and efficient lock implementation.
- OS coordinates concurrent threads using locks and queues.