# Task 9

# TASK 9 – Evaluate the Memory Hierarchy and I/O Systems

## 1. Introduction

A smart hospital handles different types of data, including MRI images, electronic patient records and continuous readings from bedside monitors. These data have different storage, speed and reliability requirements. The operating system uses a memory hierarchy and different I/O techniques to manage data efficiently. Selecting the correct storage level and I/O method improves performance, reduces CPU overhead and ensures that critical medical information is available when required.

## 2. Levels of the Memory Hierarchy

The memory hierarchy organizes storage according to speed, capacity and cost. Faster storage is generally smaller and more expensive, while slower storage provides greater capacity at a lower cost.

| Memory level | Typical access time | Typical capacity | Purpose |
|---|---:|---:|---|
| CPU registers | Less than 1 ns | Bytes to a few KB | Hold currently processed instructions and data |
| L1/L2/L3 cache | Around 1–30 ns | KB to tens of MB | Store frequently used data close to the CPU |
| Main memory (RAM) | Around 50–100 ns | GBs | Hold active programs and working data |
| SSD | Around 50–200 microseconds | Hundreds of GBs to TBs | Fast permanent storage |
| Hard disk (HDD) | Around 5–15 milliseconds | TBs | Large-capacity long-term storage |
| Network storage | Around 1–100+ milliseconds | TBs to PBs | Shared storage, backups and remote access |

*Note: These are approximate illustrative values. Actual performance depends on hardware, workload, network conditions and storage technology.*

Registers and cache provide the fastest access, while RAM supports currently running applications. SSDs and HDDs provide persistent storage, and network storage supports sharing and backup across hospital systems.

## 3. Suitable Storage for Hospital Data

Different hospital data should be stored at different levels based on access frequency, size and criticality.

### A. MRI Images

MRI images are large files that may occupy hundreds of megabytes or more.

- Newly captured images should initially be transferred into RAM buffers.
- Frequently accessed images should be stored on high-speed SSDs.
- Completed scans should be stored in a medical image archive, such as a PACS system.
- Older images can be moved to high-capacity HDD or network storage.
- Backup copies should be maintained in separate storage to protect against data loss.

**Evaluation:** SSD storage is suitable for active MRI images because it provides faster retrieval than HDDs. Network or HDD storage is useful for long-term archives because of its larger capacity and lower cost.

### B. Patient Records

Patient records contain medical histories, prescriptions, test results and personal information.

- Frequently accessed database pages should remain in RAM.
- Frequently used database information can be held in CPU caches.
- The database should be stored permanently on reliable SSDs.
- Backups and archival records should be maintained on separate secure storage.

**Evaluation:** SSD-backed database storage combined with RAM caching provides fast patient-record retrieval. Access control, encryption and backups are necessary to protect confidentiality and availability.

### C. Bedside Monitor Readings

Bedside monitors continuously generate sensor readings such as heart rate, oxygen saturation and blood pressure.

- The latest readings should be held in RAM for immediate processing.
- Critical readings should be processed with real-time scheduling.
- Recent readings can be stored temporarily in a local buffer.
- Historical readings should be saved to a central monitoring database or network storage.

**Evaluation:** Monitor readings require predictable and low-latency access. They should not depend on slow HDD or network access for immediate alarm decisions. Local processing and buffering ensure that monitoring continues even during temporary network failures.

## 4. Programmed I/O, Interrupt-Driven I/O and DMA

The operating system can use different methods to transfer data between devices and memory.

### A. Programmed I/O

In programmed I/O, the CPU repeatedly checks the device status and transfers data when the device is ready.

- Simple to implement.
- The CPU remains occupied checking the device.
- Wastes CPU time when the device is slow.

**Evaluation:** It may be suitable for simple, low-speed devices, but it is inefficient for large MRI image transfers.

### B. Interrupt-Driven I/O

In interrupt-driven I/O, the device sends an interrupt when it requires CPU attention or when an operation is completed.

- The CPU can perform other tasks while waiting.
- The interrupt service routine handles the device event.
- It is more efficient than continuous polling.
- Too many interrupts can create significant CPU overhead.

**Evaluation:** It is suitable for bedside monitors because sensor events and abnormal readings need prompt attention. However, interrupting the CPU for every transferred data word is inefficient for large image files.

### C. Direct Memory Access (DMA)

DMA allows a device to transfer data directly between the device and main memory without requiring the CPU to handle every individual word.

- The CPU configures the DMA controller with the memory address, transfer size and direction.
- The DMA controller performs the data transfer.
- The CPU can execute other tasks during the transfer.
- An interrupt can notify the CPU when the transfer is complete or when an error occurs.

**Evaluation:** DMA is the most suitable method for MRI image transfer because MRI produces large amounts of data. It reduces CPU overhead and improves overall system performance.

