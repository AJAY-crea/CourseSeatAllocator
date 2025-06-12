#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <ctime>
#include <algorithm>

using namespace std;

class Student; //forward declaration
class User {
    protected:
        string name;
        string id;
        string smail;
        string passWord;
        string role;
        public:
            User(string name, string id, string smail,string password, string role): name(name), id(id), smail(smail), passWord(password), role(role) {}
            bool pswChecker(string& psw, string smail) {
                return passWord == psw;
            }

            virtual string getmail() const {
                return smail;
            }
};

class Professor : public User {
    private:
        string branch;
        string officeRoom;
        string phoneNumber;
        time_t lastLoginTime;
    public:
        Professor(string name, string id, string smail, string password, string role, string branch, string officeRoom, string phoneNumber, time_t lastLoginTime)
        : User(name, id, smail, password, role), branch(branch), officeRoom(officeRoom), phoneNumber(phoneNumber), lastLoginTime(lastLoginTime) {}
        string getmail() const override {
            return smail;
        }
};  

class Course {
    private:
        string courseCode;
        string courseName;
        string branch;
        Professor* offeringProfessor;
        bool  cg_based;
        bool coreCourse;
        int size;
        char slot;
        int credits;
        vector<Student*> allotedStudents;
    public:
        Course(string courseCode, string courseName, string branch,
           Professor* offeringProfessor, bool cg_based,
           bool coreCourse, int size, char slot, int credits)
        : courseCode(courseCode),
          courseName(courseName),
          branch(branch),
          offeringProfessor(offeringProfessor),
          cg_based(cg_based),
          coreCourse(coreCourse),
          size(size),
          slot(slot),
          credits(credits) {
            allotedStudents.clear();
          }

        int getSize() {
            return size;
        }
        void decrementSize() {
            size--;
        }
        bool is_core() {
            return coreCourse;
        }
        string getCourseCode() {
            return courseCode;
        }
        string getBranch() {
            return branch;
        }
        char getSlot() {
            return slot;
        }
        void addStudent(Student* s) {
            allotedStudents.push_back(s);
        }
        int getCredits() {
            return credits;
        }

};

class Student : public User {
    private:
        string branch;
        float cg;
        vector<Course*> preferences;
        vector<Course*> allocatedCourses;
        set<char> availableSlots;
        time_t submissionTime;
        int creditLimit;
        int presentCredits;
        vector<string> comments;
    public:
        Student(string name, string id, string smail, string password, string role, string branch, float cg)
            : User(name, id, smail, password, role), branch(branch), cg(cg), presentCredits(0) {
            submissionTime = time(NULL);
            allocatedCourses.clear();
            for (char slot = 'A'; slot <= 'H'; slot++) {
                availableSlots.insert(slot);
            }   
            if(cg >= 9.0){creditLimit = 75;}
            else if(cg >= 8.0){creditLimit = 65;}
            else {creditLimit = 55;}
        }

        void addpreference(Course* c) {
            preferences.push_back(c);
        }

        string getbranch() {
            return branch;
        }

        float getcg() {
            return cg;
        }

        vector<Course*> getPreferences() {
            return preferences;
        }
        void assignCourse(Course* c) {
            allocatedCourses.push_back(c);
        }
        bool slotAvailable(char slot) {
            return availableSlots.find(slot) != availableSlots.end();
        }
        void removeSlot(char s) {
            availableSlots.erase(s);
        }
        time_t* getSubmissionTime() {
            return &submissionTime;
        }
        void updateSubmissionTime() {
            submissionTime = time(NULL);
        }
        pair<vector<Course*>,vector<Course*>> splitCourses() {
            vector<Course*> coreCourses;
            vector<Course*> electiveCourses;
            for(Course* course : preferences) {
                if(course->is_core()  and course->getBranch() == branch) {
                    coreCourses.push_back(course);
                }
                else {
                    electiveCourses.push_back(course);
                }
            }
            return {coreCourses,electiveCourses};
        } 
        void commentIntialization() {
                comments.resize(preferences.size(),"");
        }

