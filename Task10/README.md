# Task 10

# TASK 10 – Measure and Compare

## 1. Introduction

A Linux operating system uses system calls to provide services to applications. These calls require transitions between user mode and kernel mode. Processes and threads also consume system resources when they are created. Measuring these operations helps evaluate the performance of the smart hospital system.

This task measures system calls during file copying, CPU time spent in user and kernel modes, and the time and memory required to create 1,000 processes and 1,000 threads.

## 2. System Calls for Different Buffer Sizes

The `strace -c` command is used to count system calls made by a program and summarize the time spent in those calls.

The file-copy program from Task 06 is tested using different buffer sizes:

- 1 byte
- 512 bytes
- 4096 bytes

### Expected behaviour

A small buffer requires more read and write operations because the file is transferred in many small pieces. A larger buffer reduces the number of system calls.

For a 10,000-byte file, the approximate number of successful read operations, excluding the final end-of-file read, is:

| Buffer size | Expected data read operations |
|---:|---:|
| 1 byte | 10,000 |
| 512 bytes | 20 |
| 4096 bytes | 3 |

The actual system-call counts reported by `strace` may be higher because of end-of-file checks, file opening, closing, output, and other library operations.

### Actual measurements

| Buffer size | Actual read calls | Actual write calls | Total system calls |
|---:|---:|---:|---:|
| 1 byte | To be measured | To be measured | To be measured |
| 512 bytes | To be measured | To be measured | To be measured |
| 4096 bytes | To be measured | To be measured | To be measured |

**Evaluation:** The results should show that increasing the buffer size reduces the number of read and write system calls. This reduces repeated transitions between user mode and kernel mode. However, an excessively large buffer consumes more memory, so a suitable buffer size must balance memory use and performance.

## 3. User Mode and Kernel Mode Execution Time

The Linux `time` command measures the execution time of a program.

It reports three important values:

- **Real time:** Total elapsed time from start to completion.
- **User time:** CPU time spent executing application code in user mode.
- **System time:** CPU time spent executing kernel code on behalf of the application.

Example command:

`time ./copy_bench`

### Actual measurements

| Buffer size | Real time (seconds) | User time (seconds) | System time (seconds) |
|---:|---:|---:|---:|
| 1 byte | To be measured | To be measured | To be measured |
| 512 bytes | To be measured | To be measured | To be measured |
| 4096 bytes | To be measured | To be measured | To be measured |

**Evaluation:** Small buffers generally cause more system calls and more kernel activity. Larger buffers can reduce system time by transferring more data per call. Real-time measurements may vary because of CPU load, storage speed, caching and virtual-machine performance.

## 4. Creating 1,000 Processes and 1,000 Threads

A process is an independent running program with its own virtual address space and operating-system resources. A thread is an execution unit within a process. Threads belonging to the same process share its address space and many resources.

### Process creation using fork()

The `fork()` system call creates a child process. The child initially has a separate virtual address space, commonly implemented using copy-on-write memory pages.

Creating 1,000 processes requires repeated calls to `fork()`. The operating system must allocate and manage process-related structures, page tables and scheduling information.

### Thread creation using pthread_create()

The `pthread_create()` function creates a new thread within the same process.

Threads share the process's code, data and heap. Each thread has its own stack and execution state. Therefore, thread creation generally requires less memory-management overhead than process creation.

### Actual measurements

| Measurement | 1,000 processes | 1,000 threads |
|---|---:|---:|
| Number successfully created | To be measured | To be measured |
| Creation and completion time (seconds) | To be measured | To be measured |
| Maximum resident memory (KB) | To be measured | To be measured |

**Evaluation:** Thread creation is generally faster and uses less memory than process creation because threads share the same address space and many resources. Processes provide stronger isolation because each process has its own virtual address space. Threads are more lightweight but require synchronization when accessing shared data.

## 5. Alternative Concept and Complexity Analysis

If threads are created instead of processes, the expected result is a reduction in creation time and memory-management overhead.

### Processes

- Each process has its own virtual address space.
- The operating system manages separate process structures and memory mappings.
- Copy-on-write reduces the immediate cost of copying memory after `fork()`.
- Processes provide stronger isolation and fault containment.
- Communication between processes may require pipes, sockets or shared memory.

### Threads

- Threads share code, data and heap memory.
- Each thread has its own stack and CPU execution state.
- Thread creation usually requires fewer resources.
- Communication is easier through shared memory.
- Synchronization is necessary to avoid race conditions.

### Complexity comparison

For N creations, both approaches require approximately O(N) creation operations. However, process creation generally has higher per-creation resource-management overhead than thread creation.

The actual performance difference depends on Linux configuration, available memory, process limits, thread-stack settings and system load.

### Hospital application

For the smart hospital:

- Independent and security-sensitive services should use separate processes for stronger isolation.
- Parallel image-processing tasks can use multiple threads when shared data access is carefully synchronized.
- Bedside monitor processing should use predictable scheduling and must not be delayed by unnecessary background tasks.

## 6. Overall Evaluation

The measurements help evaluate the earlier design decisions.

1. Larger file-copy buffers should reduce system-call frequency and kernel overhead.
2. User and system time measurements show how much CPU time is spent in application code and operating-system services.
3. Thread creation should generally be faster and more memory-efficient than process creation.
4. Processes provide stronger isolation, which is important for protecting critical hospital services.
5. The best design balances performance, memory usage, reliability and security rather than choosing only the fastest option.

## 7. Conclusion

Linux measurements provide practical evidence of operating-system performance. Larger I/O buffers reduce repeated system calls, while threads generally require fewer resources than processes. However, processes provide stronger memory isolation. A smart hospital should use efficient I/O buffering, threads for suitable parallel tasks and separate processes for critical services that require stronger protection.