### Comparison of I/O Methods

| Method | CPU involvement | Main advantage | Main disadvantage | Suitable hospital use |
|---|---|---|---|---|
| Programmed I/O | Very high | Simple implementation | Wastes CPU time through polling | Simple, low-speed devices |
| Interrupt-driven I/O | Moderate | CPU responds when an event occurs | Frequent interrupts cause overhead | Bedside monitor events |
| DMA | Low during transfer | Efficient large data transfer | Requires DMA hardware and buffer management | MRI image transfer |

## 5. Effect of Caching on Patient Record Look-up

Caching stores frequently accessed data in faster memory so that it can be retrieved without repeatedly accessing slower storage.

For example, when a doctor searches for a patient's record:

1. The database first checks whether the required data is available in its cache.
2. If the data is present, it is returned quickly. This is called a cache hit.
3. If the data is absent, it is retrieved from SSD or another storage device. This is called a cache miss.
4. The retrieved data may be placed in the cache for future requests.

**Evaluation:** Caching reduces average access time and improves response speed, especially when doctors frequently access the same patient records. However, cache size is limited, and cached information must be kept consistent with the permanent database. Patient records must also be protected from unauthorized access.

## 6. Alternative Concept and Complexity Analysis: Interrupt-Driven I/O Instead of DMA

If the MRI scanner transfers a 500 MB image using one interrupt per word instead of DMA, the CPU must handle an interrupt for every transferred word. This creates a large processing overhead.

### A. Number of Interrupts

Assume:

- Image size = 500 MB
- 1 MB = 1,000,000 bytes
- Word size = 4 bytes (32 bits)

Total image size:

500 × 1,000,000 = 500,000,000 bytes

Number of words:

500,000,000 ÷ 4 = 125,000,000 words

Therefore, the interrupt-driven method requires approximately **125 million interrupts**, assuming one interrupt per 32-bit word.

### B. CPU Time Used by Interrupts

Assume each interrupt requires approximately 1–5 microseconds of CPU processing time.

At 1 microsecond per interrupt:

125,000,000 × 1 microsecond = 125 seconds

At 5 microseconds per interrupt:

125,000,000 × 5 microseconds = 625 seconds

Therefore, CPU interrupt-handling time could be approximately **125–625 seconds** under these assumptions.

This is a simplified estimate. Actual interrupt cost depends on processor speed, driver design, operating-system overhead and hardware. It does not include the physical time required to transfer the image itself.

### C. DMA Compared with One Interrupt per Word

With DMA, the CPU configures the transfer and the DMA controller transfers the data directly into memory. The CPU normally receives an interrupt when a transfer block or the complete transfer finishes.

For example, if the image is transferred in 10 MB blocks:

500 MB ÷ 10 MB = 50 blocks

This requires approximately 50 completion interrupts, rather than 125 million word-level interrupts, assuming one interrupt per block.

| Factor | Interrupt per word | DMA |
|---|---|---|
| Number of interrupts | 125 million | Approximately 50 for 10 MB blocks |
| CPU involvement | Very high | Low during data transfer |
| Transfer management | CPU handles each word | DMA controller handles the transfer |
| Performance | High CPU overhead | More efficient for large transfers |
| Buffer requirement | Small hardware/FIFO buffers may be used, with software buffering as needed | A larger RAM buffer or block buffer is commonly used |
| Suitability for MRI | Poor | Highly suitable |

### D. Memory Buffer Requirements

**Interrupt-driven I/O:** Data is handled in small units, often through a device FIFO or small temporary buffer. The CPU must service interrupts frequently and move the data into its destination buffer. Large software buffers may still be used to collect the image, but they do not remove the per-word interrupt overhead.

**DMA:** A larger memory buffer is generally allocated for block transfers. For example, two 10 MB buffers can be used in a double-buffering arrangement. While DMA fills one buffer, the CPU or image-processing software can process data in the other buffer. This improves throughput and reduces waiting time.

### E. Final Evaluation

DMA is clearly more efficient for transferring large MRI images. Interrupt-driven I/O for every word would generate 125 million interrupts for a 500 MB image under the stated assumptions, consuming substantial CPU time. DMA reduces the number of CPU interruptions and allows the processor to perform other hospital tasks.

## 7. Conclusion

A smart hospital requires an efficient memory hierarchy and suitable I/O methods. MRI images should use RAM buffers and SSD-based storage for active processing, patient records should use SSD-backed databases with RAM caching, and bedside monitor readings should be processed locally with low latency. Interrupt-driven I/O is appropriate for monitor events, while DMA is the best choice for large MRI image transfers. These choices improve system speed, reduce CPU overhead and su
pport reliable hospital operations.
