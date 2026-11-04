# TASK 7 – Evaluate Process Control System Calls

## 1. Introduction

A command shell is a program that accepts commands from users and executes them through the operating system. On a database server, the shell may start backup utilities, database maintenance programs and monitoring tools.

The operating system provides process-control system calls to create, execute, synchronize and terminate processes. The important operations include `fork()`, `exec()`, `wait()` and `exit()`.

## 2. Functions of Process-Control System Calls

| System call/function | Purpose |
|---|---|
| `fork()` | Creates a new child process by duplicating the calling process. |
| `exec()` | Replaces the current process image with a new program. Functions such as `execlp()` are members of the exec family. |
| `wait()` | Suspends the parent until one of its child processes terminates and collects its termination status. |
| `waitpid()` | Waits for a specified child process or a selected group of children. |
| `exit()` | Terminates a process after flushing standard I/O streams and running registered termination handlers. |
| `_exit()` | Terminates a process immediately without performing C library stream flushing or registered exit handlers. |

These operations allow the shell to manage commands while maintaining process isolation and obtaining execution results.

## 3. How a Shell Executes a Command

When a user enters a command, the shell performs the following operations:

1. Reads and interprets the command.
2. Creates a child process using `fork()`.
3. The child calls an `exec()` family function to replace its program with the requested command.
4. The parent shell calls `wait()` or `waitpid()` to wait for the child.
5. The operating system records the child's termination status.
6. The parent retrieves the status using macros such as `WIFEXITED()` and `WEXITSTATUS()`.
7. The shell displays the result and accepts another command.

For example, when the shell executes `expr 6 * 7`, the child process runs the expression and prints `42`. The parent waits for the child and obtains exit status `0`, indicating successful execution.

## 4. Zombie and Orphan Processes

### Zombie Process

A zombie is a process that has terminated, but whose parent has not yet collected its termination status using `wait()` or `waitpid()`.

The operating system retains a small process-table entry containing information such as the process ID and exit status. This allows the parent to collect the result later.

**Prevention:** The parent should call `wait()` or `waitpid()` to collect terminated children's statuses.

### Orphan Process

An orphan is a process whose parent terminates before the child process finishes.

The operating system reassigns the orphan to an appropriate system process, commonly PID 1 or another designated subreaper. When the orphan eventually terminates, its new parent collects its exit status.

### Comparison

| Zombie | Orphan |
|---|---|
| Child has already terminated. | Child is still running after its parent terminates. |
| Exit status has not been collected. | Parent process no longer exists. |
| Requires status collection by the parent or reaper. | Reassigned to a system process or subreaper. |

## 5. Why fork() Followed by exec() Is Used

Using `fork()` followed by `exec()` separates process creation from program execution.

Advantages:

- The parent shell remains active while the child executes another program.
- The child can modify its environment, file descriptors and I/O redirection before executing the command.
- The parent can wait for the child and obtain its exit status.
- Multiple commands can run independently.
- The shell can manage foreground and background jobs.

A single process-creation operation could combine some of these steps, but separating them provides flexibility and supports the traditional UNIX process model.

## 6. Completed C Program

The following program demonstrates the shell executing two jobs. The first child runs the `expr` command, and the second child terminates with exit status 3.

### Source code: process_control.c

```c
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    printf("shell: running job 1\n");
    fflush(stdout);

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        execlp("expr", "expr", "6", "*", "7", (char *)NULL);
        perror("execlp");
        _exit(127);
    }

    int status;

    if (waitpid(pid, &status, 0) < 0) {
        perror("waitpid");
        return 1;
    }

    if (WIFEXITED(status))
        printf("job 1 exit status %d\n", WEXITSTATUS(status));

    printf("shell: running job 2\n");
    fflush(stdout);

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0)
        _exit(3);

    if (waitpid(pid, &status, 0) < 0) {
        perror("waitpid");
        return 1;
    }

    if (WIFEXITED(status))
        printf("job 2 exit status %d\n", WEXITSTATUS(status));

    return 0;
}
```

