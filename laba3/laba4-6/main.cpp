#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <cctype>
#include <sstream>
#include <array>
#include "University.h"
#include "Student.h"
#include "Lecturer.h"
#include "Bonus.h"

using namespace std;

int main() {
    University university;
    int option;
    string name;
    int age, id, capacity, grade, type;

    university.generateRandomData();
    Student::setUniversity(&university);

    while (true) {
        cout << "1. Add Lecturer\n2. Delete Lecturer\n3. Add Student\n4. Delete Student\n5. Add Subject\n6. Show University Data\n7. Assign Grade to Student\n8. Show Grades of Student\n9. Add bonus\n0. Exit\n";
        cin >> option;
        switch (option) {
        case 1: {
            cout << "Enter lecturer's name, age, and ID: ";
            cin >> name >> age >> id;
            Lecturer* lecturer = new Lecturer(id, age, name);
            university.addLecturer(lecturer);
            break;
        }
        case 2: {
            cout << "Enter lecturer's ID to delete: ";
            cin >> id;
            university.deleteLecturer(id);
            break;
        }
        case 3: {
            cout << "Enter student's name, age, and ID: ";
            cin >> name >> age >> id;
            Student* student = new Student(id, age, name);
            university.addStudent(student);
            break;
        }
        case 4: {
            cout << "Enter student's ID to delete: ";
            cin >> id;
            university.deleteStudent(id);
            break;
        }
        case 5: {
            cout << "Enter subject's name and capacity: ";
            cin >> name >> capacity;
            Subject* subject = new Subject(name, capacity);
            if (!university.getLecturers().empty()) {
                Lecturer* lecturer = university.getLecturers().front();
                lecturer->addSubject(subject);
                cout << "Subject added to first lecturer.\n";
            }
            else {
                cout << "No lecturers available to assign the subject.\n";
                delete subject;
            }
            break;
        }
        case 6: {
            university.showUniversity();
            break;
        }
        case 7: {
            cout << "Enter student's ID, subject's name, and grade: ";
            cin >> id >> name >> grade;
            university.assignGrade(id, name, grade);
            break;
        }
        case 8: {
            cout << "Enter student's ID: ";
            cin >> id;
            auto studentIt = find_if(university.getStudents().begin(), university.getStudents().end(),
                [id](Student* student) { return student->getId() == id; });
            if (studentIt != university.getStudents().end()) {
                (*studentIt)->showGrades();
            }
            else {
                cout << "Student not found.\n";
            }
            break;
        }
        case 9: {
            cout << "Choose who you want to grant a bonus.\n1. For student\n2. For lecturer\n";
            cin >> type;
            switch (type) {
            case 1: {
                for (const auto& student : university.getStudents()) {
                    cout << "Student ID: " << student->getId() << ", Name: " << student->getPersonalInfo().getName() << " (Age: " << student->getPersonalInfo().getAge() << ")\n";
                }
                cout << "Choose student ID: ";
                cin >> id;

                Student* student = university.getStudent(id);
                if (!student) {
                    cout << "Student not found.\n";
                    break;
                }

                float bonusSize;
                cout << "Provide bonus size: ";
                cin >> bonusSize;

                cout << "Choose a bonus reason:\n";
                Bonus::showReasons(reasons::student);

                int reason;
                cin >> reason;
                studentReason sReason = static_cast<studentReason>(reason);

                StudentBonus* studentBonus = new StudentBonus(sReason, bonusSize);
                student->addBonus(studentBonus);

                cout << "Bonus reasons:\n";
                for (const auto& reason : studentBonus->ShowReason()) {
                    cout << reason << "\n";
                }

                break;
            }
            case 2: {
                for (const auto& lecturer : university.getLecturers()) {
                    cout << "Lecturer ID: " << lecturer->getId() << ", Name: " << lecturer->getPersonalInfo().getName() << " (Age: " << lecturer->getPersonalInfo().getAge() << ")\n";
                }
                cout << "Choose lecturer ID: ";
                cin >> id;

                Lecturer* lecturer = university.getLecturer(id);
                if (!lecturer) {
                    cout << "Lecturer not found.\n";
                    break;
                }

                float bonusSize;
                cout << "Provide bonus size: ";
                cin >> bonusSize;

                cout << "Choose a bonus reason:\n";
                Bonus::showReasons(reasons::lecturer);

                int reason;
                cin >> reason;
                lecturerReason lReason = static_cast<lecturerReason>(reason);

                LecturerBonus* lecturerBonus = new LecturerBonus(lReason, bonusSize);
                lecturer->addBonus(lecturerBonus);

                cout << "Bonus reasons:\n";
                for (const auto& reason : lecturerBonus->ShowReason()) {
                    cout << reason << "\n";
                }

                break;
            }
            default:
                cout << "Invalid option. Try again.\n";
                break;
            }
            break;
        }
        case 0:
            return 0;
        default:
            cout << "Invalid option. Try again.\n";
            break;
        }
    }
}
