/*
    Programming Assignment #4
*/
#include <fstream>
#include <iostream>
#include <cmath>
#include <string>
#include "hash_function.h"
#include "hash_table.h"
#include "graph.h"
#include "utils.h"

using namespace std;


/*
    [Task 1] Bucket hashing

    Description:
        Implement a closed hash table with bucket hashing.
        This hash table is used with n-bit integer keys, and hashing into a bucket table of size 2^r, and the size of each bucket is k.
        So the total capacity of a hash table will be k⋅2^r.
        Also, the hash table contains an overflow bucket, of which size is limited to 2^r, to store overflowed elements sequentially.
        We use the binary mid-square hash function, and as a key is n bits, your code should treat the square of the key as 2n bits.
        You can assume that r  is an even number, and keys are positive integers.
        Note that you cannot insert a new key into a deleted slot.
        And you don’t need to consider an overflow of the overflow bucket. 

        TODO: Implementation BinaryMidSquareHash::hashing, BucketHashTable::insert and BucketHashTable::erase functions

    Input: A sequence of commands
        - ('n',integer): the size of a key. (The first command is always 'n')
        - ('r',integer): the size of an index. (The second command is always 'r')
        - ('k',integer): the size of a bucket. (The third command is always 'k')
        - ('insert',integer): insert integer into the hash table.
        - ('erase',integer): delete integer from the hash table.

    Output: For each slot of the hash table and the overflow bucket, print out
        - the value if the state of the slot is occupied.
        - the state if the state of the slot is empty or deleted.
*/

void task_1(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 1]" << endl;
    try {
        int n, r, k, d, key;
        BinaryMidSquareHash *hf;
        BucketHashTable *ht;

        if (instr_seq.getLength() < 3 ||
            instr_seq.getInstruction(0).getCommand().compare("n") != 0 ||
            instr_seq.getInstruction(1).getCommand().compare("r") != 0 ||
            instr_seq.getInstruction(2).getCommand().compare("k") != 0) {
            cerr << "Invalid starting commands" << endl;
            exit(-1);
        }

        n = instr_seq.getInstruction(0).getValue();
        r = instr_seq.getInstruction(1).getValue();
        k = instr_seq.getInstruction(2).getValue();
        hf = new BinaryMidSquareHash(n, r);
        ht = new BucketHashTable(pow(2, r), k, hf);

        for (int i = 3; i < instr_seq.getLength(); i++) {
            string command = instr_seq.getInstruction(i).getCommand();
            int key = instr_seq.getInstruction(i).getValue();
            
            if (command.compare("insert") == 0) {
                ht->insert(key);
            } else if (command.compare("erase") == 0) {
                ht->erase(key);
            } else {
                cerr << "Invalid command" << endl;
                exit(-1);
            }
        }
        ht->print_table(fout);

        delete ht;
        delete hf;
    } catch (const char *e) {
        cerr << e << endl;
    }
}

/*
    [Task 2] Double Hashing

    Description:
        Implement a closed hash table with double hashing. This hash table is used with n-bit integer keys and hashing into a table of size 2^r.
        The index of the key k  after i-th collision, h_i (k), is:

        h_i (k) = (h_1 (k)+i⋅h_2 (k)) mod 2^r, 

        where h_1 (k) is the multiplication hash function, and h_2 (k) is the digit folding hash function.
        In multiplication hash function, we first multiply the key k by a constant real number A in the range 0<A<1 and extract the fractional part of kA.
        Then, we multiply this value by the size of a hash table and take the ﬂoor of the result.
        So h_1 will be denoted as

        h_1 (k) = floor(2^r (kA mod 1)).

        For simplicity, let’s use A =0.1.
        Also, digit folding hash function will sum all bits of a key, treating the key as n bits.
        You can assume that keys are positive integers.
        You don’t need to consider an insertion when the table is full, a deletion of a key which does not exist, and multiple insertions of the same key.
        And also you don’t need to consider the case when the hash function cannot find an available slot.
        Note that you cannot insert a new key into the deleted slot. 
        You can modify hast_function.cpp, hash_function.h, hash_table.cpp and hash_table.h files for this problem.
        Hint: Try to use fmod function in math library to extract the fractional part after division.

        TODO: Implementation MultiplicationHash::hashing, DigitFoldingHash::hashing, DoubleHashTable::insert and DoubleHashTable::erase functions 

    Input & output
    Input: A sequence of commands
        - ('n',integer): the size of a key. (The first command is always 'n')
        - ('r',integer): the size of an index. (The second command is always 'r')
        - ('insert',integer): insert {integer} into the hash table.
        - ('erase',integer): delete {integer} from the hash table.
        
    Output: For each slot of the hash table, print out
        - the value, if the state of the slot is occupied.
        - the state if the state of the slot is empty or deleted.
*/

