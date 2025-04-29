#include <iostream>
using namespace std;

// Define structure for a BST Node
struct Node {
    int data;
    Node* left;
    Node* right;

    // Constructor to initialize a new node
    Node(int value) {
        data = value;
        left = right = nullptr;
    }
};

// Function to insert a node in BST
Node* insert(Node* root, int value) {
    if (!root) return new Node(value); // If tree is empty, create root

    // Recursively insert into left or right subtree
    if (value < root->data)
        root->left = insert(root->left, value);
    else
        root->right = insert(root->right, value);

    return root;
}

// Function to find number of nodes in longest path (height of BST)
int longestPath(Node* root) {
    if (!root) return 0;

    int left = longestPath(root->left);
    int right = longestPath(root->right);

    // Return the larger path + 1 (for current node)
    return max(left, right) + 1;
}

// Function to find the minimum value in BST
int findMin(Node* root) {
    if (!root) {
        cout << "Tree is empty.\n";
        return -1;
    }

    // Keep moving left to find the smallest value
    while (root->left)
        root = root->left;

    return root->data;
}

// Function to mirror (swap left and right) the BST
void mirror(Node* root) {
    if (!root) return;

    // Swap left and right children
    swap(root->left, root->right);

    // Recursively mirror left and right subtrees
    mirror(root->left);
    mirror(root->right);
}

// Function to search for a value in BST
bool search(Node* root, int key) {
    if (!root) return false;

    if (root->data == key) return true;

    // Search left or right based on comparison
    if (key < root->data)
        return search(root->left, key);
    else
        return search(root->right, key);
}

// In-order traversal: Left, Root, Right
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

// Main function with user interaction
int main() {
    Node* root = nullptr;
    int n, val;

    // Get number of initial elements and insert into BST
    cout << "Enter number of initial values: ";
    cin >> n;
    cout << "Enter values to insert in BST: ";
    for (int i = 0; i < n; i++) {
        cin >> val;
        root = insert(root, val);
    }

    int choice;
    // Menu-driven interface
    do {
        cout << "\n---- MENU ----\n";
        cout << "1. Insert new node\n";
        cout << "2. Find longest path (height)\n";
        cout << "3. Find minimum value\n";
        cout << "4. Mirror the tree\n";
        cout << "5. Search a value\n";
        cout << "6. Display Inorder traversal\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                // Insert new node
                cout << "Enter value to insert: ";
                cin >> val;
                root = insert(root, val);
                break;

            case 2:
                // Display height of BST
                cout << "Longest path length: " << longestPath(root) << "\n";
                break;

            case 3:
                // Find and display minimum value
                cout << "Minimum value: " << findMin(root) << "\n";
                break;

            case 4:
                // Mirror the BST
                mirror(root);
                cout << "Tree mirrored.\n";
                break;

            case 5:
                // Search a value
                cout << "Enter value to search: ";
                cin >> val;
                cout << (search(root, val) ? "Found\n" : "Not Found\n");
                break;

            case 6:
                // Display BST in-order
                cout << "Inorder traversal: ";
                inorder(root);
                cout << "\n";
                break;

            case 7:
                // Exit program
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 7);

    return 0;
}
