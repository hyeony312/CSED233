/*
    Programming Assignment #3

*/
#include <fstream>
#include <iostream>
#include <string>
#include <math.h>

#include "tree.h"
#include "utils.h"
#include "sort.h"
#include "dabst.h"
#include "avl.h"
#include "b_tree.h"
#include "mst.h"

using namespace std;



/*
    [Task 1] insertion sort

    Description:
        Implement a function that sorts a given array using the insertion sort algorithm in ascending order.
        You can modify sort.cpp and sort.h files for this problem.

        TODO: Implement sortAlg::insertionSort function

    Input:
        ('insert',integer): insert integer into the array
        ('insertionSort',NULL): sort the array using insertion sort algorithm

    Output:
        Every value in the array for each sorting step including the initial step,
        string separated with the white space (please use built-in function to print the array).
        You don’t need to consider exceptional cases such as overflow or an empty array.
        We will not test such cases.

*/

void task_1(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 1]" << endl;
    try {
        sortAlg sort;
        for (int i = 0; i < instr_seq.getLength(); i++) {
            string command = instr_seq.getInstruction(i).getCommand();
            if (command.compare("insert") == 0) {
                sort.arr[sort.arr_size] = instr_seq.getInstruction(i).getValue();
                sort.arr_size++;
            } else if (command.compare("insertionSort") == 0) {
                sort.printArray(fout);
                sort.insertionSort(fout);
            } else {
                cerr << "Invalid command" << endl;
                exit(-1);
            }
        }
    } catch (const char *e) {
        cerr << e << endl;
    }
}

/*
    [Task 2] merge sort

    Description:
        Implement a function that shows process of recursive merge sort algorithms and counts the number of ‘drop’ operations.
        It will sort a given array in ascending order.
        You can modify sort.cpp and sort.h files for this problem.

        TODO: Implement sortAlg::mergeSort function
        TODO: Implement sortAlg::merge function

    Input:
        ('insert',integer): insert integer into the array
        ('mergeSort',NULL): sort the array using the merge sort algorithm, and count ‘drop’ operations. 

    Output:
        Every value in the array for each sorting step including the initial step, string separated with the white space (please use built-in function to print the array).
        The number of ‘drop’ operations.
*/

void task_2(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 2]" << endl;
    try {
        int count = 0;
        sortAlg sort;
        for (int i = 0; i < instr_seq.getLength(); i++) {
            string command = instr_seq.getInstruction(i).getCommand();
            if (command.compare("insert") == 0) {
                sort.arr[sort.arr_size] = instr_seq.getInstruction(i).getValue();
                sort.arr_size++;
            } else if (command.compare("mergeSort") == 0) {
                sort.printArray(fout);
                sort.mergeSort(fout, 0, sort.arr_size - 1, count);
            } else {
                cerr << "Invalid command" << endl;
                exit(-1);
            }
        }
        fout << count << endl;
    } catch (const char *e) {
        cerr << e << endl;
    }
}

/*
    [Task 3] Duplication-Aware BST Insertion / Deletion 

    Description:
        Implement functions that inserts and deletes an element into a duplication-aware binary search tree.
        You can modify dabst.cpp and dabst.h files for this problem.

        TODO: Implementation DABSTree::insert function
        TODO: Implementation DABSTree::remove function

    Input of DABSTree::insert
        Key of the element to be inserted.

    Input of DABSTree::remove
        Key of the element to be deleted.

    Output of DABSTree::remove
        Print -1 if the key does not exist in the tree, and do not delete any element

    task_3 prints
        The results of preorder and inorder traversal of the current constructed tree when each operation performed successfully.
        -1, when DABSTree::remove is called and the key does not exist in the tree.
*/

