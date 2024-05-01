#pragma once
#include <string>

using namespace std;

class BTree {
public:
  /////////////////////////////////////////////////////////
  //////  TODO: Implement BTree class, Add public members if required
  //////////////
  /* class Node {
  public:
    int *key;
    Node **children;
    Node *parent;
  };

  Node *_root;
  int degree;

  Node *makeNode(int key);
  void splitNode(Node *currentNode, Node *parentNode); */
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
  BTree(int M){/* degree = M; */};
  int has_elem(int key);
  int insert_elem(int key);
  int delete_elem(int key);
  string postOrder();

private:
  /////////////////////////////////////////////////////////
  //////  TODO: Add private members if required ///////////

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
};
