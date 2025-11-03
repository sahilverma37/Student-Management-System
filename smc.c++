#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student {
public:
    int rollNo;
    string name;
    float marks;

    void getData() {
        cout << "\nEnter Roll No: ";
        cin >> rollNo;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Marks: ";
        cin >> marks;
    }

    void showData() {
        cout << "\nRoll No: " << rollNo;
        cout << "\nName: " << name;
        cout << "\nMarks: " << marks << endl;
    }
};

void addStudent() {
    Student s;
    ofstream file("students.txt", ios::app);
    s.getData();
    file << s.rollNo << "," << s.name << "," << s.marks << endl;
    file.close();
    cout << "\nStudent record added successfully!\n";
}

void displayStudents() {
    ifstream file("students.txt");
    string line;
    cout << "\n----- Student Records -----\n";
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

void searchStudent(int rollNo) {
    ifstream file("students.txt");
    string line;
    bool found = false;
    while (getline(file, line)) {
        int pos = line.find(",");
        int r = stoi(line.substr(0, pos));
        if (r == rollNo) {
            cout << "\nStudent Found: " << line << endl;
            found = true;
            break;
        }
    }
    if (!found)
        cout << "\nRecord not found!\n";
    file.close();
}

void deleteStudent(int rollNo) {
    ifstream file("students.txt");
    ofstream temp("temp.txt");
    string line;
    bool deleted = false;

    while (getline(file, line)) {
        int pos = line.find(",");
        int r = stoi(line.substr(0, pos));
        if (r != rollNo)
            temp << line << endl;
        else
            deleted = true;
    }
    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (deleted)
        cout << "\nRecord deleted successfully!\n";
    else
        cout << "\nRecord not found!\n";
}

int main() {
    int choice, rollNo;

    do {
        cout << "\n===== Student Management System =====";
        cout << "\n1. Add Student";
        cout << "\n2. Display All Students";
        cout << "\n3. Search Student";
        cout << "\n4. Delete Student";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addStudent();
            break;
        case 2:
            displayStudents();
            break;
        case 3:
            cout << "\nEnter Roll No to Search: ";
            cin >> rollNo;
            searchStudent(rollNo);
            break;
        case 4:
            cout << "\nEnter Roll No to Delete: ";
            cin >> rollNo;
            deleteStudent(rollNo);
            break;
        case 5:
            cout << "\nExiting program...";
            break;
        default:
            cout << "\nInvalid choice! Try again.";
        }
    } while (choice != 5);

    return 0;
}