void task_2(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 2]" << endl;
    try {
        int n, r, k, d, key;
        MultiplicationHash *hf_1;
        DigitFoldingHash *hf_2;
        DoubleHashTable *ht;

        if (instr_seq.getLength() < 2 ||
            instr_seq.getInstruction(0).getCommand().compare("n") != 0 ||
            instr_seq.getInstruction(1).getCommand().compare("r") != 0) {
            cerr << "Invalid starting commands" << endl;
            exit(-1);
        }

        n = instr_seq.getInstruction(0).getValue();
        r = instr_seq.getInstruction(1).getValue();
        hf_1 = new MultiplicationHash(n, r);
        hf_2 = new DigitFoldingHash(n, r);
        ht = new DoubleHashTable(pow(2, r), hf_1, hf_2);

        for (int i = 2; i < instr_seq.getLength(); i++) {
            string command = instr_seq.getInstruction(i).getCommand();
            int key = instr_seq.getInstruction(i).getValue();
            if (command.compare("insert") == 0) {
                ht->insert(key);
            } else if (command.compare("erase") == 0) {
                ht->erase(key);
            } else {
                cerr << "Invalid command" << endl;
                exit(-1);
            }
        }
        ht->print_table(fout);

        delete ht;
        delete hf_1;
        delete hf_2;
    } catch (const char *e) {
        cerr << e << endl;
    }
}

/*
    [Task 3] Undirected Graph - Graph Traversal
    
    Description:
        Implement a function that perform DFS and BFS traversal from the given undirected graph. 
        The graph may consist of several connected components. The search starts with the node of the smallest label in lexicographical order.  
        If there exist n connected component, then 
            1) print the total number of connected component and 
            2) print n traverses separated with a newline in the ascending lexicographical order. 

        TODO: Implement Graph::addUndirectedEdge, Graph::DFS and Graph::BFS functions

    Input & output
    Input: Pairs of node labels that indicate edges.
        - ('A', 'B'): an edge  between node A and B.
        - ('End','DFS') or ('End','BFS'):String representing traverse mode. 
        - If the input edge already exists in the graph, ignore the input.
    Output:
        - The number of connected component in the given undirected graph
        - The result of DFS or BFS traverse separated with white space. Multiple traverses should be separated with a new line, in an ascending lexicographical order.  
*/

void task_3(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 3]" << endl;
    try {
        Graph graph;
        for (int i = 0; i < instr_seq.getLength() - 1; i++) {
            string firstNode = instr_seq.getInstruction(i).getCommand();
            string secondNode = instr_seq.getInstruction(i).getValueStr();
            graph.addUndirectedEdge(firstNode, secondNode);
        }
        string search = instr_seq.getInstruction(instr_seq.getLength() - 1).getValueStr();
        if(search.compare("DFS") == 0)
            fout << graph.DFS() << endl;
        else if(search.compare("BFS") == 0)
            fout << graph.BFS() << endl;
    } catch (const char *e) {
        cerr << e << endl;
    }
}

/*
    [Task 4] Directed Graph - Strongly Connected Component

    Description:
        Implement a function that finds every strongly connected components in the given directed graph. 
        A strongly connected component is a maximal strongly connected subgraph which every vertex is reachable from every other vertex within the subgraph. 
        If there exist n strongly connected component, then 
            1) print the total number of strongly connected component and 
            2) print the strongly connected components in an ascending lexicographical order of it’s smallest label of nodes. 
               Print each strongly connected component by printing an ascending lexicographical order of node labels separated by white space. 

        TODO: Implement Graph::addDirectedEdge and Graph::StronglyConnectedComponent functions

    Input & output 
    Input: Pairs of node labels that indicate edges.  
        - ('A','B'): an edge from node A to node B. 
        - If the input edge already exists in the graph, ignore the input. 
        
    Output:  
        - The number of strongly connected component in the given directed graph. 
        - Strongly connected components separated with new line. It should be printed so that the label of the smallest node in each component is in ascending lexicographical order.  
        - The label of nodes in strongly connected component should be printed in an ascending lexicographical order and separated with white space. 
*/

