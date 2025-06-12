# CourseSeatAllocator

This is a C++ project that simulates a college course seat allocation system based on students' preferences, CGPA, available slots, and credit limits.

✅ Features
Student and Professor registration

Course registration (core/elective, CGPA-based or not)

Student login to enter or edit course preferences

Allocation based on:

CGPA (higher CG gets priority)

Slot availability

Credit limits

Submission time (for tie-breaking)

Core courses allotted automatically

Elective courses allotted based on conditions

Students receive personalized messages on allocation status

🛠️ How to Run
Compile the code:

r
Copy
Edit
g++ -std=c++17 -o course_allocation main.cpp
Run the program:

bash
Copy
Edit
./course_allocation
Follow the prompts to:

Register students/professors/courses

Log in as a student

Submit and edit preferences

View course allotment results

📌 Note
Uses OOP concepts like classes, inheritance, and polymorphism

All data is handled in-memory (no file I/O)
