#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Student {
    int rollNo;
    string name;
    string course;
};

// Function to add a new student record
void addStudent() {
    ofstream outFile("students.txt", ios::app); // append mode
    Student s;
    cout << "Enter Roll No: ";
    cin >> s.rollNo;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, s.name);
    cout << "Enter Course: ";
    getline(cin, s.course);

    outFile << s.rollNo << " " << s.name << " " << s.course << endl;
    outFile.close();
    cout << "Student record added successfully.\n";
}

// Function to display all student records
void displayStudents() {
    ifstream inFile("students.txt");
    Student s;
    bool found = false;

    cout << "\n--- Student Records ---\n";
    while (inFile >> s.rollNo) {
        inFile.ignore();
        getline(inFile, s.name, ' ');
        getline(inFile, s.course);
        cout << "Roll No: " << s.rollNo << ", Name: " << s.name << ", Course: " << s.course << endl;
        found = true;
    }
    inFile.close();

    if (!found) {
        cout << "No student records found.\n";
    }
}

// Function to delete a student record by roll number
void deleteStudent() {
    int roll;
    cout << "Enter Roll No to delete: ";
    cin >> roll;

    ifstream inFile("students.txt");
    ofstream tempFile("temp.txt");

    Student s;
    bool found = false;
    while (inFile >> s.rollNo) {
        inFile.ignore();
        getline(inFile, s.name, ' ');
        getline(inFile, s.course);

        if (s.rollNo != roll) {
            tempFile << s.rollNo << " " << s.name << " " << s.course << endl;
        } else {
            found = true;
        }
    }
    inFile.close();
    tempFile.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found) {
        cout << "Student record deleted successfully.\n";
    } else {
        cout << "Student with Roll No " << roll << " not found.\n";
    }
}

// Function to search for a student by roll number
void searchStudent() {
    int roll;
    cout << "Enter Roll No to search: ";
    cin >> roll;

    ifstream inFile("students.txt");
    Student s;
    bool found = false;

    while (inFile >> s.rollNo) {
        inFile.ignore();
        getline(inFile, s.name, ' ');
        getline(inFile, s.course);

        if (s.rollNo == roll) {
            cout << "\nStudent found:\n";
            cout << "Roll No: " << s.rollNo << ", Name: " << s.name << ", Course: " << s.course << endl;
            found = true;
            break;
        }
    }
    inFile.close();

    if (!found) {
        cout << "Student with Roll No " << roll << " not found.\n";
    }
}

int main() {
    int choice;
    do {
        cout << "\n--- Student Information System ---\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Delete Student\n";
        cout << "4. Search Student by Roll No\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: deleteStudent(); break;
            case 4: searchStudent(); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while(choice != 5);

    return 0;
}