void task_4(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 4]" << endl;
    try {
        Graph graph;
        for (int i = 0; i < instr_seq.getLength(); i++) {
            string firstNode = instr_seq.getInstruction(i).getCommand();
            string secondNode = instr_seq.getInstruction(i).getValueStr();
            graph.addDirectedEdge(firstNode, secondNode);
        }
        fout << graph.StronglyConnectedComponent() << endl;
    } catch (const char *e) {
        cerr << e << endl;
    }
}

/*
    [Task 5] Dijkstra's Algorithm

    Description:
        Implement a function that finds the shortest path from the source node to the destination node in the given graph.
        We assume that the given graph is a undirected, weighted, and weakly-connected graph.
        All weights of edges are positive (i.e. larger than 0).
        This function should return the sequence of node labels along the path and also the length (sum of the weights of the edges) of the path.
        If the path from the source node to the destination node doesn't exist, return 'error'.
        You can modify the graph.cpp and graph.h files for this problem.

        TODO: Implement Graph::addUndirectedEdge and Graph::getShortestPath_task5 functions

    Input & output
    Input: A sequence of commands
        - ('A-B', integer): an edge between node A to node B with weight value {integer}.
        - ('A', 'B'): a pair of node labels that indicates the source and the destination node. The first element indicates the source node and the second one indicates the destination node.
    Output:
        - A sequence of the node labels along the path followed by length of the path.
        - error if the path does not exist 
 */

void task_5(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 5]" << endl;
    try {
        Graph graph;
        for (int i = 0; i < instr_seq.getLength() - 1; i++) {
            string command = instr_seq.getInstruction(i).getCommand();
            int value = instr_seq.getInstruction(i).getValue();
            string firstNode = command.substr(0, command.find('-'));
            string secondNode =
                command.substr(command.find('-') + 1, command.length());
            graph.addUndirectedEdge(firstNode, secondNode, value);
        }
        string source =
            instr_seq.getInstruction(instr_seq.getLength() - 1).getCommand();
        string destination =
            instr_seq.getInstruction(instr_seq.getLength() - 1).getValueStr();
        fout << graph.getShortestPath_task5(source, destination) << endl;
    } catch (const char *e) {
        cerr << e << endl;
    }
}

/*
    [Task 6] Floyd's Algorithm
    
    Description:
        Implement a function that finds the shortest paths of all pairs of nodes in the given graph.
        Unlike problem 3, there will be an edge(s) with negative weight value(s).
        The answer output should return the sequence of node labels along the path and also the length (sum of the weights of the edges) of the path.
        If the source and the destination is identical, distance is 0.
        If there is no path from the source to the destination, distance is INF.
        You can modify the graph.cpp and graph.h files for this problem.
        
        TODO: Implement Graph::addUnDirectedEdge and Graph::getShortestPath_task6 function

    Input & output
    Input: A sequence of commands
        - ('A-B', integer): an edge between node A to node B with weight value {integer}.
        - ('A', 'B'): a pair of node labels that indicates the source and the destination node. The first element indicates the source node and the second one indicates the destination node.
    Output:
        - A sequence of the node labels along the path followed by length of the path.
        - INF if the path does not exist 
*/

void task_6(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 6]" << endl;
    try {
        Graph graph;
        for (int i = 0; i < instr_seq.getLength()-1; i++) {
            string command = instr_seq.getInstruction(i).getCommand();
            int value = instr_seq.getInstruction(i).getValue();
            string firstNode = command.substr(0, command.find('-'));
            string secondNode =
                command.substr(command.find('-') + 1, command.length());
            graph.addUndirectedEdge(firstNode, secondNode, value);
        }
        string source =
            instr_seq.getInstruction(instr_seq.getLength() - 1).getCommand();
        string destination =
            instr_seq.getInstruction(instr_seq.getLength() - 1).getValueStr();
        fout << graph.getShortestPath_task6(source, destination) << endl;
    } catch (const char *e) {
        cerr << e << endl;
    }
}