        void addComment(int a,Course* c) {
            int n = 0;
            for(Course* course : preferences) {
                if(course == c){
                    if(a == 1)  {
                        comments[n] = "This course is alloted to you successfully";
                    }
                    else if(a == 2) {
                        comments[n] = "This course wasn't alloted to you because of insufficient seats available.";
                    }
                    else if(a == 3)
                    {
                        comments[n] = "This course wasn't alloted to you because of slot clash.";
                    }
                    else if(a == 4){
                        comments[n] = "This course wasn't alloted to you because of creditLimit.";
                    }
                    break;
                }
                n++;
            }
        }

        void addCredits(int p) {
            presentCredits += p;
        }

        int getPresentCredits() {
            return presentCredits;
        }
        int getMaxCedits() {
            return creditLimit;
        }
        void clearPreference() {
            preferences.clear();
        }
        string getCommentAt(int idx) {
            return comments[idx];
        }
        string getmail() const override {
            return smail;
        }

};

bool comp(Student* a, Student* b) {
    if(a->getcg() != b->getcg()) return a->getcg() > b->getcg();
    return a->getSubmissionTime() < b ->getSubmissionTime(); 
}

class College {
    public:
        unordered_map<string,Student*> allStudents_for_fast_access;
        vector<Student*> allStudents;
        vector<Course*> allCourses;
        unordered_map<string,Course*> allCourses_for_fast_access;
        unordered_map<string, Professor*> allProfs;
    public:
        College() {};
        void addstudent( Student* s) {
            allStudents_for_fast_access[s->getmail()] = s;
            allStudents.push_back(s);
        }
        void addProfessor(Professor* p) {
            allProfs[p->getmail()] = p;
        }
        void addCourse(Course* c) {
            allCourses.push_back(c);
            allCourses_for_fast_access[c->getCourseCode()] =  c;
        }
        void sort_cg() {
            sort(allStudents.begin(), allStudents.end(), comp);
        }

        void studentCommmetIntialization() {
            for(Student* student : allStudents) {
                student->commentIntialization();
            }
        }

        void assignCoreCourses() {
            for(Student* student : allStudents) {
                string studentBranch = student->getbranch();
                vector<Course*> coreCourses = student->splitCourses().first;
                for(Course* course : coreCourses) {
                    student->addCredits(course->getCredits());
                    course->decrementSize();
                    course->addStudent(student);
                    student->assignCourse(course);
                    student->removeSlot(course->getSlot());
                    student->addComment(1,course);
                }
            }
        }
        void allocationForElectives() {
            for(Student* student : allStudents) {
                vector<Course*> electivepreference = student->splitCourses().second;
                for(Course* course : electivepreference) {
                        if(course->getSize() > 0 and student->slotAvailable(course->getSlot()) and student->getPresentCredits() + course->getCredits() <= student->getMaxCedits() ) {
                            course->decrementSize();
                            student->removeSlot(course->getSlot());
                            course->addStudent(student);
                            student->assignCourse(course);
                            student->addCredits(course->getCredits());
                            student->addComment(1,course);
                        }
                        else if(course->getSize() == 0 ){
                            student->addComment(2,course);
                        }
                        else if(student->slotAvailable(course->getSlot()) == false) {
                            student->addComment(3,course);
                        }
                        else if(student->getPresentCredits() + course->getCredits() > student->getMaxCedits()) {
                            student->addComment(4,course);
                        }
                }
            }
        }
};


