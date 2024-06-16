#include "University.h"
#include <array>
#include <iostream>
#include <algorithm>
#include <random>
#include <string>

using namespace std;

constexpr array<const char*, 10> firstNames = { "John", "Jane", "Alice", "Bob", "Charlie", "Diana", "Edward", "Fiona", "George", "Hannah" };
constexpr array<const char*, 10> lastNames = { "Smith", "Johnson", "Williams", "Brown", "Jones", "Garcia", "Miller", "Davis", "Rodriguez", "Martinez" };
constexpr array<const char*, 5> subjectNames = { "Math", "Physics", "Chemistry", "Biology", "History" };

University::~University() {
    for (auto lecturer : lecturers) {
        delete lecturer;
    }
    for (auto student : students) {
        delete student;
    }
}

Lecturer* University::getLecturer(int id) {
    auto it = find_if(lecturers.begin(), lecturers.end(),
        [id](Lecturer* lecturer) { return lecturer->getId() == id; });
    if (it != lecturers.end()) {
        return *it;
    }
    return nullptr;
}

void University::addLecturer(Lecturer* lecturer) {
    lecturers.push_back(lecturer);
}

void University::deleteLecturer(int id) {
    auto it = find_if(lecturers.begin(), lecturers.end(),
        [id](Lecturer* lecturer) { return lecturer->getId() == id; });
    if (it != lecturers.end()) {
        delete* it;
        lecturers.erase(it);
        cout << "Lecturer with ID " << id << " deleted.\n";
    }
    else {
        cout << "Lecturer with ID " << id << " not found.\n";
    }
}

Student* University::getStudent(int id) {
    auto it = find_if(students.begin(), students.end(),
        [id](Student* student) { return student->getId() == id; });
    if (it != students.end()) {
        return *it;
    }
    return nullptr;
}

void University::addStudent(Student* student) {
    students.push_back(student);
}

void University::deleteStudent(int id) {
    auto it = find_if(students.begin(), students.end(),
        [id](Student* student) { return student->getId() == id; });
    if (it != students.end()) {
        delete* it;
        students.erase(it);
        cout << "Student with ID " << id << " deleted.\n";
    }
    else {
        cout << "Student with ID " << id << " not found.\n";
    }
}

void University::showUniversity() const {
    for (const auto& lecturer : lecturers) {
        cout << "Lecturer ID: " << lecturer->getId() << ", Name: " << lecturer->getPersonalInfo().getName() << " (Age: " << lecturer->getPersonalInfo().getAge() << ")\n";
        lecturer->showSubjects();
        lecturer->showBonuses();
    }
    for (const auto& student : students) {
        cout << "Student ID: " << student->getId() << ", Name: " << student->getPersonalInfo().getName() << " (Age: " << student->getPersonalInfo().getAge() << ")\n";
        student->showGrades();
        student->showBonuses();
    }
}

void University::generateRandomData() {
    random_device rd;
    default_random_engine engine(rd());
    uniform_int_distribution<int> distAge(18, 65);
    uniform_int_distribution<int> distGrade(1, 10);
    uniform_int_distribution<int> distId(1000, 9999);
    uniform_int_distribution<int> generalDistId(10000, 99999);

    for (int i = 0; i < 5; ++i) {
        int age = distAge(engine);
        int id = distId(engine);
        int generalId = generalDistId(engine);
        string name = string(firstNames[i % firstNames.size()]) + " " + string(lastNames[i % lastNames.size()]);
        Lecturer* lecturer = new Lecturer(id, age, name, generalId);
        addLecturer(lecturer);

        for (const auto& subjectName : subjectNames) {
            Subject* subject = new Subject(subjectName, 30);
            lecturer->addSubject(subject);
        }
    }

    for (int i = 0; i < 20; ++i) {
        int age = distAge(engine);
        int id = distId(engine);
        int generalId = generalDistId(engine);
        string name = string(firstNames[i % firstNames.size()]) + " " + string(lastNames[i % lastNames.size()]);
        Student* student = new Student(id, age, name, generalId);
        addStudent(student);

        for (const auto& lecturer : lecturers) {
            for (const auto& subject : lecturer->getSubjects()) {
                if (student->getSelectedSubjects().size() < 3) {
                    student->addSubject(subject);
                }
            }
        }

        for (size_t j = 0; j < student->getSelectedSubjects().size(); ++j) {
            int numGrades = distGrade(engine);
            for (int k = 0; k < numGrades; ++k) {
                student->addGrade(j, distGrade(engine));
            }
        }
    }
}

void University::assignGrade(int studentId, const string& subjectName, int grade) {
    auto studentIt = find_if(students.begin(), students.end(),
        [studentId](Student* student) { return student->getId() == studentId; });
    if (studentIt != students.end()) {
        Student* student = *studentIt;
        for (auto& subject : student->getSelectedSubjects()) {
            if (subject->getName() == subjectName) {
                auto it = find(student->getSelectedSubjects().begin(), student->getSelectedSubjects().end(), subject);
                if (it != student->getSelectedSubjects().end()) {
                    size_t index = distance(student->getSelectedSubjects().begin(), it);
                    student->addGrade(index, grade);
                    cout << "Grade assigned.\n";
                    return;
                }
            }
        }
        cout << "Subject not found.\n";
    }
    else {
        cout << "Student not found.\n";
    }
}
