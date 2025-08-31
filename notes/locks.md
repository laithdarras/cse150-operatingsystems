# CSE 150 – Lecture 06: Synchronization – Atomic Operations & Locks

---

## 🧠 Key Concepts

- **Synchronization** ensures multiple threads or processes can operate safely in shared environments.
- **Race conditions** arise when multiple threads access shared data simultaneously without proper coordination.
- **Atomic operations** are indivisible — they complete without interruption.
- This lecture sets the foundation for building **locks**, which prevent race conditions.

---

## Lecture Notes

### What is Synchronization?
- Synchronization is used to control **concurrent access** to shared resources.
> The goal is to avoid **deadlock** and **race conditions**!

### Race Conditions
- Happen when the **order of thread execution** affects the result.
- Critical when threads read-modify-write shared variables.

#### Example:
```c
x = x + 1;
// Translates to:
t1 = x;
t1 = t1 + 1;
x = t1;
```

---

### Locks
- Locks ensure only one thread enters a critical section at a time.
- Prevents simultaneous access to shared resources.
- Using Locks:
    - Lock.acquire() → Enter critical section
    - Lock.release() → Exit critical section

---

### Atomic Operations
- What is an Atomic Operation?
    - An operation that completes entirely or not at all.
    - Prevents interference from other threads.

- Implementing Synchronization Requires:
    1. Atomicity for lock implementation
    2. Support for test-and-set, disable interrupts, or similar hardware-level features

---

### Methods for Implementing Locks
1. Disabling Interrupts
    - Turn off interrupts to ensure no context switch
    - Good for uniprocessors only
    - Problems:
        - Doesn’t work on multiprocessors
        - Dangerous if interrupts stay disabled too long

2. Test-and-Set (Hardware Support)
- Hardware primitive: reads a variable and sets it to 1 atomically
- Spinlock implementation
- Can cause busy waiting
```c
while (TestAndSet(&lock)) {
    // spin
}
```
3. Compare-and-Swap
- Atomic compare and update value
- Safer and more general than Test-and-Set

---

### Spinlocks vs Sleeping Locks
| Type           | Pros                    | Cons                       |
|----------------|-------------------------|----------------------------|
| **Spinlock**    | Fast if wait is short    | Wastes CPU cycles          |
| **Sleeping Lock** | Doesn't waste CPU       | Slower to context switch   |

---

### Key Takeaways
- Synchronization is essential to coordinate threads
- Locks are built from atomic operations
- Spinlocks are simple but wasteful