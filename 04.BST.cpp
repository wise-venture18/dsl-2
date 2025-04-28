#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = right = nullptr;
    }
};

class BST {
public:
    Node* insert(Node* root, int key) {
        if (root == nullptr) {
            return new Node(key);
        }
        if (key < root->data) {
            root->left = insert(root->left, key);
        } else {
            root->right = insert(root->right, key);
        }
        return root;
    }

    int findMin(Node* root) {
        while (root->left != nullptr) {
            root = root->left;
        }
        return root->data;
    }

    int longestPath(Node* root) {
        if (root == nullptr) {
            return 0;
        }
        int leftDepth = longestPath(root->left);
        int rightDepth = longestPath(root->right);
        return max(leftDepth, rightDepth) + 1;
    }

    void swapChildren(Node* root) {
        if (root) {
            swap(root->left, root->right);
            swapChildren(root->left);
            swapChildren(root->right);
        }
    }

    bool search(Node* root, int key) {
        if (root == nullptr)
            return false;
        if (root->data == key)
            return true;
        if (key < root->data)
            return search(root->left, key);
        return search(root->right, key);
    }
};

int main() {
    BST tree;
    Node* root = nullptr;
    int n, value;

    cout << "Enter number of nodes to insert: ";
    cin >> n;

    cout << "Enter " << n << " values:\n";
    for (int i = 0; i < n; ++i) {
        cin >> value;
        root = tree.insert(root, value);
    }

    cout << "\nMinimum value: " << tree.findMin(root) << endl;
    cout << "Longest path length: " << tree.longestPath(root) << endl;

    tree.swapChildren(root);
    cout << "Left and right children swapped.\n";

    cout << "Enter value to search: ";
    cin >> value;
    if (tree.search(root, value))
        cout << value << " found in the tree.\n";
    else
        cout << value << " not found in the tree.\n";
    
    return 0;
}
