#pragma once
#include <string>

using namespace std;

class Node {
public:
    Node(int key) : key(key), height(0), count(1), left(NULL), right(NULL) {}
    int key;
    int height;
    int count;
    Node *left;
    Node *right;
Node* parent;
int LorR=0;
    /* Add public members if required*/

    string print_key() { return to_string(key); };
    string print_count() { return to_string(count); };
};

class BinaryTree {
public:
    BinaryTree() { _root = NULL; };
    ~BinaryTree() {
        delete[] _root;
        _root = NULL;
    };
    string preOrder();
    string inOrder();

protected:
    Node *_root;

private:
    void _inOrder(string& output, Node *cur);
    void _preOrder(string& output, Node *cur);
};
