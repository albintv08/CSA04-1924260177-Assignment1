# Task 11

# TASK 11 – Recommend and Defend the Operating-System Plan

**Marks:** 4  
**Bloom's Level:** K5 – Evaluate

## 1. Introduction

A smart hospital requires a reliable, secure and efficient operating-system environment to manage patient monitoring, medical records, MRI imaging, communication and other hospital services. Since each environment has different performance and security requirements, using one general-purpose operating system for every application may not provide the best solution.

Based on the analysis of Tasks 1–10, I recommend a combination of real-time, desktop, handheld, multiprocessor and clustered operating-system environments. This approach provides suitable performance, reliability, security and scalability for the hospital.

## 2. Recommended Operating-System Plan

| Hospital environment | Recommended OS type | Recommended structure | Reason |
|---|---|---|---|
| Bedside patient monitors | Hard real-time OS (RTOS) | Microkernel-based or small real-time kernel | Predictable response to critical sensor events |
| Nurses' tablets | Handheld/mobile OS | Modular kernel | Battery efficiency, wireless connectivity and secure applications |
| Doctors' workstations | Desktop OS | Hybrid or modular monolithic kernel | User-friendly interface and compatibility with medical applications |
| Patient-record database | Clustered server OS | Modular kernel | High availability, data protection and failover |
| MRI imaging server | Multiprocessor/SMP OS | Modular kernel | Parallel processing and efficient handling of large image files |
| Partner-hospital communication | Distributed/network operating environment | Modular network services | Secure communication and resource sharing between hospitals |

### A. Bedside Patient Monitors

A hard real-time operating system is recommended because patient monitors continuously process sensor readings and generate alarms when abnormal conditions occur.

- Use interrupt-driven I/O to respond to sensor events.
- Use real-time scheduling to prioritize critical monitoring tasks.
- Use memory protection to isolate applications.
- Use privileged kernel operations to control hardware safely.
- Maintain local buffering so monitoring continues during network interruptions.

A microkernel-based RTOS is preferable because separating services can improve fault isolation. However, its message-passing overhead must be measured to ensure that deadlines are met.

### B. Nurses' Tablets

A handheld operating system is recommended for nurses' tablets.

- Provide a simple user interface.
- Support wireless communication with hospital servers.
- Use authentication and role-based access control.
- Use encryption to protect patient information.
- Manage battery consumption and application resources.

A modular kernel allows device drivers and services to be updated without unnecessarily changing the entire operating system.

### C. Doctors' Workstations

A desktop operating system is suitable for doctors' workstations because doctors need graphical applications, medical-record access, report generation and diagnostic tools.

- Provide a graphical user interface.
- Support multitasking and program execution.
- Use file-system permissions and encryption.
- Provide secure network communication.
- Use user authentication and activity auditing.

A hybrid or modular operating-system structure provides a balance between performance, compatibility and maintainability.

### D. Patient-Record Database

A clustered server operating system is recommended for the patient-record database.

- Store patient records on reliable SSD storage.
- Keep frequently accessed database pages in RAM.
- Use caching to improve record retrieval.
- Provide authentication, role-based access and encryption.
- Maintain audit logs and regular backups.
- Use clustering and failover to improve availability.

If one database server fails, another cluster node should take over the service. This reduces downtime and protects access to important patient information.

### E. MRI Imaging Server

A multiprocessor operating system using symmetric multiprocessing (SMP) is recommended.

- Support multiple processors or CPU cores.
- Use DMA for large MRI image transfers.
- Use RAM buffers during image processing.
- Store active images on SSDs.
- Use HDD or network storage for long-term archives.
- Provide parallel processing for image reconstruction and analysis.

SMP allows multiple processors to share system resources and distribute workloads efficiently.

### F. Partner-Hospital Communication

A distributed operating environment is recommended to connect the three hospitals.

- Use secure network communication.
- Encrypt patient information during transmission.
- Apply authentication and access control.
- Maintain communication logs and audit trails.
- Support secure data exchange between hospital databases.
- Provide backup communication arrangements.

This allows authorized medical staff to access required patient information across hospitals while maintaining confidentiality and integrity.

## 3. Services, Protection and I/O Methods

The recommended operating systems should provide the following services and protection mechanisms.

