# CSE 150 – Lecture 18: I/O Systems

---

## Key Concepts

- **Dual-mode operation** (user vs kernel mode)
- **System calls**: interface for user programs to access kernel functions (e.g. `open()`, `read()`, `write()`)
- **I/O devices** are diverse in behavior, speed, and structure - yet the OS must present a **uniform interface**
- **Interrupts vs Polling**: Two mechanisms for handling I/O device communication
- **Device drivers**: Kernel components that interact directly with hardware
- **Blocking vs Non-blocking vs Asynchronous I/O**
- **Memory-mapped I/O**
- **Direct Memory Access (DMA)**
- **I/O request lifecycle**
- Understanding **processor interaction with I/O** (key for Project 2)

---

## In-Depth

### Dual-Mode Operation (User <--> Kernel)
- A **mode bit** specifies current mode (User or Kernel)
- **System Calls** are used by users to switch to kernel mode for I/O
  - Examples:
    - `open()`, `close()`, `read()`, `write()`, `lseek()`
    - File ops: `mkdir()`, `unlink()`, `rmdir()`
- **Interrupts** are always handled in kernel mode

---

### What is the Role of I/O?
- Without I/O, computers can't communicate with external world
- **Challenges**:
  - Devices are unreliable (failures, errors)
  - Devices have different and unpredictable speeds
  - Need **standardization** and **reliability**! (this is the goal of the IO system)

---

### Operational Parameters of I/O
- **Data Granularity**:
  - Byte devices: e.g. keyboard, mouse
  - Block devices: e.g. disks, SSDs
- **Transfer Mechanism**:
  - **Polling**: CPU checks device periodically
  - **Interrupts**: Device notifies CPU when ready
- **Solution**: Combine both polling and interrupts based on context

---

### Goal of the I/O Subsystem
- Present a **uniform interface** for all devices
  - So that user code doesn't need to change for different hardware

```c
FILE *fd = fopen("/dev/something", "rw");
for (int i = 0; i < 10; i++) {
    fprintf(fd, "Count %d\n", i);
}
close(fd);
```
- This works the same for multiple devices!

---

### Device Drivers

- **Device drivers** are kernel-level components that **interact directly with the hardware**
- They are like the layer between hardware and the OS
- **Users never directly interact with drivers**, instead they use system calls like:
  - `open()`, `read()`, `write()`, `close()`, `ioctl()`

#### Responsibilities of a Device Driver:
- Understand the **hardware protocol** for the device
- Translate generic OS commands into device-specific instructions
- Decide on a **strategy** to handle data:
  - **Polling**: Check if device is ready
  - **Interrupts**: Wait for device signal
  - **Asynchronous**: Notify upon readiness

#### Why Important?
- **All I/O** passes through drivers; this is key to reliability and performance
- Having standard drivers means **users can code once** and have it work across devices
- For **Project 2**, we will implement basic driver-like interfaces:
  - `read()`, `write()`, `open()`, `close()`, `strategy()`

> Think of drivers as device-specific "translators" that allow the OS to "speak" to any piece of hardware.


---

### Types of Devices

| Device Type        | Examples                          | Access Type | Syscalls                         |
|--------------------|-----------------------------------|-------------|----------------------------------|
| Block Devices       | Hard Drives, SSDs, USB Drives     | Block       | `open()`, `read()`, `seek()`, etc. |
| Character Devices   | Keyboards, Mice, Serial Ports     | Byte        | `get()`, `put()`, etc.           |
| Network Devices     | Ethernet, Wi-Fi, Bluetooth        | Stream      | Sockets API (covered later when discussing networking)                      |



---

### User vs Kernel Interaction Timing (I/O Modes)

| I/O Mode         | Description                                                       |
|------------------|-------------------------------------------------------------------|
| Blocking         | Process sleeps until I/O is complete                              |
| Non-Blocking     | Call returns immediately, even if I/O isn't ready                 |
| Asynchronous     | Kernel later notifies user when I/O completes (usually via ready queue) |


--- 

### Kernel vs User-Level Drivers
- **Kernel Drivers:**
    - For critical devices like displays
    - Must be efficient and stable
    - Limited memory capacity, no blocking
- **User Drivers:**
    - Non-threatening devices like USB drives
    - More flexible, easier to implement
    - Can use threads, blocking operations

---

### Memory-Mapped IO
- Device registers mapped to physical memory addresses
- E.g. Writing to video memory at `0x8000F000` changes what’s shown on the screen.
- Writing to memory region updates device output

---

### Data Transfer Mechanisms

| Method              | Description                                      | Pros                  | Cons                    |
|---------------------|--------------------------------------------------|------------------------|-------------------------|
| Programmed I/O      | CPU reads/writes to device registers directly    | Simple, easy to implement | CPU-intensive, slow     |
| Interrupt Driven I/O| Device interrupts CPU when ready                 | More efficient than polling | Slightly more complex   |
| DMA (Direct Memory Access) | Device moves data directly to memory         | High performance       | Requires extra hardware |

> Note: DMA reduces CPU overhead by allowing hardware to interact directly with memory

---

### Kernel IO Structure
- **Top Half**: Handles syscalls, initiates IO
- **Bottom Half**: Runs on interrupt, completes the IO, wakes processes
- **Life Cycle of an IO Request**:
    - 1. User makes syscall
    - 2. Kernel passes to top half of driver
    - 3. Top half interacts with hardware or queues operation
    - 4. Bottom half is triggered by hardware interrupt
    - 5. Process is notified or resumed

---

## Instructor's Remarks
- Know **at least 2 syscall examples for the exam**
- Project 2 will have us implement `open`, `read`, `write`, `strategy`, `iotctl`
- Understand how interrupts and polling are combined
- Focus on processor-to-device interaction and lifecycle of IO requests
- **Display Controller example**: memory-mapped control with dedicated address blocks
    - Changing data in memory directly updates display

---

## Key Takeaways
- The IO system **standardizes communication** with hardware
- **Interrupts and polling** both have use cases - often combined
- **Drivers live in the kernel** and enable the OS to interact with different devices
- Project 2 will directly test understanding of these concepts