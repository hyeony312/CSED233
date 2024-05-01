#include "mst.h"
#include <iostream>
#include <string>

using namespace std;

string MultiWayTree::preOrder() {
  string output;
  _preOrder(output, _root);
  if (!output.empty())
    output.pop_back();
  return output;
}

void MultiWayTree::_preOrder(string &output, MultiNode *cur) {
  if (cur == NULL)
    return;

  output.append(cur->print_key());
  output.append(" ");
  _preOrder(output, cur->left);
  _preOrder(output, cur->middle);
  _preOrder(output, cur->right);
}

int MultiWaySearchTree::insert(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  if (_root == NULL) {
    MultiNode *node = new MultiNode;
    _root = node;
  }
  MultiNode *curr = _root;

  while (1) {
    if (curr->key1 == key || curr->key2 == key) {
      return -1;
    }

    if (curr->key1 == 0) { // No key
      curr->key1 = key;
      break;
    } else if (curr->key2 == 0) { // One key
      if (curr->key1 > key) {
        curr->key2 = curr->key1;
        curr->key1 = key;
        break;
      } else {
        curr->key2 = key;
        break;
      }
    } else { // Two keys
      if (key < curr->key1) {
        if (curr->left == NULL) {
          MultiNode *node = new MultiNode;
          curr->left = node;
        }
        curr = curr->left;
      } else if (key < curr->key2) {
        if (curr->middle == NULL) {
          MultiNode *node = new MultiNode;
          curr->middle = node;
        }
        curr = curr->middle;
      } else {
        if (curr->right == NULL) {
          MultiNode *node = new MultiNode;
          curr->right = node;
        }
        curr = curr->right;
      }
    }
  }

  return 0;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int MultiWaySearchTree::remove(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  if (_root == NULL) {
    return -1;
  }

  MultiNode *curr = _root;
  MultiNode *parent = NULL;

  while (1) {
    // find node
    if (curr->key1 == key) {
      deleteNode(curr, parent, key);
      clearEmpty(_root);
      break;
    } else if (curr->key2 == key) {
      deleteNode(curr, parent, key);
      clearEmpty(_root);
      break;
    }

    // search next node
    if (curr == NULL) { // No key
      return -1;
    } else if (curr->key2 == 0) { // One key
      if (curr->key1 > key) {
        curr = curr->left;
        parent = curr;
      } else {
        curr = curr->middle;
        parent = curr;
      }
    } else { // Two keys
      if (key < curr->key1) {
        curr = curr->left;
        parent = curr;
      } else if (key < curr->key2) {
        curr = curr->middle;
        parent = curr;
      } else {
        curr = curr->right;
        parent = curr;
      }
    }
  }

  return 0;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */
void MultiWaySearchTree::clearEmpty(MultiNode *curr) {
  if (curr->left == NULL && curr->middle == NULL && curr->right == NULL) {
    return;
  }

  if (curr->left != NULL && curr->left->key1 == 0) {
    curr->left = NULL;
  }
  if (curr->middle != NULL && curr->middle->key1 == 0) {
    curr->middle = NULL;
  }
  if (curr->right != NULL && curr->right->key1 == 0) {
    curr->right = NULL;
  }

  if (curr->left != NULL) {
    clearEmpty(curr->left);
  }
  if (curr->middle != NULL) {
    clearEmpty(curr->middle);
  }
  if (curr->right != NULL) {
    clearEmpty(curr->right);
  }
}

void MultiWaySearchTree::deleteNode(MultiNode *curr, MultiNode *parent,
                                    int key) {
  if (parent == NULL)
    parent = _root;

  if (curr->key1 == key) {
    if (curr->middle != NULL) { // if has right subtree
      curr = curr->middle;
      while (1) { // find min
        if (curr->left != NULL) {
          curr = curr->left;
        } else {
          parent->key1 = curr->key1;
          if (curr->key2 > 0) {
            curr->key1 = curr->key2;
            curr->key2 = 0;
            if (curr->middle != NULL) {
              curr->left = curr->middle;
              curr->middle = NULL;
            }
            if (curr->right != NULL) {
              curr->middle = curr->right;
              curr->right = NULL;
            }
          } else {
            curr->key1 = 0;
            clearEmpty(_root);
          }
          clearEmpty(_root);
          break;
        }
      }
    } else if (curr->left != NULL) { // if has only left subtree
      curr = curr->left;
      while (1) { // find max
        if (curr->right != NULL) {
          curr = curr->right;
        } else {
          parent->key1 = curr->key2;
          curr->key2 = 0;
          break;
        }
      }
    } else { // has no child
      if (curr->key2 > 0) {
        curr->key1 = curr->key2;
        curr->key2 = 0;
      } else {
        curr->key1 = 0;
      }
    }
  } else if (curr->key2 == key) {
    if (curr->right != NULL) { // if has right subtree
      curr = curr->right;
      while (1) { // find min
        if (curr->left != NULL) {
          curr = curr->left;
        } else {
          parent->key2 = curr->key1;
          if (curr->key2 > 0) {
            curr->key1 = curr->key2;
            curr->key2 = 0;
            if (curr->middle != NULL) {
              curr->left = curr->middle;
              curr->middle = NULL;
            }
            if (curr->right != NULL) {
              curr->middle = curr->right;
              curr->right = NULL;
            }
          } else {
            curr->key1 = 0;
            clearEmpty(_root);
          }
          break;
        }
      }
    } else if (curr->middle != NULL) { // if has only left subtree
      curr = curr->middle;
      while (1) { // find max
        if (curr->right != NULL) {
          curr = curr->right;
        } else {
          parent->key2 = curr->key2;
          curr->key2 = 0;
          break;
        }
      }
    } else { // has no child
      if (curr->key2 > 0) {
        curr->key1 = curr->key2;
        curr->key2 = 0;
      } else {
        curr->key1 = 0;
      }
    }
  }
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