void task_3(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 3]" << endl;
    try {
        DABSTree tree;
        int ret;
        for (int i = 0; i < instr_seq.getLength(); i++) {
            string command = instr_seq.getInstruction(i).getCommand();
            int key = instr_seq.getInstruction(i).getValue();
            if (command.compare("insert") == 0) {
                tree.insert(key);
                fout << tree.preOrder() << endl;
                fout << tree.inOrder() << endl;
            } else if (command.compare("remove") == 0) {
                ret = tree.remove(key);
                if (ret == -1) 
                    fout << ret << endl;
                else {
                    fout << tree.preOrder() << endl;
                    fout << tree.inOrder() << endl;
                }
            } else {
                cerr << "Invalid command" << endl;
                exit(-1);
            }
        }
    } catch (const char *e) {
        cerr << e << endl;
    }
}

/*
    [Task 4] AVL tree Insert / Remove

    Description:
        Implement a function that inserts and removes an element at an AVL tree.
        The insert and remove might cause the AVL tree to violate its properties (imbalance). 
        Your code should be able to resolve the various imbalance type (LL, LR, RL, RR) of the AVL tree. 
        You can modify avl.cpp and avl.h files for this problem. 

        TODO: Implementation AVLTree::insert function
        TODO: Implementation AVLTree::remove function

        Hint : suggest you to call 'insert' and 'remove' function in BinarySearchTree class 

    Input of AVLTree::insert
        Key of the element to insert

    Output of AVLTree::insert
        Return -1 if the key already exists in the tree, 0 otherwise.
        (If the key already exists, do not insert the element)

    Input of AVLTree::remove
        Key of the element to remove

    Output of AVLTree::remove
        Return -1 if the key does not exist in the tree, 0 otherwise.
        (If the key does not exist, do not remove any element)

    task_4 prints
        -1 if the key does/doesn't exist for insert/remove.
        the preorder and inorder traversal of the constructed tree after *each* insertion/deletion.
*/

void task_4(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 4]" << endl;
    try {
        AVLTree tree;
        int ret;
    for (int i = 0; i < instr_seq.getLength(); i++) {
        string command = instr_seq.getInstruction(i).getCommand();
            int key = instr_seq.getInstruction(i).getValue();
            if (command.compare("insert") == 0) {
                ret = tree.insert(key);
                if (ret == -1){
                    fout << ret << endl;
                }
                else {
                    fout << tree.preOrder() << endl;
                    fout << tree.inOrder() << endl;
                }
            } else if (command.compare("remove") == 0) {
                ret = tree.remove(key);
                if (ret == -1) {
                    fout << ret << endl;
                }
                else {
                    fout << tree.preOrder() << endl;
                    fout << tree.inOrder() << endl;
                }
            } else {
                cerr << "Invalid command" << endl;
                exit(-1);
            }
        }
    } catch (const char *e) {
        cerr << e << endl;
    }
}

/*
    [Task 5] Multi-way Search Tree (MST)

    Description:
      Let’s consider multi-way search tree (MST). When inserting
      or deleting a key, the property of multi-way search tree
      should be always satisfied: (1) Every key in a node is
      ordered increasingly, (2) Every key is greater than all keys
      stored in its left subtree & less than all keys in its right subtree.

      TODO: Implementation MultiWaySearchTree::insert function
      TODO: Implementation MultiWaySearchTree::remove function


    Input of MultiWaySearchTree::insert
        Key of the element to be inserted.

    Output of MultiWaySearchTree::insert
        Return the -1 if the key already exists in the tree.
        (If the key already exists, do not insert the element)

    Input of MultiWaySearchTree::remove
        Key of the element to be deleted.

    Output of MultiWaySearchTree::remove
        Return the -1 if the key does not exist in the tree.
        (If the key does not exist, do not delete any element)

    task_3 prints
        the return for *each* insertion/deletion and
        the results of preorder and inorder traversal of the constructed tree.
*/