| Environment | Important OS services | Protection mechanisms | Recommended I/O |
|---|---|---|---|
| Patient monitors | Program execution, sensor handling, error detection and scheduling | Process isolation and privileged kernel operations | Interrupt-driven I/O |
| Nurses' tablets | User interface, communication, file management and power management | Authentication, encryption and access control | Interrupt-driven I/O |
| Doctors' workstations | Multitasking, file systems, communication and accounting | User permissions, MFA and encryption | Interrupt-driven I/O and programmed I/O for simple devices |
| Patient database | File management, communication, resource allocation and recovery | RBAC, auditing, encryption and backups | DMA and interrupt-driven I/O |
| MRI server | Process management, memory management and device management | Memory protection and controlled device access | DMA |
| Hospital network | Communication, error detection and security | TLS encryption, authentication and network access control | Interrupt-driven networking and DMA where supported |

### Protection of Hospital Data

The following mechanisms are important:

1. **User mode and kernel mode:** Prevent ordinary applications from directly performing privileged operations.
2. **Memory protection:** Prevent one process from accessing another process's memory.
3. **Authentication:** Verify the identity of doctors, nurses and administrators.
4. **Role-based access control:** Allow users to access only the information required for their responsibilities.
5. **Encryption:** Protect patient information at rest and during transmission.
6. **Auditing:** Record access and important changes to medical records.
7. **Backup and recovery:** Protect medical information against accidental deletion, hardware failure and cyberattacks.

## 4. Limitations and Risks of the Recommended Plan

Although the recommended design provides several advantages, it also has limitations.

| Limitation or risk | Possible effect | Recommended solution |
|---|---|---|
| High implementation cost | Multiple specialized systems increase expenses | Use cost-effective hardware and phased implementation |
| Complex maintenance | Different OS environments require specialized knowledge | Establish centralized IT management and maintenance procedures |
| Network failure | Hospitals may temporarily lose access to shared records | Maintain local databases, buffering and backup network links |
| Cybersecurity attacks | Unauthorized access or data theft | Apply encryption, MFA, patching and security monitoring |
| Hardware failure | Medical services may become unavailable | Use redundant hardware and failover systems |
| Software incompatibility | Medical applications may not work across all systems | Perform compatibility testing and use standard interfaces |
| Data inconsistency | Different hospitals may hold outdated records | Implement controlled synchronization and database consistency checks |

The hospital must also regularly test emergency procedures, security controls and backup recovery arrangements.

## 5. Suitability for Three Hospitals

The recommended plan can be extended to a group of three hospitals.

Each hospital should maintain its own local systems for bedside monitoring, medical workstations, tablets and essential patient-record services.

A shared distributed architecture can connect all three hospitals through secure communication links.

### Recommended arrangement

- Each hospital maintains local real-time monitoring systems.
- Each hospital maintains access to its local patient database.
- MRI imaging systems use local high-performance servers.
- Centralized services support authorized information sharing.
- Secure replication and backups protect records across locations.
- Network failure should not stop critical bedside monitoring.

This approach provides local operational independence while allowing authorized information sharing.

**Evaluation:** The design remains suitable for three hospitals because it combines local processing with centralized coordination. However, network capacity, storage requirements, data synchronization, cybersecurity and maintenance costs must increase as the number of connected users and medical devices grows.

## 6. Alternative Concept and Complexity Analysis: Virtual Machines on Two Large Servers

An alternative approach is to replace separate physical machines with virtual machines (VMs) running on two large physical servers.

A hypervisor would manage multiple virtual machines, and each VM could run a different operating-system environment.

For example:

- A real-time monitoring VM.
- A patient-record database VM.
- An MRI image-processing VM.
- A workstation application VM.
- A communication-services VM.

### A. Effect on Monitor Response Time

Virtualisation introduces additional scheduling and resource-management overhead.

The hypervisor must allocate CPU time, memory and device access to each VM. If several VMs compete for CPU resources, bedside monitoring tasks may experience delays.

For critical patient monitors, unpredictable delays could be dangerous.

**Recommendation:** Critical monitoring should remain on dedicated physical RTOS devices or use a validated real-time hypervisor with CPU reservation, processor pinning, device passthrough and deterministic scheduling. The monitor's worst-case response time must be tested against its deadline.

### B. Memory and Processor Overhead

Virtualisation requires additional resources.

- Each VM needs memory for its guest operating system and applications.
- The hypervisor also consumes memory and processor resources.
- Virtual devices and memory management introduce additional overhead.
- Multiple VMs may compete for processor time.

For example, if two servers each have 64 GB RAM, the total physical memory is 128 GB. This memory must be shared among the hypervisor, guest operating systems and applications. It cannot all be allocated to hospital applications.

