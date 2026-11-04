# Task 12

# TASK 12 – RE-EVALUATE AND ADAPT THE DESIGN

**Bloom's Level:** K5 – Evaluate  
**Marks:** 8

## Introduction

The original smart hospital design was developed to support bedside patient monitoring, nurses' tablets, doctors' workstations, patient-record databases, MRI imaging servers and communication between three hospitals.

However, two new requirements have changed the system:

1. Remote monitoring devices are installed in patients' homes and transmit medical readings over the internet.
2. Patient records are moved to a cloud service shared by all three partner hospitals.

These changes introduce new challenges involving internet connectivity, response time, availability, cybersecurity, privacy and distributed data management.

**Decision: MODIFY the original design.**

The original architecture is technically suitable as a foundation, but it must be extended to support secure remote monitoring and cloud-based patient records.

---

## A. Impact Analysis – 2 Marks

The changed requirements affect operating-system types, services, protection mechanisms and communication methods.

### 1. Impact on Operating-System Types

| Environment | Original design | Impact of changed requirement | Revised approach |
|---|---|---|---|
| Bedside monitors | Hard real-time OS | Must continue local monitoring even during network failure | Retain hard RTOS |
| Home monitoring devices | Not included | Devices must collect and transmit readings through the internet | Add embedded RTOS or suitable embedded OS |
| Nurses' tablets | Handheld OS | Must securely access home-monitoring data and cloud records | Retain mobile OS with secure cloud applications |
| Doctors' workstations | Desktop OS | Must access cloud-based records across hospitals | Retain desktop OS with secure cloud connectivity |
| Patient database | Clustered server OS | Records move to a shared cloud environment | Modify to distributed cloud database services |
| MRI imaging server | Multiprocessor OS | May transfer images to cloud storage or archives | Retain multiprocessor OS with secure cloud integration |
| Hospital communication | Distributed system | Must support internet-connected devices and cloud services | Expand to secure distributed architecture |

### 2. Impact on Operating-System Services

The following services become more important:

- **Communication:** Home devices must transmit readings securely through the internet.
- **Program execution:** Embedded devices must execute sensor-reading and transmission applications.
- **File and database management:** Patient records must be stored, retrieved and synchronized through cloud services.
- **Error detection:** The system must detect failed connections, device errors and incomplete data transfers.
- **Resource allocation:** Cloud computing resources must be allocated to multiple hospitals and users.
- **Accounting and auditing:** All access to cloud records must be recorded.
- **Protection and security:** Remote devices and cloud accounts require strong authentication and access control.

### 3. Impact on Protection Mechanisms

| Protection mechanism | New requirement |
|---|---|
| Authentication | Verify home devices, healthcare workers and cloud services |
| Encryption | Protect patient data during internet transmission and cloud storage |
| Role-based access control | Restrict records according to the user's hospital role |
| Multi-factor authentication | Strengthen access to cloud-based medical records |
| Device identity | Ensure that only registered monitoring devices can transmit readings |
| Audit logging | Record access, updates and data transfers |
| Memory protection | Isolate device applications and operating-system components |
| Backup and recovery | Protect cloud records against accidental deletion and service failure |

**Impact evaluation:** The original system's security mechanisms are still useful, but they must be extended to cover remote devices, internet communication and shared cloud resources. The internet increases the attack surface, so device authentication, secure communication and continuous monitoring become essential.

---

## B. Evaluation of the Original Design – 2 Marks

The original design provides a strong foundation, but it cannot be used without modifications.

### 1. Response Time

In the original hospital, bedside monitors communicate with local systems. Local communication can provide predictable response times.

With home monitoring devices, readings must travel through the internet. Internet latency can vary due to network congestion, distance, connection quality and service interruptions.

A cloud service may also introduce additional network and processing delays.

**Evaluation:** Critical alarms must not depend entirely on cloud connectivity. Home devices should process abnormal readings locally and generate immediate local alerts when necessary. The cloud should be used for remote monitoring, record storage and medical review.

### 2. Reliability

The original hospital design uses local monitoring systems and clustered database services.

The new design depends on internet connectivity and cloud availability.

Possible failures include:

