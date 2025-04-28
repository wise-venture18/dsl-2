#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Employee {
    int id;
    string name;
    string position;
    float salary;

    // For easier writing and reading to file, we override the I/O operations
    friend ostream& operator<<(ostream& os, const Employee& emp) {
        os << emp.id << '\n' << emp.name << '\n' << emp.position << '\n' << emp.salary << '\n';
        return os;
    }

    friend istream& operator>>(istream& is, Employee& emp) {
        is >> emp.id;
        is.ignore();  // To ignore the newline after id
        getline(is, emp.name);
        getline(is, emp.position);
        is >> emp.salary;
        return is;
    }
};

class EmployeeSystem {
private:
    string filename;
    string indexFilename;

    void sortIndex() {
        // Manually sorting index file based on Employee IDs
        ifstream indexFile(indexFilename, ios::binary);
        int ids[100], index = 0;
        while (indexFile.read(reinterpret_cast<char*>(&ids[index]), sizeof(ids[index]))) {
            index++;
        }

        // Manual sorting of IDs (using bubble sort for simplicity)
        for (int i = 0; i < index - 1; i++) {
            for (int j = 0; j < index - i - 1; j++) {
                if (ids[j] > ids[j + 1]) {
                    int temp = ids[j];
                    ids[j] = ids[j + 1];
                    ids[j + 1] = temp;
                }
            }
        }

        // Re-write sorted IDs into the index file
        ofstream sortedIndexFile(indexFilename, ios::binary);
        for (int i = 0; i < index; i++) {
            sortedIndexFile.write(reinterpret_cast<const char*>(&ids[i]), sizeof(ids[i]));
        }
    }

    int findEmployeeIndex(int id) {
        // Binary search for an ID in the index file
        ifstream indexFile(indexFilename, ios::binary);
        int ids[100], index = 0;
        int tempId;
        while (indexFile.read(reinterpret_cast<char*>(&tempId), sizeof(tempId))) {
            ids[index++] = tempId;
        }

        int left = 0, right = index - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (ids[mid] == id) {
                return mid;  // Found it
            }
            if (ids[mid] < id) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return -1;  // Not found
    }

public:
    EmployeeSystem(const string& file, const string& indexFile) : filename(file), indexFilename(indexFile) {}

    void addEmployee(const Employee& emp) {
        // First, check if the employee already exists using the index file
        if (findEmployeeIndex(emp.id) != -1) {
            cout << "Employee with ID " << emp.id << " already exists." << endl;
            return;
        }

        // Append employee to the data file
        ofstream dataFile(filename, ios::app);
        dataFile << emp;

        // Update the index file (just append the new employee ID)
        ofstream indexFile(indexFilename, ios::app | ios::binary);
        indexFile.write(reinterpret_cast<const char*>(&emp.id), sizeof(emp.id));

        // After adding, we need to sort the index file
        sortIndex();
        cout << "Employee added successfully." << endl;
    }

    void deleteEmployee(int id) {
        // Check if the employee exists
        int index = findEmployeeIndex(id);
        if (index == -1) {
            cout << "Employee with ID " << id << " does not exist." << endl;
            return;
        }

        // Create a temporary array to hold the data
        Employee employees[100];
        int count = 0;
        ifstream dataFile(filename);
        Employee emp;
        while (dataFile >> emp) {
            if (emp.id != id) {
                employees[count++] = emp;
            }
        }

        // Rewrite the data file without the deleted employee
        ofstream dataFileOut(filename);
        for (int i = 0; i < count; i++) {
            dataFileOut << employees[i];
        }

        // Rewrite the index file without the deleted employee ID
        int ids[100], indexCount = 0;
        ifstream indexFile(indexFilename, ios::binary);
        while (indexFile.read(reinterpret_cast<char*>(&ids[indexCount]), sizeof(ids[indexCount]))) {
            indexCount++;
        }

        ofstream indexFileOut(indexFilename, ios::binary);
        for (int i = 0; i < indexCount; i++) {
            if (ids[i] != id) {
                indexFileOut.write(reinterpret_cast<const char*>(&ids[i]), sizeof(ids[i]));
            }
        }

        cout << "Employee with ID " << id << " deleted successfully." << endl;
    }

    void displayEmployees() {
        ifstream dataFile(filename);
        Employee emp;
        cout << "Employee Records:\n";
        while (dataFile >> emp) {
            cout << "ID: " << emp.id << "\nName: " << emp.name << "\nPosition: " << emp.position << "\nSalary: " << emp.salary << "\n\n";
        }
    }

    void searchEmployee(int id) {
        int index = findEmployeeIndex(id);
        if (index == -1) {
            cout << "Employee with ID " << id << " does not exist." << endl;
            return;
        }

        ifstream dataFile(filename);
        Employee emp;
        while (dataFile >> emp) {
            if (emp.id == id) {
                cout << "Employee found:\n";
                cout << "ID: " << emp.id << "\nName: " << emp.name << "\nPosition: " << emp.position << "\nSalary: " << emp.salary << endl;
                return;
            }
        }
    }
};

int main() {
    EmployeeSystem empSystem("employees.txt", "index.dat");

    int choice, id;
    Employee emp;
    do {
        cout << "\n1. Add Employee\n2. Delete Employee\n3. Display Employees\n4. Search Employee\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter employee details:\n";
            cout << "ID: ";
            cin >> emp.id;
            cin.ignore();
            cout << "Name: ";
            getline(cin, emp.name);
            cout << "Position: ";
            getline(cin, emp.position);
            cout << "Salary: ";
            cin >> emp.salary;
            empSystem.addEmployee(emp);
            break;

        case 2:
            cout << "Enter employee ID to delete: ";
            cin >> id;
            empSystem.deleteEmployee(id);
            break;

        case 3:
            empSystem.displayEmployees();
            break;

        case 4:
            cout << "Enter employee ID to search: ";
            cin >> id;
            empSystem.searchEmployee(id);
            break;

        case 5:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
