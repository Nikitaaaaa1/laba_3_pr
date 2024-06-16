#pragma once
#ifndef PERSONAL_DATA_H_
#define PERSONAL_DATA_H_

#include <string>
#include <algorithm>
#include <random>

using namespace std;
class PersonalData {
protected:
    int generalId;
private:
    int age;
    string name;
public:
    PersonalData(int age, const string& name, int id) : age(age), name(name), generalId(id) {}
    PersonalData(int age, const string& name);
    int getAge() const { return age; }
    string getName() const { return name; }
};
#endif 