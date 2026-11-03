# Task 5

# TASK 5 – Examine System Calls

## 1. Introduction

A system call is a mechanism through which a user-level program requests a service from the operating system kernel. Applications cannot directly access protected hardware or kernel resources. Therefore, they use system calls to perform operations such as reading files, creating processes, accessing devices and communicating with other processes.

System calls provide a controlled interface between user applications and the operating system.

## 2. Categories of System Calls

| Category | Purpose | Examples |
|---|---|---|
| Process Control | Creates, executes and terminates processes. | `fork()`, `exec()`, `exit()`, `wait()` |
| File Management | Creates, opens, reads, writes and closes files. | `open()`, `read()`, `write()`, `close()` |
| Device Management | Requests access to hardware devices and controls their operations. | `ioctl()`, `read()`, `write()` |
| Information Maintenance | Obtains or updates system and process information. | `getpid()`, `time()`, `uname()` |
| Communication | Enables data exchange between processes. | `pipe()`, `socket()`, `send()`, `recv()` |
| Protection | Controls access permissions and security. | `chmod()`, `chown()`, `access()` |

These categories allow applications to use operating-system services in a secure and organized manner.

## 3. Step-by-Step Working of the `read()` System Call

The `read()` system call is used to obtain data from a file, device or another input source.

The process takes place as follows:

1. **Library Call:** The application calls the `read()` function through the C library interface.
2. **System Call Request:** The library prepares the system-call number and required arguments.
3. **Trap Instruction:** A special instruction transfers control from the user program to the kernel.
4. **Mode Switch:** The CPU changes from user mode to kernel mode, allowing the operating system to execute privileged operations.
5. **Kernel Processing:** The kernel checks the file descriptor, validates the buffer and requested size, and obtains the requested data.
6. **Return to User Mode:** The kernel returns the number of bytes read or an error indication.
7. **Program Continues:** Execution resumes in the application, which can process the received data.

**Flow:**

Application → C Library → Trap/System Call Instruction → Kernel Mode → Kernel Performs Read Operation → Return Value → User Mode → Application Continues.

## 4. Methods of Passing Parameters to the Kernel

The operating system needs information such as a file descriptor, memory address and number of bytes to perform a system call. Parameters can be passed in three main ways:

### a) Registers

Parameters are placed directly into CPU registers. This method is fast because registers are directly accessible to the processor.

### b) Memory Block

Parameters are stored in a block of memory, and the address of that block is passed through a register. This is useful when several parameters must be transferred.

### c) Stack

Parameters are pushed onto the program stack. The operating system or system-call interface retrieves them when processing the request.

The method used depends on the processor architecture and operating-system system-call convention.

## 5. Using `strace` to Examine System Calls

`strace` is a Linux command-line debugging tool that traces system calls made by a program. It displays the system-call name, arguments, return values and errors.

For example:

```bash
strace ./read_demo
```

It can display operations such as:

```text
openat(...)
read(...)
write(...)
close(...)
```

The `strace` command helps developers understand how applications interact with the kernel, identify file-access problems and investigate performance issues.

## 6. Alternative Concept and Complexity Analysis

An application can use C standard library functions such as `fopen()`, `fread()` and `fwrite()` instead of directly using the `open()`, `read()` and `write()` system calls.

The C standard library provides buffered file I/O. It stores data temporarily in a memory buffer and transfers data in larger blocks rather than making a system call for every small read or write.

### Comparison

| Direct System Calls | Buffered C Library Functions |
|---|---|
| Uses `open()`, `read()`, `write()` and `close()`. | Uses `fopen()`, `fread()`, `fwrite()` and `fclose()`. |
| Application controls the size of each read or write request. | Library manages an internal buffer. |
| Small requests can cause many system calls. | Multiple small operations can be combined into fewer system calls. |
| Requires less library-managed buffering. | Requires extra memory for the buffer. |

### System Call Complexity

Let:
- `n` = total number of bytes in the file.
- `b` = number of bytes transferred in each direct system call.
- 4096 bytes = an illustrative library buffer size.

For direct system calls, the approximate number of read or write operations is:

**n / b**

With library buffering, the approximate number of underlying read or write operations is:

**n / 4096**

For example, for a file of 1 MB (1,048,576 bytes):

- With a direct buffer of 100 bytes: approximately 10,486 read operations.
- With a 4096-byte buffer: approximately 256 read operations.

These figures are illustrative and exclude additional calls such as opening and closing the file. Actual counts depend on the buffer size, file size, operating system and program implementation.

### Extra Buffer Space

Buffered library functions require additional memory to maintain their internal buffer. For example, a 4096-byte buffer requires approximately 4 KB of extra memory per buffered file stream.

Although this increases memory usage, it reduces frequent transitions between user mode and kernel mode. Therefore, buffered I/O generally improves performance when applications perform many small file operations.

## 7. Implementation and Evidence

The following C program demonstrates how a program uses the `open()`, `read()`, `write()` and `close()` system calls.

### Source Code: `read_demo.c`

```c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    char buffer[100];
    ssize_t bytes;

    fd = open("sample.txt", O_RDONLY);

    if (fd < 0) {
        perror("open");
        return 1;
    }

    bytes = read(fd, buffer, sizeof(buffer) - 1);

    if (bytes < 0) {
        perror("read");
        close(fd);
        return 1;
    }

    buffer[bytes] = '\0';

    printf("Data read from file: %s\n", buffer);

    close(fd);

    return 0;
}
```

### Execution Commands

```bash
echo "Smart Hospital Operating System" > sample.txt
gcc read_demo.c -o read_demo
./read_demo
```

### Trace System Calls

```bash
strace -e trace=openat,read,write,close ./read_demo
```

The trace should show file-opening, reading, writing and closing operations. The exact output may vary depending on the Linux environment and C library.

**Evidence to attach:**
1. Screenshot of the C source code.
2. Screenshot showing successful compilation and program execution.
3. Screenshot of the `strace` output showing the `openat()`, `read()`, `write()` and `close()` calls.

## 8. Conclusion

System calls provide the essential communication interface between user applications and the operating-system kernel. Different categories of system calls support process management, file operations, device access, communication, information maintenance and protection. The `read()` system call demonstrates how control moves from user mode to kernel mode and returns to the application. Tools such as `strace` help examine this interaction. Buffered C library functions reduce the number of system calls by transferring data in larger blocks, improving performance at the cost of additional memory.
