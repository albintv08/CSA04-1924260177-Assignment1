# CSA04 – Operating Systems Assignment 1
**Title:** Evaluate and Justify the Operating-System Design of a Smart Hospital  
**Student:** Albin T V  
**Register number:** 1924260177  
**Nature:** Individual assignment

## Environment
Use GitHub Codespaces (Ubuntu Linux). Record actual environment details with:
```bash
uname -a
cat /etc/os-release
gcc --version
```

## Compile
```bash
gcc -std=c11 -Wall -Wextra -O2 Task06/copy_bench.c -o Task06/copy_bench
gcc -std=c11 -Wall -Wextra -O2 Task07/process_control.c -o Task07/process_control
gcc -std=c11 -Wall -Wextra -O2 -pthread Task10/process_thread_bench.c -o Task10/process_thread_bench
```

## Run
```bash
./Task06/copy_bench
./Task07/process_control
./Task10/process_thread_bench
```

## Trace and timing
```bash
sudo apt-get update && sudo apt-get install -y strace
strace -c ./Task06/copy_bench
/usr/bin/time -v ./Task06/copy_bench
/usr/bin/time -v ./Task07/process_control
```

## Repository layout
`Task01` through `Task12` hold task notes, code, data and evidence. Add actual terminal screenshots to `screenshots/`. Each task should have at least one meaningful commit.

## Evidence checklist
- [ ] Actual GCC and Linux version recorded
- [ ] Task 6 and Task 7 compiled and executed
- [ ] Task 10 repeated measurements recorded
- [ ] `strace -c` and `/usr/bin/time -v` output captured
- [ ] Genuine terminal screenshots added
- [ ] Replace the repository URL placeholder in the report with the real URL
- [ ] Commit progressively, not as a single final upload

**Important:** Timing varies by Codespace host/load. Do not present invented timings or screenshots as actual measurements.