- Home internet connection failure.
- Device battery failure.
- Cloud service outage.
- Network congestion.
- Data synchronization failure.
- Temporary loss of communication between hospitals.

**Evaluation:** The original design must be modified to include local data buffering, automatic reconnection, redundant communication links and cloud backup mechanisms.

Home devices should continue collecting readings during network interruptions and transmit stored readings when connectivity returns.

### 3. Security

Cloud storage makes patient records accessible from different hospitals and locations. However, it increases the risk of unauthorized access, data leakage and cyberattacks.

Potential threats include:

- Unauthorized access to cloud accounts.
- Stolen device credentials.
- Interception of patient information.
- Malware attacks on home monitoring devices.
- Unauthorized modification of medical readings.
- Data exposure due to incorrect cloud access permissions.

**Evaluation:** The original security mechanisms are insufficient unless they are extended to cover cloud identity management, encrypted communication, device authentication and centralized auditing.

### Overall Evaluation

The original design is partially suitable because it already supports real-time monitoring, secure databases and distributed communication. However, it requires additional mechanisms to support remote devices and cloud-based records.

Therefore, modification is more appropriate than retaining the original design unchanged.

---

## C. Adaptation or Redesign – 2 Marks

The revised architecture should combine embedded real-time systems, local processing, secure internet communication and distributed cloud storage.

### 1. Revised Operating-System Plan

| Environment | Revised operating-system plan | Main responsibility |
|---|---|---|
| Hospital bedside monitors | Hard RTOS | Local real-time monitoring and immediate alarms |
| Home monitoring devices | Embedded RTOS or embedded OS | Collect readings, detect abnormalities and buffer data |
| Home gateway or mobile application | Embedded Linux or mobile OS | Securely transmit readings to the cloud |
| Nurses' tablets | Handheld OS | Access patient readings and records |
| Doctors' workstations | Desktop OS | Access cloud records and diagnostic applications |
| MRI imaging server | Multiprocessor OS | Process large images and transfer them securely |
| Shared patient records | Distributed cloud database services | Store and synchronize records between hospitals |
| Hospital communication | Distributed network services | Connect devices, hospitals and cloud systems |

### 2. Remote Patient Monitoring Architecture

Home monitoring devices may include heart-rate sensors, blood-pressure monitors and oxygen-saturation sensors.

The revised data flow is:

1. Sensors collect readings from the patient.
2. The embedded operating system processes the readings.
3. Critical abnormal readings trigger local alerts without waiting for the cloud.
4. The device or gateway securely transmits readings over the internet.
5. The cloud service receives and stores the readings.
6. Authorized nurses and doctors access the information through hospital applications.
7. If the internet connection fails, readings are stored locally and transmitted after reconnection.

### 3. Cloud-Based Patient Records

The shared cloud service should provide:

- Centralized patient-record management.
- Secure access for all three hospitals.
- Database replication and backup.
- Encryption at rest and during transmission.
- Role-based access control.
- Multi-factor authentication.
- Audit logs.
- Disaster recovery and availability monitoring.

Each hospital should have authorized access to the shared records according to its responsibilities.

A distributed database can support information sharing, but synchronization and consistency must be carefully managed to prevent outdated or conflicting patient information.

### 4. Revised Architecture Diagram

```text
             PATIENTS AT HOME
                    |
             Medical Sensors
                    |
          Embedded Real-Time OS
                    |
        Local Processing and Alerts
                    |
             Home Gateway
                    |
          Secure Internet Connection
                    |
                    v
        +-------------------------+
        |     SHARED CLOUD        |
        |                         |
        |  Patient Record System  |
        |  Remote Monitoring Data |
        |  Database and Backups   |
        +-------------------------+
                    |
          Secure Hospital Network
                    |
       +------------+------------+
       |            |            |
       v            v            v
   HOSPITAL 1   HOSPITAL 2   HOSPITAL 3
       |            |            |
   Doctors      Doctors      Doctors
   Nurses       Nurses       Nurses
   Monitors     Monitors     Monitors
   MRI Server   MRI Server   MRI Server
```

### 5. Additional Security and Reliability Measures

