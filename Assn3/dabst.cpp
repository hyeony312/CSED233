#include "dabst.h"
#include "bst.h"
#include "tree.h"
#include <iostream>
#include <string>

using namespace std;

string DABSTree::inOrder() {
  string output;
  _inOrder(output, _root);
  if (!output.empty())
    output.pop_back();
  return output;
}

string DABSTree::preOrder() {
  string output;
  _preOrder(output, _root);
  if (!output.empty())
    output.pop_back();
  return output;
}

void DABSTree::_inOrder(string &output, Node *cur) {
  if (cur == NULL)
    return;
  _inOrder(output, cur->left);
  output.append(cur->print_key());
  output.append("(");
  output.append(cur->print_count());
  output.append(")");
  output.append(" ");
  _inOrder(output, cur->right);
}

void DABSTree::_preOrder(string &output, Node *cur) {
  if (cur == NULL)
    return;
  output.append(cur->print_key());
  output.append("(");
  output.append(cur->print_count());
  output.append(")");
  output.append(" ");
  _preOrder(output, cur->left);
  _preOrder(output, cur->right);
}

int DABSTree::insert(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  Node *_node = new Node(key);
  Node *curr = _root;

  while (1) {
    if (_root == NULL) {
      _root = _node;
      break;
    }

    if (curr->key > _node->key) {
      _node->height++;
      if (curr->left == NULL) {
        curr->left = _node;
        break;
      }
      curr = curr->left;
    } else if (curr->key < _node->key) {
      _node->height++;
      if (curr->right == NULL) {
        curr->right = _node;
        break;
      }
      curr = curr->right;
    } else {
      curr->count++;
      break;
    }
  }

  return 0;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int DABSTree::remove(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  Node *curr = _root;
  Node *pre;
  int rl = 0;

  while (1) {
    if (_root == NULL) {
      return -1;
    }

    if (curr->key > key) {
      if (curr->left != NULL) {
        pre = curr;
        curr = curr->left;
        rl = 1;
      }
    } else if (curr->key < key) {
      if (curr->right != NULL) {
        pre = curr;
        curr = curr->right;
        rl = 2;
      }
    } else if (curr->key == key) {
      break;
    }

    if (curr->left == NULL && curr->right == NULL)
      break;
  }

  if (curr->key != key)
    return -1;

  if (curr->count > 1) {
    curr->count--;
  } else if (curr->left == NULL && curr->right == NULL) { // degree 0
    if (rl == 0)
      _root = NULL;
    else if (rl == 1)
      pre->left = NULL;
    else if (rl == 2)
      pre->right = NULL;
  } else if (curr->left != NULL && curr->right != NULL) { // degree 2
    if (rl == 0) {
      Node *temp = _root->right, *pre_temp = _root;
      while (1) {
        if (temp->left == NULL) {
          break;
        }
        pre_temp = temp;
        temp = temp->left;
      }

      _root->key = temp->key;
      _root->count = temp->count;

      if (temp->right != NULL) {
        pre_temp->left = temp->right;
      } else {
        pre_temp->left = NULL;
      }
    } else {
      Node *temp, *pre_temp;
      while (1) {
        pre_temp = temp;
        temp = temp->left;
        if (temp->left == NULL)
          break;
      }

      curr->key = temp->key;
      curr->count = temp->count;

      if (temp->right != NULL) {
        pre_temp->left = temp->right;
      }
    }
  } else if (curr->left != NULL || curr->right != NULL) { // degree 1
    if (rl == 0) {
      if (_root->left != NULL)
        _root = _root->left;
      else if (_root->right != NULL)
        _root = _root->right;
    } else if (rl == 1) {
      if (curr->left != NULL)
        pre->left = curr->left;
      else if (curr->right != NULL)
        pre->left = curr->right;
    } else if (rl == 2) {
      if (curr->left != NULL)
        pre->right = curr->left;
      else if (curr->right != NULL)
        pre->right = curr->right;
    }
  }

  return 0;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////