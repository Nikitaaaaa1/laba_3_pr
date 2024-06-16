#pragma once
#ifndef STUDENT_H_
#define STUDENT_H_

#include <vector>
#include <iostream>
#include "PersonalData.h"
#include "Subject.h"
#include "Bonus.h"

using namespace std;

class Subject;
class University; // Forward declaration

class Student {
private:
    int id;
    PersonalData personalInfo;
    vector<Subject*> selectedSubjects;
    vector<vector<int>> grades;
    vector<StudentBonus*> bonuses;
    static University* university; 

public:
    Student(int id, int age, const string& name, int generalId) : id(id), personalInfo(age, name, generalId) {}
    Student(int id, int age, const string& name) : id(id), personalInfo(age, name) {}
    Student(const Student& other); 
    Student& operator=(const Student& other); 

    int getId() const { return id; }
    PersonalData getPersonalInfo() const { return personalInfo; }
    const vector<Subject*>& getSelectedSubjects() const { return selectedSubjects; }
    const vector<vector<int>>& getGrades() const { return grades; }

    void addSubject(Subject* subject);
    void addGrade(size_t subjectIndex, int grade);
    void showGrades() const;
    void showBonuses() const;

    void addBonus(StudentBonus* bonus) {
        bonuses.push_back(bonus);
    }

    Subject* operator[](size_t index) const;

    static void setUniversity(University* uni) { university = uni; }
    static University* getUniversity() { return university; }
};

#endif // STUDENT_H_