- Use TLS encryption for internet communication.
- Authenticate every registered monitoring device.
- Use secure device updates and software patching.
- Apply MFA and role-based access control to cloud applications.
- Maintain local buffers for readings during network failure.
- Use redundant cloud storage and tested backups.
- Monitor suspicious access and unusual data transmission.
- Use secure synchronization to prevent duplicate or inconsistent records.

**Adaptation evaluation:** This modified architecture provides remote monitoring and shared cloud records without sacrificing local real-time monitoring. It also improves the ability of the three hospitals to share medical information securely.

---

## D. Evidence-Based Defence – 2 Marks

The decision to modify the original design is supported by the operating-system analysis and practical measurements from earlier tasks.

### 1. Evidence from System Call Measurements – Task 6

The file-copy experiment compares different buffer sizes.

Larger buffers are expected to reduce the number of read and write system calls.

| Buffer size | Measured read calls | Measured write calls | Evaluation |
|---|---:|---:|---|
| 1 byte | [Insert actual result] | [Insert actual result] | High system-call overhead |
| 512 bytes | [Insert actual result] | [Insert actual result] | Reduced overhead |
| 4096 bytes | [Insert actual result] | [Insert actual result] | More efficient data transfer |

**Defence:** This supports using suitable buffering for remote monitoring data and large medical image transfers. However, buffering must not introduce unacceptable delays for critical alarms.

### 2. Evidence from CPU Time Measurements – Task 10

The `time` command measures real, user and system execution time.

| Buffer size | Real time | User time | System time |
|---|---:|---:|---:|
| 1 byte | [Insert actual result] | [Insert actual result] | [Insert actual result] |
| 512 bytes | [Insert actual result] | [Insert actual result] | [Insert actual result] |
| 4096 bytes | [Insert actual result] | [Insert actual result] | [Insert actual result] |

**Defence:** These results help identify the CPU overhead caused by frequent system calls. Efficient buffering can reduce unnecessary kernel activity and improve data-transfer performance.

### 3. Evidence from Process and Thread Measurements – Task 10

| Measurement | 1,000 processes | 1,000 threads |
|---|---:|---:|
| Creation time | [Insert actual result] | [Insert actual result] |
| Maximum resident memory | [Insert actual result] | [Insert actual result] |

**Defence:** The comparison helps justify using lightweight threads for suitable parallel processing tasks and separate processes where stronger isolation is required.

### 4. Technical Trade-offs

| Design decision | Advantage | Limitation |
|---|---|---|
| Embedded RTOS at home | Predictable local processing | Limited memory and processing power |
| Local abnormal-reading detection | Immediate response without cloud dependency | Requires reliable local software |
| Cloud patient records | Shared access across hospitals | Depends on cloud and network availability |
| Distributed database | Supports multiple hospitals | Requires consistency and synchronization |
| Encryption and authentication | Protect patient confidentiality | Introduces processing and management overhead |
| Local buffering | Prevents data loss during network failure | Requires additional storage and later synchronization |

### 5. Final Defence

The original design should be modified because the new requirements introduce remote devices and shared cloud records. Completely redesigning the system would increase cost and complexity unnecessarily.

The modified architecture retains the strongest features of the original design:

- Hard real-time operating systems for critical monitoring.
- Mobile and desktop operating systems for healthcare applications.
- Multiprocessor systems for MRI processing.
- Distributed services for communication.
- Secure cloud databases for shared patient records.

It adds embedded operating systems for home devices, local abnormal-reading detection, secure internet communication and cloud-based storage.

The measurements from Tasks 6 and 10 support the importance of efficient buffering and resource management. However, they do not directly measure internet latency or cloud availability. These must be tested separately before deployment.

**Final decision: MODIFY the original design.** This provides the best balance of performance, reliability, security, scalability and cost for a smart hospital network connecting three hospitals and patients at home.

---

## Conclusion

The introduction of remote patient monitoring and cloud-based patient records changes the requirements of the original smart hospital architecture. The existing design provides a strong foundation, but it must be extended to support embedded real-time devices, secure internet communication and distributed cloud storage.

The revised design ensures that critical patient monitoring continues locally, even when internet connectivity is unavailable, while cloud services provide shared patient information across all three hospitals. Therefore, modifying the original architecture is the most technically appropriate and cost-effective decision.
