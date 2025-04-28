
#include <iostream>
#include <string>
using namespace std;

// Node structure for AVL Tree
struct Node {
    string keyword;
    string meaning;
    Node* left;
    Node* right;
    int height;
    
    Node(string k, string m) : keyword(k), meaning(m), left(nullptr), right(nullptr), height(1) {}
};

// Utility functions
int height(Node* node) {
    return node ? node->height : 0;
}

int getBalance(Node* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    
    x->right = y;
    y->left = T2;
    
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    
    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    
    y->left = x;
    x->right = T2;
    
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    
    return y;
}

// Insert a keyword and meaning
Node* insert(Node* node, string keyword, string meaning) {
    if (!node)
        return new Node(keyword, meaning);
    
    if (keyword < node->keyword)
        node->left = insert(node->left, keyword, meaning);
    else if (keyword > node->keyword)
        node->right = insert(node->right, keyword, meaning);
    else {
        cout << "Keyword already exists. Updating meaning.\n";
        node->meaning = meaning;
        return node;
    }
    
    node->height = 1 + max(height(node->left), height(node->right));
    
    int balance = getBalance(node);
    
    // Left Left
    if (balance > 1 && keyword < node->left->keyword)
        return rightRotate(node);
    
    // Right Right
    if (balance < -1 && keyword > node->right->keyword)
        return leftRotate(node);
    
    // Left Right
    if (balance > 1 && keyword > node->left->keyword) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    
    // Right Left
    if (balance < -1 && keyword < node->right->keyword) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    
    return node;
}

// Find minimum value node
Node* minValueNode(Node* node) {
    Node* current = node;
    
    while (current->left)
        current = current->left;
    return current;
}

// Delete a keyword
Node* deleteNode(Node* root, string keyword) {
    if (!root)
        return root;
    
    if (keyword < root->keyword)
        root->left = deleteNode(root->left, keyword);
    else if (keyword > root->keyword)
        root->right = deleteNode(root->right, keyword);
    else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            
            if (!temp) {
                temp = root;
                root = nullptr;
            }
            else
                *root = *temp;
            
            delete temp;
        }
        else {
            Node* temp = minValueNode(root->right);
            root->keyword = temp->keyword;
            root->meaning = temp->meaning;
            root->right = deleteNode(root->right, temp->keyword);
        }
    }
    
    if (!root)
        return root;
    
    root->height = 1 + max(height(root->left), height(root->right));
    
    int balance = getBalance(root);
    
    // Left Left
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    
    // Left Right
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    
    // Right Right
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    
    // Right Left
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    
    return root;
}

// Search a keyword
Node* search(Node* root, string keyword) {
    if (!root || root->keyword == keyword)
        return root;
    
    if (keyword < root->keyword)
        return search(root->left, keyword);
    else
        return search(root->right, keyword);
}

// Inorder Traversal (sorted order)
void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        cout << root->keyword << " : " << root->meaning << endl;
        inorder(root->right);
    }
}

// Main Program
int main() {
    Node* root = nullptr;
    int choice;
    string keyword, meaning;
    
    do {
        cout << "\n--- Dictionary Management ---\n";
        cout << "1. Add/Update Keyword\n";
        cout << "2. Delete Keyword\n";
        cout << "3. Search Keyword\n";
        cout << "4. Display Dictionary (Sorted Order)\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        
        switch(choice) {
            case 1:
                cout << "Enter keyword: ";
                getline(cin, keyword);
                cout << "Enter meaning: ";
                getline(cin, meaning);
                root = insert(root, keyword, meaning);
                break;
            case 2:
                cout << "Enter keyword to delete: ";
                getline(cin, keyword);
                root = deleteNode(root, keyword);
                break;
            case 3:
                cout << "Enter keyword to search: ";
                getline(cin, keyword);
                {
                    Node* found = search(root, keyword);
                    if (found)
                        cout << "Meaning: " << found->meaning << endl;
                    else
                        cout << "Keyword not found!\n";
                }
                break;
            case 4:
                cout << "Dictionary Contents (Sorted):\n";
                inorder(root);
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 5);
    
    return 0;
}
