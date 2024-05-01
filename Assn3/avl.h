#pragma once
#include "bst.h"

using namespace std;

class AVLTree : public BinarySearchTree {
public:
  AVLTree(){};
  ~AVLTree(){};

  int insert(int key);
  int remove(int key);

private:
  /////////////////////////////////////////////////////////
  //////  TODO: Add private members if required ///////////
Node* pivotNode;
void findPivot(Node *curr, Node** toPivot);
void updateHeight(Node *curr);
  void updateBalance(Node *curr);
  int getBF(Node *curr);

  void leftRotation(Node* pivot);
  void rightRotation(Node* pivot);

  void LLcase(Node* pivot);
  void LRcase(Node* pivot);
  void RLcase(Node* pivot);
  void RRcase(Node* pivot);

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
};