#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <cctype>
#include <sstream>
#include <array>

using namespace std;

constexpr array<const char*, 10> firstNames = { "John", "Jane", "Alice", "Bob", "Charlie", "Diana", "Edward", "Fiona", "George", "Hannah" };
constexpr array<const char*, 10> lastNames = { "Smith", "Johnson", "Williams", "Brown", "Jones", "Garcia", "Miller", "Davis", "Rodriguez", "Martinez" };
constexpr array<const char*, 5> subjectNames = { "Math", "Physics", "Chemistry", "Biology", "History" };

class PersonalData {
private:
    int age;
    string name;
public:
    PersonalData(int age, const string& name) : age(age), name(name) {}
    int getAge() const { return age; }
    string getName() const { return name; }
};

class Subject;
class Student;

class Student {
private:
    int id;
    PersonalData personalInfo;
    vector<Subject*> selectedSubjects;
    vector<vector<int>> grades;
public:
    Student(int id, int age, const string& name) : id(id), personalInfo(age, name) {}

    int getId() const { return id; }
    PersonalData getPersonalInfo() const { return personalInfo; }
    const vector<Subject*>& getSelectedSubjects() const { return selectedSubjects; }
    const vector<vector<int>>& getGrades() const { return grades; }

    void addSubject(Subject* subject);
    void addGrade(size_t subjectIndex, int grade);
    void showGrades() const;
};

class Subject {
private:
    string name;
    int studentCapacity;
    vector<Student*> enrolledStudents;
public:
    Subject(const string& name, int studentCapacity) : name(name), studentCapacity(studentCapacity) {}

    string getName() const { return name; }
    int getStudentCapacity() const { return studentCapacity; }
    const vector<Student*>& getEnrolledStudents() const { return enrolledStudents; }

    void addStudent(Student* student);
};

class Lecturer {
private:
    PersonalData personalInfo;
    vector<Subject*> subjects;
public:
    Lecturer(int age, const string& name) : personalInfo(age, name) {}

    PersonalData getPersonalInfo() const { return personalInfo; }
    const vector<Subject*>& getSubjects() const { return subjects; }

    void addSubject(Subject* subject);
    void calculateAverage() const;
    void showSubjects() const;
};

class University {
private:
    vector<Lecturer*> lecturers;
    vector<Student*> students;
public:
    ~University();
    const vector<Lecturer*>& getLecturers() const { return lecturers; }
    const vector<Student*>& getStudents() const { return students; }

    void addLecturer(Lecturer* lecturer);
    void deleteLecturer(Lecturer* lecturer);
    void addStudent(Student* student);
    void deleteStudent(Student* student);
    void showUniversity() const;
    void generateRandomData();
    void assignGrade(int studentId, const string& subjectName, int grade);
};

void Student::addSubject(Subject* subject) {
    selectedSubjects.push_back(subject);
    grades.emplace_back();
    subject->addStudent(this);
}

void Student::addGrade(size_t subjectIndex, int grade) {
    if (subjectIndex < grades.size()) {
        grades[subjectIndex].push_back(grade);
    }
}

void Student::showGrades() const {
    for (size_t i = 0; i < selectedSubjects.size(); ++i) {
        const Subject* subject = selectedSubjects[i];
        cout << "Grades for " << subject->getName() << ": ";
        for (int grade : grades[i]) {
            cout << grade << " ";
        }
        cout << endl;
    }
}

void Subject::addStudent(Student* student) {
    if (enrolledStudents.size() < static_cast<size_t>(studentCapacity)) {
        enrolledStudents.push_back(student);
    }
    else {
        cout << "Subject " << name << " is full." << endl;
    }
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
    for (const auto& subject : subjects) {
        cout << "Subject: " << subject->getName() << " with " << subject->getEnrolledStudents().size() << " students\n";
    }
}

University::~University() {
    for (auto lecturer : lecturers) {
        delete lecturer;
    }
    for (auto student : students) {
        delete student;
    }
}

void University::addLecturer(Lecturer* lecturer) {
    lecturers.push_back(lecturer);
}

void University::deleteLecturer(Lecturer* lecturer) {
    auto it = find(lecturers.begin(), lecturers.end(), lecturer);
    if (it != lecturers.end()) {
        lecturers.erase(it);
        delete lecturer;
    }
}

void University::addStudent(Student* student) {
    students.push_back(student);
}

void University::deleteStudent(Student* student) {
    auto it = find(students.begin(), students.end(), student);
    if (it != students.end()) {
        students.erase(it);
        delete student;
    }
}

void University::showUniversity() const {
    for (const auto& lecturer : lecturers) {
        cout << "Lecturer: " << lecturer->getPersonalInfo().getName() << " (Age: " << lecturer->getPersonalInfo().getAge() << ")\n";
        lecturer->showSubjects();
    }
    for (const auto& student : students) {
        cout << "Student ID: " << student->getId() << ", Name: " << student->getPersonalInfo().getName() << " (Age: " << student->getPersonalInfo().getAge() << ")\n";
        student->showGrades();
    }
}

