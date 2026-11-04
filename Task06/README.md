# Task 6

# TASK 6 – Evaluate the Cost of System Calls

## 1. Introduction

System calls allow user programs to request services from the operating-system kernel. However, system calls involve additional processing compared with ordinary function calls. When a program copies a large file using repeated read and write operations, the number of system calls can significantly affect performance.

For a hospital database backup program, reducing unnecessary system calls helps improve copying speed and system efficiency.

## 2. Why System Calls Cost More Than Ordinary Function Calls

An ordinary function call generally transfers control within the same process and execution mode. A system call requires a controlled transition from user mode to kernel mode.

The additional operations may include:
- Saving and restoring processor state.
- Switching execution privilege from user mode to kernel mode.
- Validating system-call arguments.
- Checking permissions and file descriptors.
- Performing the requested kernel operation.
- Returning the result and switching back to user mode.

Therefore, frequent small system calls can increase CPU overhead and reduce application performance.

## 3. Effect of Buffer Size on System Calls

Buffer size determines how many bytes are transferred during each read or write operation.

For a file of size `n` and buffer size `b`, the approximate number of read calls, including the final call that detects end-of-file, is:

\[
\text{Read calls}=\left\lceil\frac{n}{b}\right\rceil+1
\]

For the given 10,000-byte file:

| Buffer size | Data read calls | Final EOF call | Total read calls |
|---:|---:|---:|---:|
| 1 byte | 10,000 | 1 | 10,001 |
| 512 bytes | 20 | 1 | 21 |
| 4096 bytes | 3 | 1 | 4 |

A larger buffer reduces the number of system calls. However, an excessively large buffer may consume unnecessary memory.

## 4. How Library Buffering Improves Performance

C standard library functions such as `fread()` and `fwrite()` use internal buffers to combine smaller operations into larger transfers.

For example, instead of requesting one byte from the kernel repeatedly, the library can read a larger block into its internal buffer and provide individual bytes to the application from memory.

Advantages:
- Reduces the number of system calls.
- Reduces user-mode/kernel-mode transitions.
- Improves file-copying performance for many small operations.
- Provides convenient file-handling functions.

The disadvantage is additional memory consumption for the library's internal buffers.

## 5. Completed C Program

The following program copies a 10,000-byte file using the `read()` and `write()` system calls with buffer sizes of 1, 512 and 4096 bytes.

### Source code: `copy_bench.c`

```c
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

long copy_file(const char *src, const char *dst, size_t bufsize)
{
    char buf[8192];

    if (bufsize == 0 || bufsize > sizeof(buf))
        return -1;

    int in = open(src, O_RDONLY);
    if (in < 0) return -1;

    int out = open(dst, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (out < 0) {
        close(in);
        return -1;
    }

    long calls = 0;
    ssize_t n;

    while (1) {
        n = read(in, buf, bufsize);
        calls++;

        if (n == 0)
            break;

        if (n < 0) {
            if (errno == EINTR)
                continue;
            close(in);
            close(out);
            return -1;
        }

        ssize_t written = 0;

        while (written < n) {
            ssize_t w = write(out, buf + written, n - written);

            if (w < 0) {
                if (errno == EINTR)
                    continue;
                close(in);
                close(out);
                return -1;
            }

            if (w == 0) {
                close(in);
                close(out);
                return -1;
            }

            written += w;
        }
    }

    close(in);
    close(out);

    return calls;
}

int main(void)
{
    FILE *f = fopen("records.dat", "w");
    if (f == NULL) {
        perror("fopen");
        return 1;
    }

    for (int i = 0; i < 10000; i++)
        fputc('A' + i % 26, f);

    fclose(f);

    size_t sizes[] = {1, 512, 4096};

    for (int i = 0; i < 3; i++) {
        long result = copy_file("records.dat", "copy.dat", sizes[i]);

        if (result < 0) {
            perror("copy_file");
            unlink("records.dat");
            unlink("copy.dat");
            return 1;
        }

        printf("buffer %4zu bytes: %5ld read() calls\n",
               sizes[i], result);
    }

    unlink("records.dat");
    unlink("copy.dat");

    return 0;
}
```

## 6. Performance Analysis

The expected measurements are:

| Buffer size | Read calls | Evaluation |
|---|---:|---|
| 1 byte | 10,001 | Very high system-call overhead |
| 512 bytes | 21 | Significantly reduced overhead |
| 4096 bytes | 4 | Lowest number of read calls among the tested sizes |

The 1-byte buffer performs the largest number of system calls because it transfers very little data per request. The 512-byte buffer reduces this overhead substantially. The 4096-byte buffer performs best among the three tested configurations.

## 7. Best Buffer Size for the Hospital Backup Program

Based on the given measurements, a 4096-byte buffer is the best choice among the three tested sizes. It requires only four read calls for the 10,000-byte test file, compared with 10,001 calls for a 1-byte buffer.

For a real hospital database backup, the final buffer size should also be tested using larger backup files and realistic storage devices. Larger buffers may improve throughput further, but they also require more memory. The choice should balance copying speed, memory consumption, reliability and the number of concurrent backup operations.

## 8. Conclusion

The number of system calls directly affects file-copying performance because each system call introduces additional kernel-transition and processing overhead. Increasing buffer size reduces the number of read and write operations. Library buffering through `fread()` and `fwrite()` also reduces frequent system calls by transferring data in blocks. Based on the supplied experiment, 4096 bytes is the most efficient of the three tested buffer sizes for the hospital backup example.