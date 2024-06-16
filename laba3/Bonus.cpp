#include "Bonus.h"

string_view Bonus::enumToString(studentReason reason) {
    switch (reason) {
    case studentReason::studentReason1: return "studentReason1";
    case studentReason::studentReason2: return "studentReason2";
    case studentReason::studentReason3: return "studentReason3";
    default: return "Unknown";
    }
}

string_view Bonus::enumToString(lecturerReason reason) {
    switch (reason) {
    case lecturerReason::lecturerReason1: return "lecturerReason1";
    case lecturerReason::lecturerReason2: return "lecturerReason2";
    case lecturerReason::lecturerReason3: return "lecturerReason3";
    default: return "Unknown";
    }
}

void Bonus::showReasons(reasons r) {
    if (r == reasons::student) {
        for (int i = 0; i < static_cast<int>(studentReason::Count); ++i) {
            studentReason reason = static_cast<studentReason>(i);
            std::cout << "Student Reason: " << i << " - " << enumToString(reason) << std::endl;
        }
    }
    else if (r == reasons::lecturer) {
        for (int i = 0; i < static_cast<int>(lecturerReason::Count); ++i) {
            lecturerReason reason = static_cast<lecturerReason>(i);
            std::cout << "Lecturer Reason: " << i << " - " << enumToString(reason) << std::endl;
        }
    }
}


StudentBonus::StudentBonus(studentReason reason, int bonusSize)
    : Bonus(bonusSize * 100, "Student") {
    AddReason(reason);
}

StudentBonus::StudentBonus(studentReason reason, float bonusSize)
    : Bonus(static_cast<int>(bonusSize * 100), "Student") {
    AddReason(reason);
}

vector<string_view> StudentBonus::ShowReason() const {
    vector<string_view> reasonsList;
    for (const auto& reason : studentReasons) {
        reasonsList.push_back(enumToString(reason));
    }
    return reasonsList;
}

bool StudentBonus::AddReason(studentReason reason) {
    studentReasons.push_back(reason);
    return true;
}

int StudentBonus::AppendBonus(float appendSize) {
    bonusSize += static_cast<int>(appendSize * 100);
    return bonusSize;
}

int StudentBonus::AppendBonus(int appendSize) {
    bonusSize += appendSize * 100;
    return bonusSize;
}


LecturerBonus::LecturerBonus(lecturerReason reason, int bonusSize)
    : Bonus(static_cast<int>(bonusSize * 100), "Lecturer") {
    AddReason(reason);
}

LecturerBonus::LecturerBonus(lecturerReason reason, float bonusSize)
    : Bonus(static_cast<int>(bonusSize * 100), "Lecturer") {
    AddReason(reason);
}

vector<string_view> LecturerBonus::ShowReason() const {
    vector<string_view> reasonsList;
    for (const auto& reason : lecturerReasons) {
        reasonsList.push_back(enumToString(reason));
    }
    return reasonsList;
}

bool LecturerBonus::AddReason(lecturerReason reason) {
    lecturerReasons.push_back(reason);
    return true;
}

int LecturerBonus::AppendBonus(float appendSize) {
    bonusSize += static_cast<int>(round(appendSize * 100));
    return bonusSize;
}

int LecturerBonus::AppendBonus(int appendSize) {
    bonusSize += appendSize * 100;
    return bonusSize;
}