Virtualisation may improve hardware utilization, but resource allocation must be carefully planned.

### C. Effect on Reliability

Virtualisation provides some advantages:

- VMs can be restarted independently.
- Virtual machines can be migrated between compatible hosts.
- Snapshots and backups can simplify recovery.
- Hardware resources can be shared efficiently.

However, using only two large servers creates risks:

- Failure of one server may affect several hospital services.
- Failure of both servers may interrupt a large part of the hospital system.
- Hypervisor vulnerabilities can affect multiple VMs.
- Resource contention can reduce performance.
- Network or shared-storage failure may affect all virtual machines.

A two-server design therefore requires redundancy, independent power supplies, replicated storage, reliable networking and tested failover procedures.

### D. Comparison of the Two Designs

| Factor | Separate physical systems | Two-server virtualised system |
|---|---|---|
| Monitor response time | More predictable with dedicated RTOS hardware | May experience hypervisor scheduling delays |
| Resource utilization | Some hardware may remain underused | Resources can be shared efficiently |
| Memory overhead | No guest OS virtualization overhead | Additional memory required for VMs and hypervisor |
| CPU overhead | Direct hardware access | Additional virtualization overhead |
| Isolation | Physical separation provides strong isolation | Logical isolation depends on hypervisor security |
| Reliability | Failure may affect an individual machine | Host failure may affect multiple VMs |
| Maintenance | Multiple physical systems to maintain | Centralized VM management |
| Scalability | Requires additional hardware | New VMs can be created when resources are available |

### E. Final Evaluation of Virtualisation

Virtualisation is suitable for many hospital services, including database applications, communication services, reporting and general-purpose workloads.

However, placing all hospital services, especially critical bedside monitoring, on only two large servers may introduce unacceptable response-time and availability risks.

A hybrid approach is preferable: retain dedicated real-time hardware for bedside monitors and use virtual machines for suitable server workloads. The two physical servers should be configured for high availability, with sufficient capacity and tested recovery procedures.

## 7. Evidence from Earlier Measurements

The recommendation is supported by the practical analysis performed in Tasks 6 and 10.

### A. System Call Measurements from Task 6

The file-copy experiment compares different buffer sizes.

| Buffer size | Read calls | Write calls | Observation |
|---|---:|---:|---|
| 1 byte | [Insert result] | [Insert result] | More system calls |
| 512 bytes | [Insert result] | [Insert result] | Fewer system calls |
| 4096 bytes | [Insert result] | [Insert result] | Reduced system-call overhead |

The experiment supports the use of suitable buffer sizes for large data transfers, such as MRI image copying and backup operations.

### B. CPU Time Measurements from Task 10

| Buffer size | Real time | User time | System time |
|---|---:|---:|---:|
| 1 byte | [Insert result] | [Insert result] | [Insert result] |
| 512 bytes | [Insert result] | [Insert result] | [Insert result] |
| 4096 bytes | [Insert result] | [Insert result] | [Insert result] |

These measurements help identify how buffer size affects execution time and kernel overhead.

### C. Process and Thread Measurements from Task 10

| Measurement | 1,000 processes | 1,000 threads |
|---|---:|---:|
| Creation/completion time | [Insert result] | [Insert result] |
| Maximum resident memory | [Insert result] | [Insert result] |

These measurements help justify using threads for suitable parallel workloads and separate processes for applications requiring stronger isolation.

**Note:** The numerical values must be filled using the actual Linux Codespaces results. Measurements should not be invented.

## 8. Overall Recommendation

The best solution for the smart hospital is a hybrid operating-system architecture.

- Use a hard real-time operating system for bedside monitors.
- Use mobile operating systems for nurses' tablets.
- Use desktop operating systems for doctors' workstations.
- Use clustered server operating systems for patient databases.
- Use multiprocessor operating systems and DMA for MRI image processing.
- Use distributed and secure network services to connect the three hospitals.
- Use virtualisation for suitable non-critical server workloads, with high availability and sufficient resource allocation.

## 9. Conclusion

A smart hospital requires more than one type of operating system because its applications have different performance, reliability and security requirements. The recommended hybrid architecture provides predictable monitoring, efficient image processing, secure patient-record management and reliable communication between hospitals.

Although virtualisation can reduce hardware costs and improve resource utilization, critical real-time monitoring should not depend on an overloaded general-purpose virtual machine. Therefore, combining dedicated real-time systems with clustered, multiprocessor and virtualised server environments provides the most balanced solution for the three-hospital network.