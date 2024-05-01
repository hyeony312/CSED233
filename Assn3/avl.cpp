#include "avl.h"
#include "bst.h"
#include "tree.h"
#include <iostream>
#include <string>

using namespace std;

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */
void AVLTree::updateHeight(Node *curr) {
  if (curr->left != NULL) {
    updateHeight(curr->left);
  }
  if (curr->right != NULL) {
    updateHeight(curr->right);
  }
  if (curr->left == NULL && curr->right == NULL) { // leaf node
    curr->height = 0;
  } else if (curr->left != NULL && curr->right == NULL) {
    curr->height = curr->left->height + 1;
  } else if (curr->left == NULL && curr->right != NULL) {
    curr->height = curr->right->height + 1;
  } else {
    curr->height = max(curr->left->height, curr->right->height) + 1;
  }
}

void AVLTree::findPivot(Node *curr, Node **toPivot) {

  if (getBF(curr) > 1) {
    (*toPivot) = curr->left;
    (*toPivot)->parent = curr;
    (*toPivot)->LorR = 1;
  } else if (getBF(curr) < -1) {
    *toPivot = curr->right;
    (*toPivot)->parent = curr;
    (*toPivot)->LorR = 2;
  }

  if (curr->left != NULL) {
    findPivot(curr->left, toPivot);
  }
  if (curr->right != NULL) {
    findPivot(curr->right, toPivot);
  }
}

int AVLTree::getBF(Node *curr) {
  int lH, rH;
  if (curr->left == NULL) {
    lH = -1;
  } else {
    lH = curr->left->height;
  }

  if (curr->right == NULL) {
    rH = -1;
  } else {
    rH = curr->right->height;
  }
  return lH - rH;
}

void AVLTree::updateBalance(Node *curr) {
  Node *toPivot = NULL;
  findPivot(_root, &toPivot);

  if (toPivot != NULL) {
    if (toPivot->LorR == 2) {
      if (toPivot->right == NULL) {
        RLcase(toPivot);
      } else if (toPivot->left == NULL) {
        RRcase(toPivot);
      }
    } else if (toPivot->LorR == 1) {
      if (toPivot->right == NULL) {
        LLcase(toPivot);
      } else if (toPivot->left == NULL) {
        LRcase(toPivot);
      }
    }
  }
}

void AVLTree::leftRotation(Node *pivot) {
  Node *parentPivot = pivot->parent;
  Node *subPivot = pivot->right;

  Node *temp = new Node(parentPivot->key);
  if (pivot->left != NULL) {
    temp->right = pivot->left;
  }
  if (parentPivot->left != NULL) {
    temp->left = parentPivot->left;
  }
  parentPivot->key = pivot->key;
  parentPivot->left = temp;
  parentPivot->right = pivot->right;
}

void AVLTree::rightRotation(Node *pivot) {
  Node *parentPivot = pivot->parent;
  Node *subPivot = pivot->left;

  Node *temp = new Node(parentPivot->key);
  if (pivot->right != NULL) {
    temp->left = pivot->right;
  }
  if (parentPivot->right != NULL) {
    temp->right = parentPivot->right;
  }
  parentPivot->key = pivot->key;
  parentPivot->right = temp;
  parentPivot->left = pivot->left;
}

void AVLTree::LLcase(Node *pivot) { rightRotation(pivot); }
void AVLTree::LRcase(Node *pivot) {
  leftRotation(pivot->left);
  rightRotation(pivot);
}
void AVLTree::RLcase(Node *pivot) {
  rightRotation(pivot->right);
  leftRotation(pivot);
}
void AVLTree::RRcase(Node *pivot) { leftRotation(pivot); }

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

int AVLTree::insert(int key) {
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
      if (curr->left == NULL) {
        curr->left = _node;
        break;
      }
      curr = curr->left;
    } else if (curr->key < _node->key) {
      if (curr->right == NULL) {
        curr->right = _node;
        break;
      }
      curr = curr->right;
    } else {
      return -1;
      break;
    }
  }
  updateHeight(_root);
  updateBalance(_root);
  return 0;

  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int AVLTree::remove(int key) {
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

  if (curr->left == NULL && curr->right == NULL) { // degree 0
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

  updateHeight(_root);
  updateBalance(_root);

  return 0;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}
