/*
===============================================================================
  CourseSeatAllocator - A C++ Project
===============================================================================

This project simulates a college course seat allocation system. It assigns 
core and elective courses to students based on preferences, CGPA, credit limits, 
and slot availability. The system supports user login, preference editing, 
automated allocation logic, and comment feedback for each course.

-------------------------------------------------------------------------------
🚀 Features
-------------------------------------------------------------------------------
1. User Roles:
   - 🧑‍🎓 Students: Register, log in, enter preferences, view allocations.
   - 👨‍🏫 Professors: Registered as instructors for courses.

2. Course Allocation Logic:
   - Core courses are mandatory based on the student’s branch.
   - Elective allocation considers:
       • CGPA
       • Submission time (tie-breaker)
       • Slot availability
       • Credit limit

3. Credit Limit Rules:
   - CGPA ≥ 9.0  ⇒ 75 credits
   - CGPA ≥ 8.0  ⇒ 65 credits
   - CGPA < 8.0  ⇒ 55 credits

4. Comment System:
   - ✅ Successfully allocated
   - ❌ Insufficient seats
   - ❌ Slot clash
   - ❌ Credit limit exceeded

5. Preference Editing:
   - Students can edit their preferences before the allocation phase.

6. Result Viewing:
   - After allocation, students can log in to view their results and 
     corresponding feedback.

-------------------------------------------------------------------------------
🏗️ Code Structure
-------------------------------------------------------------------------------
- User (Base Class)         : Common attributes for all users (students/professors)
- Student                   : Manages preferences, credit usage, and feedback
- Professor                 : Represents instructors offering courses
- Course                    : Course metadata (code, credits, slot, capacity, etc.)
- College (Manager Class)   : Handles registration, allocation, and system coordination

===============================================================================
*/
