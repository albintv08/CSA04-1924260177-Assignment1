# Task 1

# TASK 1 – COMPUTING ENVIRONMENT REQUIREMENTS

## 1. Introduction

A smart hospital uses different computing environments to support patient monitoring, medical diagnosis, communication, record management and hospital administration. Each environment has different operating-system requirements depending on its purpose, response time, reliability, security and performance.

## 2. Requirements of Different Computing Environments

### 2.1 Bedside Patient Monitoring System

**Requirements:**
- Real-time response to patient vital-sign changes.
- High reliability and continuous operation.
- Support for sensors and medical devices.
- Secure handling of patient information.
- Low memory and power consumption.

**Recommended OS:** Real-Time Operating System (RTOS).

**Justification:** An RTOS provides predictable response times and is suitable for systems that must immediately respond to critical patient conditions.

### 2.2 Nurses' Handheld Tablets

**Requirements:**
- Long battery life.
- Secure user authentication.
- Reliable wireless connectivity.
- Responsive user interface.
- Support for hospital applications.

**Recommended OS:** Mobile Operating System.

**Justification:** A mobile OS supports wireless communication, touch-based interfaces, application management and power-saving features.

### 2.3 Doctors' Workstations

**Requirements:**
- User-friendly interface.
- High processing performance.
- Secure access to patient records.
- Compatibility with medical software.
- Reliable network connectivity.

**Recommended OS:** Desktop Operating System.

**Justification:** A desktop OS supports multitasking, graphical applications, medical software and efficient interaction with hospital databases.

### 2.4 Patient Record Database Server

**Requirements:**
- High availability.
- Data integrity and consistency.
- Strong access control.
- Backup and recovery.
- Efficient transaction processing.

**Recommended OS:** Server Operating System with clustering and failover support.

**Justification:** A server OS supports centralized data management, multiple users, security and recovery mechanisms.

### 2.5 MRI Imaging Server

**Requirements:**
- High processing speed.
- Large memory capacity.
- High data-transfer speed.
- Parallel processing support.
- Reliable storage.

**Recommended OS:** Multiprocessor or Symmetric Multiprocessing (SMP) Operating System.

**Justification:** An SMP operating system can use multiple processors efficiently to process large medical images and support demanding imaging applications.

### 2.6 Partner-Hospital Communication System

**Requirements:**
- Secure data transmission.
- Confidentiality and integrity.
- Reliable network availability.
- Interoperability between hospitals.
- Activity logging and monitoring.

**Recommended OS:** Secure Network Server Operating System.

**Justification:** A secure network server OS provides communication services, access control, encryption support and network monitoring.

## 3. Comparison of Computing Environments

| Environment | Main requirement | Recommended OS |
|---|---|---|
| Patient monitor | Real-time response | RTOS |
| Nurses' tablet | Battery efficiency | Mobile OS |
| Doctors' workstation | Usability and multitasking | Desktop OS |
| Patient database | Availability and integrity | Server OS |
| MRI server | Parallel processing | SMP OS |
| Hospital communication | Secure networking | Network Server OS |

## 4. Overall Justification

A smart hospital cannot depend on a single type of operating system for all its computing environments. Patient monitors require predictable real-time responses, while handheld devices require power efficiency. Database servers need high availability and data integrity, whereas imaging servers require high processing performance.

Therefore, selecting different operating systems according to the requirements of each environment improves reliability, security, efficiency and patient-care services.

## 5. Conclusion

The operating-system design of a smart hospital must be based on the specific requirements of each computing environment. A combination of real-time, mobile, desktop and server operating systems provides an effective foundation for a reliable and secure smart hospital.