void University::generateRandomData() {
    random_device rd;
    default_random_engine engine(rd());
    uniform_int_distribution<int> distAge(18, 65);
    uniform_int_distribution<int> distGrade(1, 10);
    uniform_int_distribution<int> distId(1000, 9999);

    for (int i = 0; i < 5; ++i) {
        int age = distAge(engine);
        string name = string(firstNames[i % firstNames.size()]) + " " + string(lastNames[i % lastNames.size()]);
        Lecturer* lecturer = new Lecturer(age, name);
        addLecturer(lecturer);

        for (const auto& subjectName : subjectNames) {
            Subject* subject = new Subject(subjectName, 30);
            lecturer->addSubject(subject);
        }
    }

    for (int i = 0; i < 20; ++i) {
        int age = distAge(engine);
        int id = distId(engine);
        string name = string(firstNames[i % firstNames.size()]) + " " + string(lastNames[i % lastNames.size()]);
        Student* student = new Student(id, age, name);
        addStudent(student);

        for (const auto& lecturer : lecturers) {
            for (const auto& subject : lecturer->getSubjects()) {
                if (student->getSelectedSubjects().size() < 3) {
                    student->addSubject(subject);
                }
            }
        }

        for (size_t j = 0; j < student->getSelectedSubjects().size(); ++j) {
            int numGrades = distGrade(engine);
            for (int k = 0; k < numGrades; ++k) {
                student->addGrade(j, distGrade(engine));
            }
        }
    }
}

void University::assignGrade(int studentId, const string& subjectName, int grade) {
    auto studentIt = find_if(students.begin(), students.end(),
        [studentId](Student* student) { return student->getId() == studentId; });
    if (studentIt != students.end()) {
        Student* student = *studentIt;
        for (auto& subject : student->getSelectedSubjects()) {
            if (subject->getName() == subjectName) {
                auto it = find(student->getSelectedSubjects().begin(), student->getSelectedSubjects().end(), subject);
                if (it != student->getSelectedSubjects().end()) {
                    size_t index = distance(student->getSelectedSubjects().begin(), it);
                    student->addGrade(index, grade);
                    cout << "Grade assigned.\n";
                    return;
                }
            }
        }
        cout << "Subject not found.\n";
    }
    else {
        cout << "Student not found.\n";
    }
}

void generateRandomRecords(vector<string>& records) {
    random_device rd;
    default_random_engine engine(rd());
    uniform_int_distribution<int> distNumRecords(50, 100);

    int numRecords = distNumRecords(engine);
    records.reserve(numRecords);

    for (int i = 0; i < numRecords; ++i) {
        string record = string(firstNames[i % firstNames.size()]) + " " + string(lastNames[i % lastNames.size()]) + " teaches " + string(subjectNames[i % subjectNames.size()]) + " in group " + to_string(i) + "A_23/24_S15";
        records.push_back(record);
    }
}

void displayRecords(const vector<string>& records) {
    for (const auto& record : records) {
        cout << record << endl;
    }
}

void parseRecord(const string& record) {
    istringstream stream(record);
    string firstName, lastName, teaches, subject, in, group;
    stream >> firstName >> lastName >> teaches >> subject >> in >> group;

    if (!firstName.empty() && islower(firstName[0])) {
        firstName[0] = toupper(firstName[0]);
    }
    if (!lastName.empty() && islower(lastName[0])) {
        lastName[0] = toupper(lastName[0]);
    }

    cout << "Parsed Record: " << firstName << " " << lastName << " teaches " << subject << " in " << group << endl;
}

int main() {
    University university;
    int option;
    string name;
    int age, id, capacity, grade;

    university.generateRandomData();

    while (true) {
        cout << "1. Add Lecturer\n2. Delete Lecturer\n3. Add Student\n4. Delete Student\n5. Add Subject\n6. Show University Data\n7. Assign Grade to Student\n8. Show Grades of Student\n9. Generate and Display Records\n10. Parse a Record\n0. Exit\n";
        cin >> option;
        switch (option) {
        case 1: {
            cout << "Enter lecturer's name and age: ";
            cin >> name >> age;
            Lecturer* lecturer = new Lecturer(age, name);
            university.addLecturer(lecturer);
            break;
        }
        case 2: {
            if (!university.getLecturers().empty()) {
                Lecturer* lecturer = university.getLecturers().front();
                university.deleteLecturer(lecturer);
                cout << "First lecturer deleted.\n";
            }
            else {
                cout << "No lecturers to delete.\n";
            }
            break;
        }
        case 3: {
            cout << "Enter student's name, age, and ID: ";
            cin >> name >> age >> id;
            Student* student = new Student(id, age, name);
            university.addStudent(student);
            break;
        }
        case 4: {
            if (!university.getStudents().empty()) {
                Student* student = university.getStudents().front();
                university.deleteStudent(student);
                cout << "First student deleted.\n";
            }
            else {
                cout << "No students to delete.\n";
            }
            break;
        }
        case 5: {
            cout << "Enter subject's name and capacity: ";
            cin >> name >> capacity;
            Subject* subject = new Subject(name, capacity);
            if (!university.getLecturers().empty()) {
                Lecturer* lecturer = university.getLecturers().front();
                lecturer->addSubject(subject);
                cout << "Subject added to first lecturer.\n";
            }
            else {
                cout << "No lecturers available to assign the subject.\n";
                delete subject;
            }
            break;
        }
        case 6: {
            university.showUniversity();
            break;
        }
        case 7: {
            cout << "Enter student's ID, subject's name, and grade: ";
            cin >> id >> name >> grade;
            university.assignGrade(id, name, grade);
            break;
        }
        case 8: {
            cout << "Enter student's ID: ";
            cin >> id;
            auto studentIt = find_if(university.getStudents().begin(), university.getStudents().end(),
                [id](Student* student) { return student->getId() == id; });
            if (studentIt != university.getStudents().end()) {
                (*studentIt)->showGrades();
            }
            else {
                cout << "Student not found.\n";
            }
            break;
        }
        case 9: {
            vector<string> records;
            generateRandomRecords(records);
            displayRecords(records);
            break;
        }
        case 10: {
            cout << "Enter a record to parse: ";
            string record;
            cin.ignore();
            getline(cin, record);
            parseRecord(record);
            break;
        }
        case 0:
            return 0;
        default:
            cout << "Invalid option. Try again.\n";
            break;
        }
    }
}