int main() {
    College college;

    //Register students
    int numStudents;
    cout << "Enter number of Students: ";
    cin >> numStudents; 
    for(int i = 0; i < numStudents; ++i) {
        string name, id, email, password, role, branch;
        float cg;
        cout << "Enter Student details (name id email password role branch CGPA):\n";
        cin >> name >> id >> email >> password >> role >> branch >> cg;
        Student* s = new Student(name, id, email, password, role, branch, cg);
        college.addstudent(s);
    }

    //Register professors
    int numProfessors;
    cout << "Enter number of Professors: ";
    cin >> numProfessors;
    for(int i = 0; i < numProfessors; ++i) {
        string name, id, email, password, role, branch, office, phone;
        cout << "Enter Professor details (name id email password role branch office phone):\n";
        cin >> name >> id >> email >> password >> role >> branch >> office >> phone;
        Professor* p = new Professor(name, id, email, password, role, branch, office, phone, time(NULL));
        college.addProfessor(p);
    }

    //Register courses
    int numCourses;
    cout << "Enter number of Courses: ";
    cin >> numCourses;
    for(int i = 0; i < numCourses; ++i) {
        string code, name, branch, profEmail;
        bool isCore, isCGbased;
        int size, credits;
        char slot;

        cout << "Enter Course details (code name branch is_core(0/1) cg_based(0/1) size slot credits professor_email):\n";
        cin >> code >> name >> branch >> isCore >> isCGbased >> size >> slot >> credits >> profEmail;

        Professor* prof = college.allProfs[profEmail];
        if (!prof) {
            cout << "Professor not found. Skipping course.\n";
            continue;
        }

        Course* course = new Course(code, name, branch, prof, isCGbased, isCore, size, slot, credits);
        college.addCourse(course);
    }

    //Login-Preference Editing Phase(Before allocation)
    while (true) {
        string email, psw;
        cout << "\n--- Login to Submit Preferences ---\nEmail: ";
        cin >> email;
        cout << "Password: ";
        cin >> psw;

        if (college.allStudents_for_fast_access.find(email) != college.allStudents_for_fast_access.end()) {
            Student* student = college.allStudents_for_fast_access[email];
            if (student->pswChecker(psw, email)) {
                cout << "\nStudent Login Successful!\n";

                //Check and modify preferences
                cout << "Do you want to change your course preferences? (1 = Yes / 0 = No): ";
                int choiceChange;
                cin >> choiceChange;
                if (choiceChange == 1) {
                    student->clearPreference();   
                    cout << "Enter number of new preferences: ";
                    int n;
                    cin >> n;
                    for (int i = 0; i < n; ++i) {
                        string courseCode;
                        cout << "Enter course code #" << (i + 1) << ": ";
                        cin >> courseCode;
                        if (college.allCourses_for_fast_access.find(courseCode) == college.allCourses_for_fast_access.end()) {
                            cout << "Course not found. Skipping.\n";
                            continue;
                        }
                        Course* course = college.allCourses_for_fast_access[courseCode];
                        student->addpreference(course);
                    }
                    student->updateSubmissionTime(); 
                    cout << "Submitted at: " << ctime(student->getSubmissionTime());
                }
            } else {
                cout << "Incorrect password.\n";
            }
        } else {
            cout << "Student email not found.\n";
        }

        cout << "\nDo you want to login another student for preference editing? (y/n): ";
        char again;
        cin >> again;
        if (again != 'y' && again != 'Y') break;
    }

    // Allocation happens once
    college.sort_cg();
    college.studentCommmetIntialization();
    college.assignCoreCourses();
    college.allocationForElectives();

    // Login loop for viewing results
    while(true) {
        string email, psw;
        cout << "\n--- Login to View Allocation ---\nEmail: ";
        cin >> email;
        cout << "Password: ";
        cin >> psw;

        if(college.allStudents_for_fast_access.find(email) != college.allStudents_for_fast_access.end()) {
            Student* student = college.allStudents_for_fast_access[email];
            if (student->pswChecker(psw, email)) {
                cout << "\nStudent Login Successful!\n";
                cout << "Allocated Courses:\n";

                vector<Course*> preferences = student->getPreferences();
                for(int i = 0; i < preferences.size(); ++i) {
                    Course* course = preferences[i];
                    cout << "  " << course->getCourseCode() << " - " << course->getBranch() << " : ";
                    cout << student->getCommentAt(i) << "\n";
                }

            }
            else {
                cout << "Incorrect password.\n";
            }
        } 
        else {
            cout << "Student email not found.\n";
        }

        cout << "\nDo you want to login another student to view their allocation? (y/n): ";
        char again;
        cin >> again;
        if (again != 'y' && again != 'Y') break;
    }

    return 0;
}
