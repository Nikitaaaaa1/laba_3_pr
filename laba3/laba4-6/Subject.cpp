#include "Subject.h"


void Subject::addStudent(Student* student) {
    if (enrolledStudents.size() < static_cast<size_t>(studentCapacity)) {
        enrolledStudents.push_back(student);
    }
    else {
        cout << "Subject " << name << " is full." << endl;
    }
}