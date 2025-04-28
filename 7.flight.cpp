/*
There are flight paths between cities. If there is a flight between city A and city B then
there is an edge between the cities. The cost of the edge can be the time that flight take
to reach city B from A, or the amount of fuel used for the journey. Represent this as a
graph. The node can be represented by airport name or name of the city. Use adjacency
list representation of the graph or use adjacency matrix representation of the graph.
Check whether the graph is connected or not. Justify the storage representation used
*/
#include <iostream>
using namespace std;

int Adj_Matrix[10][10];

void DFS(int current, bool visited[], int CityNo) {
    visited[current] = true;
    for (int i = 0; i < CityNo; i++) {
        if (Adj_Matrix[current][i] != 0 && !visited[i]) {
            DFS(i, visited, CityNo);
        }
    }
}

int main() {
    int CityNo;
    cout << "Enter the no. of Cities (max 10): ";
    cin >> CityNo;

    if (CityNo > 10 || CityNo <= 0) {
        cout << "Invalid number of cities. Please enter a number between 1 and 10." << endl;
        return 1;
    }

    string CityName[CityNo];

    for (int i = 0; i < CityNo; i++) {
        cout << "Enter name of city no. " << i + 1 << ": ";
        cin >> CityName[i];
    }

    for (int i = 0; i < CityNo; i++) {
        for (int j = 0; j < CityNo; j++) {
            Adj_Matrix[i][j] = 0;
        }
    }

    cout << "Enter the Time required to fly between Cities in hrs : " << endl;

    for (int i = 0; i < CityNo; i++) {
        for (int j = i + 1; j < CityNo; j++) {
            int time;
            cout << CityName[i] << " and " << CityName[j] << " = ";
            cin >> time;
            Adj_Matrix[i][j] = time;
            Adj_Matrix[j][i] = time;
        }
    }

    cout << "\nAdjacency Matrix:\n";
    cout << "\t";
    for (int i = 0; i < CityNo; i++) {
        cout << CityName[i] << "\t";
    }
    cout << endl;

    for (int i = 0; i < CityNo; i++) {
        cout << CityName[i] << "\t";
        for (int j = 0; j < CityNo; j++) {
            cout << Adj_Matrix[i][j] << "\t";
        }
        cout << endl;
    }

    bool visited[10] = {false};

    // Start DFS from city 0
    DFS(0, visited, CityNo);

    bool isConnected = true;
    for (int i = 0; i < CityNo; i++) {
        if (!visited[i]) {
            isConnected = false;
            break;
        }
    }

    if (isConnected) {
        cout << "\nGraph is connected." << endl;
    } else {
        cout << "\nGraph is not connected." << endl;
    }

    return 0;
}
