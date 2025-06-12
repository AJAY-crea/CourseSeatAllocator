# 🎓 Course Registration and Allocation System

The **Course Registration and Allocation System** is a C++ application that simulates a real-world university course registration process. It allows students to register, log in, submit course preferences, and receive course allocations based on their **CGPA**, **submission time**, **slot availability**, and **credit limits**. The system supports both **core** and **elective** courses, **professor assignments**, and provides detailed feedback for each course allocation.

> 🛠 Built using object-oriented programming in C++, the project emphasizes **modularity**, **reusability**, and **scalability**, making it ideal for academic automation or as a portfolio-level systems design project.

---

## 🚀 Features

### 👥 User Management
- Supports two user types: **Student** and **Professor** (both inherit from a base `User` class).
- Secure login system with **email and password verification**.

### 📚 Course Management
- Each course includes:
  - Course code, name, branch, professor
  - Core/elective status
  - CGPA restriction
  - Seat size
  - Slot and credit value
- **Core courses** are mandatory for students of the same branch.
- **Electives** are allocated based on preferences and constraints.

### 📝 Preference Submission
- Students can log in to **submit or update** course preferences.
- System tracks **submission timestamps** to break ties in CGPA.

### 📈 Allocation Logic
- **Core Courses**:
  - Automatically allocated to eligible students (branch match),
  - Subject to slot and credit constraints.
- **Elective Courses**:
  - Allocated based on:
    - CGPA (descending priority)
    - Submission time (earlier gets higher priority)
    - Slot and credit limits
    - CGPA restrictions if applicable
- **Sorting criteria**: Higher CGPA first → Earlier submission time next.

### 💬 Feedback System
Students receive clear, comment-based explanations for every course request:
- ✅ `Allotted successfully`
- ❌ `Insufficient seats`
- ❌ `Slot clash`
- ❌ `Credit limit exceeded`
- ❌ `Insufficient CGPA`

---

## 🧰 Data Structures Used
- `std::vector` – for ordered collections (students, professors, courses)
- `std::unordered_map` – for quick ID-based lookups
- `std::set` – to manage available slots and enforce uniqueness

---

## 🏗️ Code Architecture

### 🔹 User (Base Class)
- **Attributes**: `name`, `id`, `smail` (email), `passWord`, `role`
- **Methods**:
  - `pswChecker()` – verify password
  - `getmail()` – return email

### 🔸 Professor (Derived from User)
- **Additional Attributes**: `branch`, `officeRoom`, `phoneNumber`, `lastLoginTime`
- Represents course instructors.

### 🔸 Student (Derived from User)
- **Attributes**:
  - `branch`, `cg` (CGPA)
  - `preferences` (vector of course codes)
  - `allocatedCourses` (final list)
  - `availableSlots`, `submissionTime`
  - `creditLimit`, `presentCredits`
  - `comments` (per course)
- **Methods**:
  - Preference management
  - Slot conflict checking
  - Credit tracking and update
  - Allocation comment generation

### 📘 Course
- **Attributes**:
  - `courseCode`, `courseName`, `branch`
  - `offeringProfessor`, `cg_based`, `coreCourse`
  - `size` (seats), `slot`, `credits`
  - `allotedStudents`
- **Methods**:
  - Seat checking, enrollment logic, metadata access

### 🏛️ College
- Central manager class
- Maintains:
  - All students, professors, and courses
- Handles:
  - Registration
  - Sorting and allocation algorithms
  - Allocation comment initialization

---

