#pragma once
#include <string>

using namespace std;

struct Node {
  Node(char input_value) : value(input_value), left(NULL), right(NULL) {}
  char value;
  Node *left;
  Node *right;
};

class BinaryTree {
public:
  BinaryTree() { _root = NULL; };
  ~BinaryTree() {
    delete[] _root;
    _root = NULL;
  };
  void buildFromString(const char *data);

  string preOrder(int node_value);
  string postOrder(int node_value);
  string inOrder(int node_value);
  int getDepth(int node_value);
  bool isReverseComplete();

private:
  Node *_root;
  Node *_buildFromString(const char *data, int start, int end);
  /////////////////////////////////////////////////////////
  //////  TODO: Add Private members if required ///////////
  Node *tar_root = NULL;
  int fin_depth = -1;
  int height = 0;
  int num=0;

  void find_node(int node_value, Node *temp);
  void preTraversal(string *output);
  void postTraversal(string *output);
  void inTraversal(string *output);
  void find_depth(int node_vlaue, int depth, Node *temp);
  void RCtraversal(int *level, int depth, Node *temp);
  void find_child(int*last_node, int tar_depth, int depth,
                   Node *temp);
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
};
