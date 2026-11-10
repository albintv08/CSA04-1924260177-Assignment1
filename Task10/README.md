# Task 10

# TASK 10 – Measure and Compare

## 1. Introduction

A Linux operating system uses system calls to provide services to applications. These calls require transitions between user mode and kernel mode. Processes and threads also consume system resources when they are created. Measuring these operations helps evaluate the performance of the smart hospital system.

This task measures read system-call overhead using different buffer sizes, CPU time spent in user and kernel modes, and the time and resource usage associated with creating 1,000 processes and 1,000 threads.

## 2. System Calls for Different Buffer Sizes

The Task 06 benchmark reads 1 MiB of data from `/dev/zero` using different buffer sizes. The `strace` command is used to observe system calls.

### Actual measurements

| Buffer size | Actual read calls | Write calls |
|---:|---:|---:|
| 1 byte | 1,048,576 | 0 |
| 512 bytes | 2,048 | 0 |
| 4096 bytes | 256 | 0 |

**Note:** This experiment measures read-system-call overhead, not file copying. No write operations are performed. The read-call counts are from the benchmark output; the `strace` summary also includes an additional runtime read.

**Evaluation:** Increasing the buffer size greatly reduces the number of read system calls. This reduces repeated transitions between user mode and kernel mode and improves efficiency. The 4096-byte buffer required far fewer calls than the 1-byte buffer.

## 3. User Mode and Kernel Mode Execution Time

The Linux `time` command measures the execution time of a program.

- **Real time:** Total elapsed time.
- **User time:** CPU time spent executing application code in user mode.
- **System time:** CPU time spent executing kernel code on behalf of the application.

Command used: `time ./copy_bench`

### Actual measurements

| Measurement | Complete benchmark |
|---|---:|
| Real time (seconds) | 0.813 |
| User time (seconds) | 0.336 |
| System time (seconds) | 0.471 |

### Individual buffer execution times

| Buffer size | Elapsed time (seconds) |
|---:|---:|
| 1 byte | 0.792358 |
| 512 bytes | 0.001537 |
| 4096 bytes | 0.000231 |

**Evaluation:** The 1-byte buffer required significantly more time because it generated many read system calls. Larger buffers reduced the number of calls and execution time. The `real`, `user` and `system` values represent the complete benchmark, not separate timings for each buffer size.

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
| Number successfully created | 1,000 | 1,000 |
| Creation and completion time (seconds) | 0.222638 | 0.069469 |
| Maximum resident memory (KB) | 128 (child) | 9,984 (parent process) |

**Evaluation:** In this experiment, the 1,000-thread workload completed faster than the 1,000-process workload. The reported memory figures are not directly comparable because the process measurement represents a child process, while the thread measurement represents the parent process containing the threads. Processes provide stronger isolation because each process has its own virtual address space. Threads share resources and require synchronization when accessing shared data.

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
