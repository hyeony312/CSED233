#include "tree.h"
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

/* This is given function. DO NOT MODIFY THIS FUNCTION */
int findIndex(const char *str, int start, int end) {
  if (start > end)
    return -1;

  string s;

  for (int i = start; i <= end; i++) {

    // if open parenthesis, push it
    if (str[i] == '(')
      s.push_back(str[i]);

    // if close parenthesis
    else if (str[i] == ')') {
      if (s.back() == '(') {
        s.pop_back();

        if (!s.length())
          return i;
      }
    }
  }
  // if not found return -1
  return -1;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
Node *BinaryTree::_buildFromString(const char *data, int start, int end) {
  if (start > end)
    return NULL;

  Node *root = new Node(data[start]);
  int index = -1;

  if (start + 1 <= end && data[start + 1] == '(')
    index = findIndex(data, start + 1, end);

  if (index != -1) {
    root->left = _buildFromString(data, start + 2, index - 1);
    root->right = _buildFromString(data, index + 2, end - 1);
  }
  return root;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
void BinaryTree::buildFromString(const char *data) {
  Node *root = _buildFromString(data, 0, strlen(data) - 1);
  _root = root;
}

string BinaryTree::preOrder(int node_value) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  if (tar_root == NULL)
    find_node(node_value, _root);
  if (tar_root == NULL)
    return "error";

  string output;

  preTraversal(&output);

  return output;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string BinaryTree::postOrder(int node_value) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  if (tar_root == NULL)
    find_node(node_value, _root);
  if (tar_root == NULL)
    return "error";

  string output;

  postTraversal(&output);

  return output;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string BinaryTree::inOrder(int node_value) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  if (tar_root == NULL)
    find_node(node_value, _root);
  if (tar_root == NULL)
    return "error";

  string output;

  inTraversal(&output);

  return output;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

int BinaryTree::getDepth(int node_value) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  int level = 0;

  find_depth(node_value, level, _root);

  return fin_depth;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

bool BinaryTree::isReverseComplete() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  // step1. Find height of tree
  find_depth(-1, 0, _root);
  // step2. Make sure the node is full up to the n-1th level
  int *level = new int[height]{0};

  RCtraversal(level, 0, _root);
  for (int i = 0; i < height; i++) {
    int node_num = 1;
    for (int j = 0; j < i; j++)
      node_num *= 2;
    if (level[i] != node_num)
      return false;
  }

  int num_last = 1; // Num of last level nodes
  for (int i = 0; i < height; i++)
    num_last *= 2;
  int*last_level = new int[num_last] {0};
  find_child(last_level, height-1, 0, _root);
  
  // step3. Is the last level of the tree filled in order from the right?
  int i;
  for(i=0;i<num_last;i++){
    if(last_level[i]==0) break;
  }
  for(int j=i+1;j<num_last;j++){
    if(last_level[j]==1) return false;
  }

  return true;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
  return false;
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional private functions  */
void BinaryTree::find_node(int node_value, Node *temp) {

  if (temp->value - '0' == node_value) {
    tar_root = temp;
  }

  if (temp->left != NULL) {
    find_node(node_value, temp->left);
  }
  if (temp->right != NULL) {
    find_node(node_value, temp->right);
  }
  return;
}

void BinaryTree::preTraversal(string *output) {
  Node *temp = tar_root;

  if (*output == "") {
    *output = tar_root->value;
  } else {
    *output = *output + " " + tar_root->value;
  }

  Node *left_child = tar_root->left;
  Node *right_child = tar_root->right;

  if (tar_root->left != NULL) {
    tar_root = left_child;
    preTraversal(output);
    tar_root = temp;
  }
  if (tar_root->right != NULL) {
    tar_root = right_child;
    preTraversal(output);
    tar_root = temp;
  }
}

void BinaryTree::postTraversal(string *output) {
  Node *temp = tar_root;

  Node *left_child = tar_root->left;
  Node *right_child = tar_root->right;

  if (tar_root->left != NULL) {
    tar_root = left_child;
    postTraversal(output);
    tar_root = temp;
  }

  if (tar_root->right != NULL) {
    tar_root = right_child;
    postTraversal(output);
    tar_root = temp;
  }

  if (*output == "") {
    *output = tar_root->value;
  } else {
    *output = *output + " " + tar_root->value;
  }
}

void BinaryTree::inTraversal(string *output) {
  Node *temp = tar_root;

  Node *left_child = tar_root->left;
  Node *right_child = tar_root->right;

  if (tar_root->left != NULL) {
    tar_root = left_child;
    inTraversal(output);
    tar_root = temp;
  }

  if (*output == "") {
    *output = tar_root->value;
  } else {
    *output = *output + " " + tar_root->value;
  }

  if (tar_root->right != NULL) {
    tar_root = right_child;
    inTraversal(output);
    tar_root = temp;
  }
}

void BinaryTree::find_depth(int node_value, int depth, Node *temp) {

  if (temp->value - '0' == node_value) {
    fin_depth = depth;
  }
  if (depth > height)
    height = depth; // Update height

  if (temp->left != NULL) {
    find_depth(node_value, depth + 1, temp->left);
  }
  if (temp->right != NULL) {
    find_depth(node_value, depth + 1, temp->right);
  }
}

void BinaryTree::RCtraversal(int *level, int depth, Node *temp) {
  if (depth < height)
    level[depth]++;
  if (temp->left != NULL) {
    RCtraversal(level, depth + 1, temp->left);
  }
  if (temp->right != NULL) {
    RCtraversal(level, depth + 1, temp->right);
  }
}

void BinaryTree::find_child(int*last_node, int tar_depth, int depth, Node *temp) {
  if (depth == tar_depth) {
    if(temp->right!=NULL) last_node[num*2] = 1; 
    if(temp->left!=NULL) last_node[(num*2)+1] = 1; 
    num++;
  }

  if (temp->right != NULL) {
    find_child(last_node, tar_depth, depth + 1, temp->right);
  }
  if (temp->left != NULL) {
    find_child(last_node, tar_depth, depth + 1, temp->left);
  }
}
///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
