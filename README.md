# CourseSeatAllocator

This project is a Course Seat Allocation System built using C++, simulating how colleges allocate core and elective courses to students based on their preferences, CGPA, credit limits, and slot availability. It includes login, preference editing, and automated allocation logic with comments on the reasons for allocation or rejection.

🚀 Features
User Roles:

🧑‍🎓 Students: Register, log in, enter preferences, view allocation.

👨‍🏫 Professors: Registered as course instructors.

Course Allocation Logic:

Prioritizes core courses as mandatory based on the student’s branch.

Electives allocated based on:

CGPA

Submission time (tie-breaker)

Slot availability

Credit limit

Credit Limit Rules:

CGPA ≥ 9.0 ⇒ 75 credits

CGPA ≥ 8.0 ⇒ 65 credits

Else ⇒ 55 credits

Comment System:

Students receive feedback on why a course was or wasn’t allocated:

✅ Successfully allocated

❌ Insufficient seats

❌ Slot clash

❌ Credit limit exceeded

Preference Editing:

Students can log in before allocation to change their course preferences.

Result Viewing:

After allocation, students can log in to view their results and comments for each course preference.

🏗️ Code Structure
User (Base Class) – Common attributes for students and professors.

Student – Handles preferences, allocation logic, comments, and credit tracking.

Professor – Basic profile of faculty offering courses.

Course – Contains details like course code, branch, credits, slot, and allotted students.

College – Central manager for student registration, course addition, and allocation processing.


