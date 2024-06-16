#pragma once

#include <string>
#include <vector>
#include "Student.h"
using namespace std;


class Subject;
class Student;


class Subject {
private:
    string name;
    int studentCapacity;
    vector<Student*> enrolledStudents;
public:
    Subject(const string& name, int studentCapacity) : name(name), studentCapacity(studentCapacity) {};

    string getName() const { return name; }
    int getStudentCapacity() const { return studentCapacity; }
    const vector<Student*>& getEnrolledStudents() const { return enrolledStudents; }

    void addStudent(Student* student);
};
