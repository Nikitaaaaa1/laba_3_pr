#include "Bonus.h"

string Bonus::enumToString(studentReason reason) {
    switch (reason) {
    case studentReason::illness: return "illness";
    default: return "Unknown";
    }
}

string Bonus::enumToString(lecturerReason reason) {
    switch (reason) {
    case lecturerReason::olimpiadeWon: return "olimpiadeWon";
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
    : Bonus(bonusSize, "Student") {
    AddReason(reason);
}

StudentBonus::StudentBonus(studentReason reason, float bonusSize)
    : Bonus(static_cast<int>(std::round(bonusSize * 100)), "Student") {
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
    bonusSize += static_cast<int>(std::round(appendSize * 100));
    return bonusSize;
}

int StudentBonus::AppendBonus(int appendSize) {
    bonusSize += appendSize;
    return bonusSize;
}


LecturerBonus::LecturerBonus(lecturerReason reason, int bonusSize)
    : Bonus(bonusSize, "Lecturer") {
    AddReason(reason);
}

LecturerBonus::LecturerBonus(lecturerReason reason, float bonusSize)
    : Bonus(static_cast<int>(std::round(bonusSize * 100)), "Lecturer") {
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
    bonusSize += static_cast<int>(std::round(appendSize * 100));
    return bonusSize;
}

int LecturerBonus::AppendBonus(int appendSize) {
    bonusSize += appendSize;
    return bonusSize;
}
