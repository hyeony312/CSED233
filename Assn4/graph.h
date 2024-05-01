#pragma once
#include <fstream>
#include <iostream>
#include <string>
#define NodeMaxCount 101
#define INF 2147483647
using namespace std;

/////////////////////////////////////////////////////////
///  TODO: Add Your Struct or Functions if required /////
class Node {
public:
  Node(string x) {
    label = x;
    next = NULL;
  };
  Node(string x, string y) {
    label = x;
    Node *node = new Node(y);
    next = node;
  };
  Node(string x, int w) {
    label = x;
    weight = w;
    next = NULL;
  };

  string label;
  int weight = 0;
  int connected = 0;
  int parent;
  Node *next;
};

class Dij_Node {
public:
  int D = INF;
  int P_count = 0;
  int P[NodeMaxCount] = {-1};
};

void changeNode(Node *array);
///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

class Graph {
public:
  Graph(){};
  ~Graph(){};

  string DFS();
  string BFS();

  int addDirectedEdge(string nodeA, string nodeB);
  int addDirectedEdge(string nodeA, string nodeB, int weight);
  int addUndirectedEdge(string nodeA, string nodeB);
  int addUndirectedEdge(string nodeA, string nodeB, int weight);

  string StronglyConnectedComponent();

  string getShortestPath_task5(string source, string destination);
  string getShortestPath_task6(string source, string destination);
  int primMST(ofstream &, string startNode);
  int kruskalMST(ofstream &, string endNode);

private:
  /////////////////////////////////////////////////////////
  //////  TODO: Add private members if required ///////////
  // task3
  Node *AdjList[NodeMaxCount] = {NULL};
  int mark[NodeMaxCount] = {0}; // Visted node change to 1
  int NodeNum = 0;

  int findIndex(string v);
  void insertUndi(string x, string y);
  void _DFS(string v, string &output);
  void _BFS(string v, string &output);

  // task4
  /*Node* _AdjList[NodeMaxCount]= {NULL};
string DFSstack[NodeMaxCount]= {NULL};
string route[NodeMaxCount]= {NULL};
int _NodeNum = 0;
void makeOplist();
int _findIndex(string v);
void SCC_DFS(string v);
void Back_DFS(string v, string route[],int& count);
*/

  // task5
  void WinsertUndi(string x, string y, int w);
  void makePath(int index, int start, string path, Dij_Node Table[]);
  int rCount = 0;
  string route[NodeMaxCount];

  // task8
  void updateST(int x, int y, int ST[][101], int STeach[], int &STnum);
  int CheckCycle(int x, int y, int ST[][101], int STeach[], int STnum);
  void search(int start, string endNode, string output);
  string output_8;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
};
