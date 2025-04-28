#include <iostream>
#include <climits>
#include <cfloat> // Include cfloat to access FLT_MAX

using namespace std;

// Function to calculate the minimum search cost of an optimal binary search tree
float optimalBST(int keys[], float freq[], int n) {
    float cost[n][n]; // Table to store the minimum cost for each subproblem

    // Fill the diagonal elements (cost of a single node is its frequency)
    for (int i = 0; i < n; i++) {
        cost[i][i] = freq[i];
    }

    // Build the table using dynamic programming
    for (int len = 2; len <= n; len++) { // len is the length of the subproblem
        for (int i = 0; i <= n - len; i++) { // i is the starting index of the subproblem
            int j = i + len - 1; // j is the ending index of the subproblem
            cost[i][j] = FLT_MAX;  // Use FLT_MAX for floating point numbers
            
            // Find the minimum cost for the subproblem (i, j)
            for (int r = i; r <= j; r++) {
                float leftCost = (r > i) ? cost[i][r - 1] : 0; // Cost of left subtree
                float rightCost = (r < j) ? cost[r + 1][j] : 0; // Cost of right subtree
                float totalCost = leftCost + rightCost + freq[r]; // Total cost of the current root

                cost[i][j] = min(cost[i][j], totalCost); // Store the minimum cost
            }
        }
    }
    
    // Return the minimum cost for the whole tree (from 0 to n-1)
    return cost[0][n - 1];
}

int main() {
    // Example input
    int keys[] = {5, 15, 25, 35}; // Keys in the BST (sorted order)
    float freq[] = {0.1, 0.2, 0.3, 0.4}; // Frequency of access (probabilities)

    int n = sizeof(keys) / sizeof(keys[0]); // Number of keys
    
    // Calculate and display the minimum search cost
    float minCost = optimalBST(keys, freq, n);
    cout << "The minimum search cost of the optimal BST is: " << minCost << endl;

    return 0;
}