/*
    [Task 7] Prim's Algorithm

    Description:
        Implement a function that finds the Minimum-cost Spanning Tree (MST) of the given weighted undirected graph using Prim’s algorithm.
        Given a start node, this function starts with the single-vertex tree of the given node. 
        Then, the function prints the path from the start node to the newly added node.
        If there are multiple edges with the same weight, this function checks the label of the added node (i.e., the node which is not included in the tree) and selects the node with the first label in lexicographical order.
        Finally, the function returns the cost of the MST (i.e., the sum of edge weights).
        You can assume that the given graph is a connected graph.
        You can modify graph.cpp and graph.h files for this problem.

        TODO: Implement Graph::addUndirectedEdge and Graph::primMST functions

    Input & output
    Input: A sequence of commands
        - ('A-B',integer): an edge between node A to node B with a weight value {integer}.
        - ('MST','A'): find MST using the Prim’s algorithm which starts with node A.
    Output:
        - For each time the tree grows, print the path from the start node to the added node as a string separated with a white space.
        - Print the cost of MST.
*/

void task_7(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 7]" << endl;
    try {
        Graph graph;
        for (int i = 0; i < instr_seq.getLength(); i++) {
            string command = instr_seq.getInstruction(i).getCommand();
            if (command.compare("MST") == 0) {
                string startNode = instr_seq.getInstruction(i).getValueStr();
                fout << graph.primMST(fout, startNode) << endl;
            } else {
                string firstNode = command.substr(0, command.find('-'));
                string secondNode =
                    command.substr(command.find('-') + 1, command.length());
                int value = instr_seq.getInstruction(i).getValue();
                graph.addUndirectedEdge(firstNode, secondNode, value);
            }
        }
    } catch (const char *e) {
        cerr << e << endl;
    }
}

/*
    [Task 8] Kruskal's Algorithm

    Description:
        Implement a function that finds the Minimum-cost Spanning Tree (MST) of the given weighted undirected graph using Kruskal's algorithm.
        The function prints the added edge and the weight of the edge each time the tree grows.
        When printing an edge, you must print the label in lexicographical order.
        If there are multiple edges with the same weight, this function also selects the edge in lexicographical order.
        That means it compares the first node of edges, and if the first node is the same, it compares the second node of edges.
        The function returns the path between two nodes and the cost of the MST (i.e., the sum of edge weights).
        You can assume that the given graph is a connected graph.
        You can modify graph.cpp and graph.h files for this problem. 

        TODO: Implement Graph::addUndirectedEdge and Graph::kruskalMST functions

    Input & output
    Input: A sequence of commands
        - ('A-B',integer): an edge between node A to node B with a weight value {integer}.
        - ('MST',char): find MST using Kruskal's algorithm and find the path starting from the node with the smallest label in lexicographical order to the node with label {char}.
    Output:
        - For each time the tree grows, print the labels of the nodes indicating the added edges in lexicographical order and the weight of the edge as a string separated with a white space.
        - Print the path from the node with the smallest label in lexicographical order to the node with label {char} and the cost of MST.
*/

void task_8(ofstream &fout, InstructionSequence &instr_seq) {
    fout << "[Task 8]" << endl;
    try {
        Graph graph;
        for (int i = 0; i < instr_seq.getLength(); i++) {
            string command = instr_seq.getInstruction(i).getCommand();
            if (command.compare("MST") == 0) {
                string endNode = instr_seq.getInstruction(i).getValueStr();
                fout << graph.kruskalMST(fout, endNode) << endl;
            } else {
                string firstNode = command.substr(0, command.find('-'));
                string secondNode =
                    command.substr(command.find('-') + 1, command.length());
                int value = instr_seq.getInstruction(i).getValue();
                graph.addUndirectedEdge(firstNode, secondNode, value);
            }
        }
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
        } catch (const char *e) {
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
        case 7:
           task_7(fout, instr_seq);
           break;
        case 8:
           task_8(fout, instr_seq);
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

            instr_seq.parseInstructions(TASK_7_DEFAULT_ARGUMENT);
            task_7(fout, instr_seq);

            instr_seq.parseInstructions(TASK_8_DEFAULT_ARGUMENT);
            task_8(fout, instr_seq);

            break;
        default:
            cout << "Wrong task number" << endl;
    }

    fout.close();
    return 0;
}
