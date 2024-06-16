#pragma once

#include <iostream>
#include <vector>
#include <string_view>
#include <cmath>
#include <string>

using namespace std;

enum class reasons {
    student,
    lecturer
};

enum class studentReason {
    studentReaso1,
    studentReaso2,
    studentReaso3,
    Count
};

enum class lecturerReason {
    lecturerReason1,
    lecturerReason2,
    lecturerReason3,
    Count
};

class Bonus
{
public:
    virtual ~Bonus() = default;
    virtual vector<string_view> ShowReason() const = 0;
    virtual int AppendBonus(float appendSize) = 0;
    virtual int AppendBonus(int appendSize) = 0;

    static void showReasons(reasons r);

protected:
    Bonus(int bonusSize, string_view laureateType)
        : bonusSize(bonusSize), laureateType(laureateType) {}

    int bonusSize;
    const string_view laureateType;

    static string enumToString(studentReason reason);
    static string enumToString(lecturerReason reason);
};

class StudentBonus : public Bonus
{
public:
    StudentBonus(studentReason reason, int bonusSize);
    StudentBonus(studentReason reason, float bonusSize);

    vector<string_view> ShowReason() const override;
    bool AddReason(studentReason reason);
    int AppendBonus(float appendSize) override;
    int AppendBonus(int appendSize) override;

private:
    vector<studentReason> studentReasons;
};

class LecturerBonus : public Bonus
{
public:
    LecturerBonus(lecturerReason reason, int bonusSize);
    LecturerBonus(lecturerReason reason, float bonusSize);

    vector<string_view> ShowReason() const override;
    bool AddReason(lecturerReason reason);
    int AppendBonus(float appendSize) override;
    int AppendBonus(int appendSize) override;

private:
    vector<lecturerReason> lecturerReasons;
};