void task_5(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 5]" << endl;
    try {
        MultiWaySearchTree tree;
        int ret;
        for (int i = 0; i < instr_seq.getLength(); i++) {
            string command = instr_seq.getInstruction(i).getCommand();
            int key = instr_seq.getInstruction(i).getValue();
            if (command.compare("insert") == 0) {
                ret = tree.insert(key);
                if (ret == -1) {
                  fout << ret << endl;
                } else{
                  fout << tree.preOrder() << endl;
                }
            } else if (command.compare("remove") == 0) {
                ret = tree.remove(key);
                if (ret == -1) {
                  fout << ret << endl;
                } else{
                  fout << tree.preOrder() << endl;
                }
            } else {
                cerr << "Invalid command" << endl;
                exit(-1);
            }
        }
    } catch (const char *e) {
        cerr << e << endl;
    }
}

/*
    [Task 6] B-tree Insertion / Deletion

    Description:
                
        Given a B-tree, implement a function that inserts or deletes an element. 
        This function inserts a key if there is no same key value in the B-tree. 
        If the key already exists in the B-tree, you need to delete an element having that key.  
        Your B-tree should maintain the B-tree property even after the insertion or deletion. 
        After finishing every insertion/deletion process, print the constructed B-tree through postorder traversal method. 
        If there is no element in the B-tree, print -1. You can modify B_tree.cpp and B_tree.h files for this problem. 

        TODO: Implementation BTree class which has has_elem, insert_elem, delete_elem


    Input: Commands (The order 'M', and multiple 'key's) 
            - ('M', integer): specify the order of a B-tree. 
            - ('key', positive integer): a key to be inserted or deleted. 

    Output
      - The results of postorder traversal of the constructed B-tree.
*/

void task_6(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 6]" << endl;
    try {
        int M;
        int idx = instr_seq.getLength();

        BTree *bt;

        if (instr_seq.getInstruction(0).getCommand().compare("M") != 0 ||
            instr_seq.getInstruction(1).getCommand().compare("key") != 0) {
            cerr << "Invalid command" << endl;
            exit(-1);
        }

        M = instr_seq.getInstruction(0).getValue();
        bt = new BTree(M);

        for(int i=1; i<idx; i++){

            int key = instr_seq.getInstruction(i).getValue();
            if(bt->has_elem(key)==1){
                bt->insert_elem(key);
            }
            else{
                bt->delete_elem(key);
            }
        }

        fout << bt->postOrder() << endl;

        delete bt;
    } catch (const char *e) {
        cerr << e << endl;
    }
}



int main(int argc, char **argv) {
    string filename = "submit.txt";
    int task_num = 0;
    InstructionSequence instr_seq;

    // Open file
    ofstream fout;
    fout.open(filename, fstream::app);
    if (!fout.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        return -1;
    }

    // Choosing task number. Default is running ALL tasks (0)
    if (argc >= 2)
        task_num = atoi(argv[1]);
    if (argc >= 3) {
        try {
            instr_seq.parseInstructions(argv[2]);
        }
        catch (const char *e) {
            cerr << e << endl;
            return -1;
        }
    }

    // Running the task(s)
    switch (task_num) {
        case 1:
            task_1(fout, instr_seq);
            break;
        case 2:
            task_2(fout, instr_seq);
            break;
        case 3:
            task_3(fout, instr_seq);
            break;
        case 4:
            task_4(fout, instr_seq);
            break;
        case 5:
            task_5(fout, instr_seq);
            break;
        case 6:
            task_6(fout, instr_seq);
            break;
        case 0:
            instr_seq.parseInstructions(TASK_1_DEFAULT_ARGUMENT);
            task_1(fout, instr_seq);

            instr_seq.parseInstructions(TASK_2_DEFAULT_ARGUMENT);
            task_2(fout, instr_seq);

            instr_seq.parseInstructions(TASK_3_DEFAULT_ARGUMENT);
            task_3(fout, instr_seq);

            instr_seq.parseInstructions(TASK_4_DEFAULT_ARGUMENT);
            task_4(fout, instr_seq);

            instr_seq.parseInstructions(TASK_5_DEFAULT_ARGUMENT);
            task_5(fout, instr_seq);

            instr_seq.parseInstructions(TASK_6_DEFAULT_ARGUMENT);
            task_6(fout, instr_seq);

            break;
        default:
            cout << "Wrong task number" << endl;
    }

    fout.close();
    return 0;
}
