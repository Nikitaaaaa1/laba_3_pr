#include "Student.h"
#include "Subject.h"
#include "University.h"

University* Student::university = nullptr;

Student::Student(const Student& other)
    : id(other.id), personalInfo(other.personalInfo), selectedSubjects(other.selectedSubjects),
    grades(other.grades), bonuses(other.bonuses) {}

Student& Student::operator=(const Student& other) {
    if (this == &other) return *this;
    id = other.id;
    personalInfo = other.personalInfo;
    selectedSubjects = other.selectedSubjects;
    grades = other.grades;
    bonuses = other.bonuses;
    return *this;
}

void Student::addSubject(Subject* subject) {
    selectedSubjects.push_back(subject);
    grades.push_back(vector<int>());
}

void Student::addGrade(size_t subjectIndex, int grade) {
    if (subjectIndex < grades.size()) {
        grades[subjectIndex].push_back(grade);
    }
}

void Student::showGrades() const {
    cout << "Grades for student ID " << id << " (" << personalInfo.getName() << "):\n";
    for (size_t i = 0; i < selectedSubjects.size(); ++i) {
        cout << "Subject: " << selectedSubjects[i]->getName() << " - Grades: ";
        for (int grade : grades[i]) {
            cout << grade << " ";
        }
        cout << endl;
    }
}

void Student::showBonuses(bool hideName = false) const {
    !hideName && cout << "Bonuses for student ID " << id << " (" << personalInfo.getName() << "):\n";
    for (const auto& bonus : bonuses) {
        cout << "Bonus size: " << to_string(bonus->AppendBonus(0) / 100)   << "\nReasons: ";
        for (const auto& reason : bonus->ShowReason()) {
            cout << reason << " ";
        }
        cout << endl;
    }
}

Subject* Student::operator[](size_t index) const {
    if (index < selectedSubjects.size()) {
        return selectedSubjects[index];
    }
    return nullptr;
}
