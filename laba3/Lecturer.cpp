#include "Lecturer.h"
#include "Subject.h"

Lecturer::Lecturer(const Lecturer& other)
    : id(other.id), personalInfo(other.personalInfo), subjects(other.subjects),
    bonuses(other.bonuses) {}

Lecturer& Lecturer::operator=(const Lecturer& other) {
    if (this == &other) return *this;
    id = other.id;
    personalInfo = other.personalInfo;
    subjects = other.subjects;
    bonuses = other.bonuses;
    return *this;
}

void Lecturer::addSubject(Subject* subject) {
    subjects.push_back(subject);
}
void Lecturer::calculateAverage() const {
    for (const auto& subject : subjects) {
        double total = 0;
        int count = 0;
        for (const auto& student : subject->getEnrolledStudents()) {
            for (const auto& grades : student->getGrades()) {
                for (int grade : grades) {
                    total += grade;
                    count++;
                }
            }
        }
        cout << "Average grade for " << subject->getName() << ": " << (count ? total / count : 0) << endl;
    }
}

void Lecturer::showSubjects() const {
    cout << "Subjects for lecturer ID " << id << " (" << personalInfo.getName() << "):\n";
    for (const auto& subject : subjects) {
        cout << "Subject: " << subject->getName() << endl;
    }
}


Subject* Lecturer::operator[](size_t index) const {
    if (index < subjects.size()) {
        return subjects[index];
    }
    return nullptr;
}