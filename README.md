# 🏥 Hospital Management System (C++)

A **menu-driven console-based Hospital Management System** developed in **C++**, implementing **Object-Oriented Programming (OOP)** and **core Data Structures** to simulate real hospital operations.

This project is designed for **academic learning** and demonstrates efficient data handling, role-based access, and patient workflow management.

---

## 📖 Project Overview

The system supports **three user roles**:
- **Admin**
- **Doctor**
- **Patient**

Each role has specific permissions to ensure proper management of hospital data such as patients, doctors, appointments, emergencies, and billing.

---

## ✨ Key Features

### 🔐 Authentication System
- Role-based login (Admin / Doctor / Patient)
- Password-protected access
- Maximum login attempt control

### 👤 Patient Management
- Patient registration & login
- View and update patient details
- Billing and payment management

### 🩺 Medical History Management
- Linked List–based medical records
- Add and view patient treatment history
- Date-wise medical notes

### 🌳 Efficient Data Handling (Data Structures)
- **AVL Tree** → Patient storage and fast searching
- **Queue** → Appointment scheduling (FIFO)
- **Priority Queue** → Emergency handling (severity-based)
- **Hash Map / Map** → Doctor–patient assignment and scheduling
- **Linked List** → Medical history records

### 📅 Appointment Scheduling
- Schedule patient appointments
- Doctor-wise timetable display

### 🚨 Emergency Management
- Severity-based emergency queue
- High-priority patients handled first

### 👨‍⚕️ Doctor Management
- Add doctors with specialization
- Assign patients to doctors
- View doctor schedules

---

## 🛠 Technologies & Concepts Used

- **Language:** C++
- **Programming Paradigm:** Object-Oriented Programming (OOP)
- **Data Structures:**
  - AVL Trees
  - Queues
  - Priority Queues
  - Linked Lists
  - Hash Maps
- **Application Type:** Console-Based System

---

## 📂 Project Structure

Hospital-Management-System/
│
├── src/
│ └── Hospital Managment System.cpp
│
├── README.md
├── .gitignore

yaml
Copy code

---

## ▶️ How to Compile & Run

### Step 1: Clone Repository
```bash
git clone https://github.com/your-username/Hospital-Management-System.git
Step 2: Compile
bash
Copy code
g++ src/Hospital Managment System.cpp -o hospital
Step 3: Run
bash
Copy code
./hospital
🔑 Default Login Credentials
Role	Password
Admin	admin123
Doctor	doctor123
Patient	patient123

🎯 Learning Outcomes
Practical use of Data Structures

Implementation of real-world hospital workflows

Role-based access control

Improved understanding of system design & logic building

🎓 Academic Use
This project is suitable for:

Data Structures & Algorithms

Object-Oriented Programming

Software Engineering Mini Projects

Semester Projects

🚀 Future Enhancements
File handling for data persistence

Graphical User Interface (GUI)

Database integration

Conversion to Java or Web-based system

👨‍💻 Author
Shoaib Arshad
Software Engineering Student
Riphah International University ,Islamabad

⭐ If you found this project useful, feel free to star the repository!
