#include "avl.h"
#include <iostream>
#include <queue>
#include <stack>

using namespace std;
using std::stack;

void AVL::rotateLeft(Node*& node) {
    Node* tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;
    node = tmp;
    return;
}

void AVL::rotateRight(Node*& node) {
    Node* tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;
    node = tmp;
    return;
}

void AVL::rotateLeftRight(Node*& node) {
    rotateLeft(node->left);
    rotateRight(node);
    return;
}

void AVL::rotateRightLeft(Node*& node) {
    rotateRight(node->right);
    rotateLeft(node);
    return;
}

int getHeight(Node* node) {
    return node == nullptr ? -1 : node->height;
}

int computeHeight(Node* root) {

    if (root == nullptr) {

        return -1;

    }
    else {

        int hLeft = computeHeight(root->left);

        int hRight = computeHeight(root->right);

        return std::max(hLeft, hRight) + 1;

    }
}

Node* updateBalance(Node* node) {
    int balance = computeHeight(node->left) - computeHeight(node->right);

    if (balance < 0) {
        int balance = computeHeight(node->right->left) - computeHeight(node->right->right);
        if (balance > 0) {
            AVL::rotateRight(node->right);
            AVL::rotateLeft(node);
        }
        else {
            AVL::rotateLeft(node);
        }
    }
    else if (balance > 0) {
        int balance = computeHeight(node->left->left) - computeHeight(node->left->right);
        if (balance < 0) {
            AVL::rotateLeft(node->left);
            AVL::rotateRight(node);
        }
        else {
            AVL::rotateRight(node);
        }
    }
    return node;
}

void updateHeight(Node* node) {
    if (node->left != nullptr) {
        updateHeight(node->left);
    }
    node->height = computeHeight(node);
    if (node->right != nullptr) {
        updateHeight(node->right);
    }
}

Node* adjustBalance(Node* node) {
    Node* rotatedNode = new Node;
    bool updateRight = false;
    bool updateLeft = false;

    if (node != nullptr) {
        node->left = adjustBalance(node->left);
        node-> right = adjustBalance(node->right);

        int balance = computeHeight(node->left) - computeHeight(node->right);
        if (balance < -1) {
            node = updateBalance(node);
        }
        else if (balance > 1) {
            node = updateBalance(node);
        }
    }
    return node;
}

void printBT(const string& prefix, const Node* node, bool isLeft)
{
    if (node != nullptr)
    {
        cout << prefix;

        cout << (isLeft ? "├──" : "└──");
        
        int balance = computeHeight(node->left) - computeHeight(node->right);
        // print the value of the node
        cout << " " << node->val << "," << node->height << "," << balance << endl;

        // enter the next tree level - left and right branch
        printBT(prefix + (isLeft ? "│   " : "    "), node->left, true);
        printBT(prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}

void printBT(const Node* node)
{
    printBT("", node, false);
}

void AVL::insert(const int& v) {
    Node* node = new Node(v);
    bool inserted = false;
    bool needsRotate = false;

    if (root == nullptr) {
        root = node;
    }
    else {
        Node* tmpNode = new Node();
        tmpNode = root;
        while (!inserted) {
            while (node->val > tmpNode->val) {
                if (tmpNode->right == nullptr) {
                    tmpNode->right = node;
                    inserted = true;
                }
                else {
                    tmpNode = tmpNode->right;
                }
            }
            while (node->val < tmpNode->val) {
                if (tmpNode->left == nullptr) {
                    tmpNode->left = node;
                    inserted = true;
                }
                else {
                    tmpNode = tmpNode->left;
                }
            }
        }
    }

    updateHeight(root);

    int balance = computeHeight(root->left) - computeHeight(root->right);
    if (balance > 1 || (balance < -1)) {
        root = updateBalance(root);
    }

    root = adjustBalance(root);

    updateHeight(root);
    printBT(root);
}
