#pragma once
#include "tree.h"
#include "bst.h"

using namespace std;
class DABSTree : public BinarySearchTree {
public:
    DABSTree() { };
    ~DABSTree() { };

    string inOrder();
    string preOrder();
    void _inOrder(string& output, Node *cur);
    void _preOrder(string& output, Node *cur);
    int insert(int key);
    int remove(int key);


private:
    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};