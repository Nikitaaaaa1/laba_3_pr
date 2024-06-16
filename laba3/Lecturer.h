#pragma once
#ifndef LECTURER_H_
#define LECTURER_H_

#include <vector>
#include "Subject.h"
#include "PersonalData.h"
#include "Bonus.h"

class Lecturer {
private:
    int id;
    PersonalData personalInfo;
    vector<Subject*> subjects;
    vector<LecturerBonus*> bonuses;

public:
    Lecturer(int id, int age, const string& name, int generalId) : id(id), personalInfo(age, name, generalId) {}
    Lecturer(int id, int age, const string& name) : id(id), personalInfo(age, name) {}
    Lecturer(const Lecturer& other); 
    Lecturer& operator=(const Lecturer& other); 

    int getId() const { return id; }
    PersonalData getPersonalInfo() const { return personalInfo; }
    const vector<Subject*>& getSubjects() const { return subjects; }

    void addBonus(LecturerBonus* bonus) {
        bonuses.push_back(bonus);
    }

    void showBonuses(bool hideName = false) const {
        !hideName && cout << "Bonuses for lecturer ID " << id << " (" << personalInfo.getName() << "):\n";
        for (const auto& bonus : bonuses) {
            cout << "Bonus size: " << bonus->AppendBonus(0) / 100 << "\nReasons: ";
            for (const auto& reason : bonus->ShowReason()) {
                cout << reason << " ";
            }
            cout << endl;
        }
    }

    void addSubject(Subject* subject);
    void calculateAverage() const;
    void showSubjects() const;

    Subject* operator[](size_t index) const;
};

#endif // LECTURER_H_
