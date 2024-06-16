#pragma once
#ifndef UNIVERSITY_H_
#define UNIVERSITY_H_

#include <vector>
#include "Student.h"
#include "Lecturer.h"

using namespace std;

class University {
private:
    vector<Student*> students;
    vector<Lecturer*> lecturers;

public:
    ~University();

    Lecturer* getLecturer(int id);
    void addLecturer(Lecturer* lecturer);
    void deleteLecturer(int id);
    vector<Lecturer*> getLecturers() const { return lecturers; }

    Student* getStudent(int id);
    void addStudent(Student* student);
    void deleteStudent(int id);
    vector<Student*> getStudents() const { return students; }

    void showUniversity() const;
    void generateRandomData();
    void assignGrade(int studentId, const string& subjectName, int grade);
};

#endif // UNIVERSITY_H_
