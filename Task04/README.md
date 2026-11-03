# Task 4


# TASK 4 – EVALUATE THE SERVICES AN OPERATING SYSTEM MUST PROVIDE

## 1. Introduction

An operating system provides essential services that allow applications and hardware components to work together. In a smart hospital, different environments require different operating-system services depending on their purpose. Patient monitors require fast and reliable operations, while database servers require strong security, communication, file management and resource allocation.

## 2. Major Operating-System Services

| OS service | Purpose |
|---|---|
| User Interface | Allows users to interact with the operating system. |
| Program Execution | Loads, executes and terminates applications. |
| I/O Operations | Controls communication with input and output devices. |
| File System | Organizes, stores and retrieves files. |
| Communication | Enables processes and systems to exchange information. |
| Error Detection | Detects hardware and software errors. |
| Resource Allocation | Distributes CPU time, memory and devices. |
| Accounting | Records resource usage and system activities. |
| Protection | Prevents unauthorized access between processes and users. |
| Security | Protects systems and information against threats and attacks. |

## 3. Required Services for Each Hospital Environment

| Environment | Essential services | Services that can be reduced |
|---|---|---|
| Bedside patient monitor | Program execution, I/O, error detection, resource allocation, protection and security | Complex graphical interface, printing and general-purpose file management |
| Nurses' tablets | User interface, program execution, communication, I/O, file system, protection and security | Unnecessary background services and desktop administration tools |
| Doctors' workstations | User interface, program execution, I/O, file system, communication, resource allocation and security | Non-essential background services |
| Patient database server | Program execution, file system, communication, error detection, resource allocation, accounting, protection and security | Unnecessary graphical interface and entertainment services |
| MRI imaging server | Program execution, I/O, file system, communication, resource allocation and error detection | Unnecessary user-interface and background services |
| Partner-hospital link | Communication, protection, security, error detection and accounting | Unnecessary local graphical and multimedia services |

## 4. Services That Can Be Removed from Bedside Patient Monitors

A bedside patient monitor is a dedicated embedded system. It does not need all the services of a general-purpose desktop operating system.

The following services can be reduced or removed:

- Complex desktop graphical interfaces.
- Unnecessary printing services.
- General-purpose multimedia applications.
- Unused network services.
- Unnecessary background applications.
- Unneeded file-management utilities.

However, critical services such as sensor input/output, real-time scheduling, error detection, protection and secure communication must remain enabled.

**Justification:** Removing unnecessary services reduces memory usage, CPU overhead and system complexity. This helps the monitor respond quickly and operate reliably.

## 5. Essential Services for the Patient Database Server

The patient database server requires several important services:

1. **File system:** Stores and retrieves patient records.
2. **Program execution:** Runs database management software.
3. **Communication:** Handles requests from doctors and hospital applications.
4. **Resource allocation:** Distributes CPU and memory resources.
5. **Error detection:** Identifies hardware, software and storage errors.
6. **Protection:** Prevents unauthorized process and user access.
7. **Security:** Provides authentication, authorization and encryption.
8. **Accounting:** Maintains activity logs and resource usage records.
9. **I/O operations:** Supports storage devices and network communication.

These services ensure that patient information remains available, accurate and protected.

## 6. How the Operating System Protects Patient Records

An operating system protects patient records using authentication, authorization, process isolation, memory protection and access-control mechanisms.

### 6.1 User Authentication

Users must prove their identity through secure login credentials or multi-factor authentication.

### 6.2 Access Control

Role-Based Access Control (RBAC) grants permissions according to the user's job responsibilities.

For example:
- Doctors can view and update authorized patient records.
- Nurses can access records required for patient care.
- Administrative staff receive only the permissions needed for their duties.

### 6.3 Process Isolation

Each application runs in a separate protected process address space. One user's program cannot directly read or modify another process's memory without authorized access.

### 6.4 File Permissions

The operating system checks file ownership and permissions before allowing a process to access patient records.

### 6.5 Encryption and Auditing

Encryption protects stored and transmitted patient information. Audit logs record who accessed or modified records and when the activity occurred.

These mechanisms help maintain patient confidentiality, integrity and accountability.

## 7. Alternative Concept and Complexity Analysis

**Alternative: Using a Full Desktop Operating System on Nurses' Tablets**

A full desktop operating system may provide many additional services and applications. However, it is not the best option for handheld hospital tablets because it is designed for more powerful computers.

### 7.1 Memory and Storage Usage (Space Complexity)

A desktop OS generally includes additional services such as desktop interfaces, printing systems, background utilities and extensive application support.

These services consume extra RAM and storage space.

A reduced handheld OS uses fewer background services and is optimized for limited memory and storage.

Therefore, a handheld OS is more efficient for tablets with limited hardware resources.

### 7.2 Start-up Time (Time Complexity)

A desktop operating system may require more time to initialize its services, load background applications and prepare the user interface.

A handheld OS generally starts faster because it runs fewer services.

Consequently, a reduced OS allows nurses to access patient information more quickly.

### 7.3 Battery Life

A full desktop OS may consume more power due to additional background processes and services.

A handheld OS is designed with power-management features, sleep modes and efficient background processing.

Therefore, the handheld OS provides better battery efficiency and longer operating time.

## 8. Final Evaluation

A smart hospital should enable only the services required by each computing environment. Bedside monitors should use a minimal set of reliable real-time services, while database servers require comprehensive file management, communication, protection, security and accounting services.

Similarly, nurses' tablets should use a reduced handheld operating system rather than a full desktop OS. This reduces memory and storage requirements, improves start-up time and extends battery life.

## 9. Conclusion

Operating-system services directly influence the performance, reliability and security of a smart hospital. Selecting essential services and disabling unnecessary components improves efficiency. Strong access control, process isolation and encryption protect sensitive patient records. Therefore, a service configuration tailored to each hospital environment provides an effective and secure solution.