## 7. Buffer Flushing Analysis

The `fflush(stdout)` function forces pending output in the standard output buffer to be written before `fork()` creates a child process.

### Why is flushing necessary?

When `fork()` executes, the child receives a copy of the parent's memory, including any pending standard I/O buffer contents.

If the buffer is not flushed, both processes may later write the same buffered text, causing duplicate output.

### Why does redirection cause duplication?

When standard output is connected to a terminal, it is normally line-buffered. When redirected to a regular file, it is normally fully buffered.

Without the second `fflush(stdout)`, the message:

`"shell: running job 2\n"`

may remain in the parent's output buffer when `fork()` occurs.

The child inherits a copy of that buffer. If the child calls `exit(3)`, the C library flushes its inherited buffer. Later, the parent also flushes its copy when it exits. Therefore, the message appears twice in the output file.

Using `_exit(3)` avoids flushing the inherited C library buffer in the child.

### Experiment

To demonstrate this, remove the second `fflush(stdout)` and change `_exit(3)` to `exit(3)`.

Compile and redirect the output:

```bash
gcc -O2 process_control.c -o process_control
./process_control > output.txt
cat output.txt
```

The message `shell: running job 2` should appear twice in the file.

This experiment demonstrates why flushing output before `fork()` and using `_exit()` in a child after a failed `exec()` are important.

## 8. Alternative Concept and Complexity Analysis

An alternative to `fork()` followed by `exec()` is `posix_spawn()`. It provides a combined interface for creating a process and starting a specified program.

Threads are another alternative for concurrent work, but they share the same process address space and do not provide the same isolation as separate processes.

### Comparison

| Factor | fork() + exec() | posix_spawn() | Threads |
|---|---|---|---|
| Process creation | Creates a child and then replaces its program | Combines process creation and program execution | Creates another thread within the same process |
| Memory | Uses copy-on-write initially | Generally avoids a full application-level fork copy | Shares process memory |
| Isolation | Strong process isolation | Strong process isolation | Limited isolation |
| Startup overhead | May involve two operations | Can be more efficient on some systems | Usually lower thread-creation overhead |
| Failure impact | Child failure is isolated from parent | Child failure is isolated from parent | A serious process-level failure may affect all threads |

### Starting 1,000 Commands

For 1,000 commands, the total startup time depends on process-creation overhead, executable loading, scheduling, system load and the commands themselves.

The traditional `fork()` and `exec()` method involves two operations for each command. `posix_spawn()` may reduce overhead by combining process creation and program execution. Threads may start more quickly, but they are not a direct replacement when each command requires a separate executable and independent security boundary.

### Memory and Copy-on-Write

With `fork()`, Linux commonly uses copy-on-write. The parent and child initially share physical memory pages. A page is copied only when one process modifies it.

Therefore, `fork()` does not normally duplicate all physical memory immediately. `exec()` then replaces the child's address space with the new program.

With `posix_spawn()`, the operating system can use an efficient implementation that avoids a full fork-style address-space copy.

Threads share the same address space, reducing memory requirements, but shared data must be synchronized to prevent race conditions.

### Evaluation

For a hospital database server, `posix_spawn()` can be a suitable alternative for launching many independent maintenance commands because it provides process isolation with a convenient creation interface.

The `fork()` and `exec()` approach remains flexible and widely used. Threads are more suitable for tasks that need shared data and frequent communication, rather than independent database maintenance commands that require separate failure boundaries.

## 9. Conclusion

Process-control system calls allow a command shell to create, execute and manage programs. `fork()` creates a child, `exec()` loads a new program, and `waitpid()` collects the child's termination status. Zombie and orphan processes demonstrate the importance of correct process management. Flushing output before `fork()` prevents duplicated buffered output, while `_exit()` avoids flushing inherited C library buffers in a child. For a hospital database server, process isolation and reliable exit-status handling are important when executing backup and maintenance commands.