#include "graph.h"
#include <fstream>
#include <iostream>
#include <string>
#define INF 2147483647
using namespace std;

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////
/*  Write your codes if you have additional functions  */
// task3
void Graph::insertUndi(string x, string y) {
  int index = findIndex(x);
  if (index == -1) {
    for (int i = 0; i <= NodeNum; i++) { // Select index
      if (i == NodeNum) {
        Node *node = new Node(x, y);
        AdjList[i] = node;
        break;
      } else if (x < AdjList[i]->label) {
        for (int j = NodeNum; j > i; j--) {
          AdjList[j] = AdjList[j - 1];
        }
        Node *node = new Node(x, y);
        AdjList[i] = node;
        break;
      }
    }
  } else { // Arleady exist
    Node *temp = new Node(y);
    for (Node *curr = AdjList[index]; curr != NULL; curr = curr->next) {
      if (curr->next == NULL) {
        curr->next = temp;
        break;
      } else if (y < curr->next->label) {
        temp->next = curr->next;
        curr->next = temp;
        break;
      }
    }
  }

  NodeNum = 0;
  for (int i = 0; AdjList[i] != NULL; i++) {
    NodeNum++;
  }
}

void Graph::WinsertUndi(string x, string y, int w) {
  int index = findIndex(x);
  if (index == -1) {
    for (int i = 0; i <= NodeNum; i++) { // Select index
      if (i == NodeNum) {
        Node *node = new Node(x, y);
        node->next->weight = w;
        AdjList[i] = node;
        break;
      } else if (x < AdjList[i]->label) {
        for (int j = NodeNum; j > i; j--) {
          AdjList[j] = AdjList[j - 1];
        }
        Node *node = new Node(x, y);
        node->next->weight = w;
        AdjList[i] = node;
        break;
      }
    }
  } else { // Arleady exist
    Node *temp = new Node(y);
    temp->weight = w;
    for (Node *curr = AdjList[index]; curr != NULL; curr = curr->next) {
      if (curr->next == NULL) {
        curr->next = temp;
        break;
      } else if (y < curr->next->label) {
        temp->next = curr->next;
        curr->next = temp;
        break;
      }
    }
  }

  NodeNum = 0;
  for (int i = 0; AdjList[i] != NULL; i++) {
    NodeNum++;
  }
}

int Graph::findIndex(string v) {
  for (int i = 0; i < NodeNum; i++) {
    if (AdjList[i]->label == v)
      return i;
  }
  return -1;
}

void Graph::_DFS(string v, string &output) {
  int index = findIndex(v);
  if (index == -1)
    return;
  // Marking
  mark[index] = 1;
  output = output + AdjList[index]->label + " ";
  // Search
  for (Node *curr = AdjList[index]->next; curr != NULL; curr = curr->next) {
    if (mark[findIndex(curr->label)] == 0) {
      _DFS(curr->label, output);
    }
  }
}

void Graph::_BFS(string v, string &output) {
  int index = findIndex(v);
  int Q[NodeMaxCount];
  int Qcount = 0;

  if (index == -1)
    return;

  // Marking & Print
  for (Node *curr = AdjList[index]->next; curr != NULL; curr = curr->next) {
    if (mark[findIndex(curr->label)] == 0) {
      output = output + curr->label + " ";
      mark[findIndex(curr->label)] = 1;

      Q[Qcount] = findIndex(curr->label);
      Qcount++;
    }
  }
  // Search
  for (int i = 0; i < Qcount; i++) {
    _BFS(AdjList[Q[i]]->label, output);
  }
}

// task4
/*
void Graph::makeOplist() {
  int _count = 0;
  for (int i = 0; AdjList[i] != NULL; i++) {
    for (Node *curr = AdjList[i]->next; curr != NULL; curr = curr->next) {
      for (int j = 0;; j++) {
        if (j == _count) {
          Node *node = new Node(AdjList[i]->label);
          _AdjList[j] = node;
          _count++;
        } else if (curr->label == _AdjList[j]->label)
          continue;
      }
    }
  }

  // sort
  for (int i = _count; i > 0; i--) {
    for (int j = i; j > 0; j--) {
      if (_AdjList[j]->label < _AdjList[j - 1]->label) {
        Node *temp = _AdjList[j];
        _AdjList[j] = _AdjList[j - 1];
        _AdjList[j - 1] = temp;
      }
    }
  }

  for (int i = 0; AdjList[i] != NULL; i++) {
    for (Node *curr = AdjList[i]->next; curr != NULL; curr = curr->next) {
      for (int j = 0;; j++) {
        if (curr->label == _AdjList[j]->label) {
          Node *node = new Node(AdjList[i]->label);
          for (Node *_curr = _AdjList[j];; _curr = _curr->next) {
            if (_curr->next == NULL) {
              _curr->next = node;
              break;
            }
          }
          break;
        }
      }
    }
  }
}

void Graph::SCC_DFS(string v) {
  int index = findIndex(v);
  if (index == -1)
    return;
  // Marking
  mark[index] = 1;
  DFSstack[_NodeNum] = v;
  _NodeNum++;
  // Search
  for (Node *curr = AdjList[index]->next; curr != NULL; curr = curr->next) {
    if (mark[findIndex(curr->label)] == 0) {
      SCC_DFS(curr->label);
    }
  }
}

int Graph::_findIndex(string v) {
  for (int i = 0; i < _NodeNum; i++) {
    if (_AdjList[i]->label == v)
      return i;
  }
  return -1;
}

void Graph::Back_DFS(string v, string route[], int &count) {
  int index = _findIndex(v);
  if (index == -1)
    return;
  // Marking
  mark[index] = 1;
  route[count] = v;
  count++;
  // Search
  for (Node *curr = AdjList[index]->next; curr != NULL; curr = curr->next) {
    if (mark[_findIndex(curr->label)] == 0) {
      Back_DFS(curr->label, route, count);
    }
  }
}
*/

// task5
void Graph::makePath(int index, int start, string path, Dij_Node Table[]) {
  if (index == start) {
    route[rCount] = path;
    rCount++;
    return;
  }
  for (int i = 0; i < Table[index].P_count; i++) {
    string temp = path + " " + AdjList[Table[index].P[i]]->label;
    makePath(Table[index].P[i], start, temp, Table);
  }
}

// task7
int CheckMST(string x, string array[], int count) {
  for (int i = 0; i < count; i++) {
    if (array[i] == x)
      return 1;
  }
  return 0;
}

// task8
void Graph::updateST(int x, int y, int ST[][101], int STeach[], int &STnum) {
  int index1 = -1, index2 = -1;
  if (STnum == 0) {
    ST[STnum][0] = x;
    ST[STnum][1] = y;
    STeach[STnum] = 2;
    STnum++;
    return;
  }

  for (int i = 0; i < STnum; i++) {
    for (int j = 0; j < STeach[i]; j++) {
      if (x == ST[i][j]) {
        index1 = i;
      }
      if (y == ST[i][j]) {
        index2 = i;
      }
    }
  }

  if (index1 == -1 && index2 == -1) {
    ST[STnum][0] = x;
    ST[STnum][1] = y;
    STeach[STnum] = 2;
    STnum++;
  } else if (index1 != -1 && index2 != -1) { // ST[index1]+ST[index2]
    int temp[index1 + index2 - 1];
    int Num = STeach[index1];

    for (int i = 0; i < Num; i++) {
      temp[i] = ST[index1][i];
    }
    for (int i = 0; i < STeach[index2]; i++) {
      if (ST[index2][i] != x && ST[index2][i] != y) {
        temp[Num] = ST[index2][i];
        Num++;
      }
    }

    // save temp
    for (int i = 0; i < Num; i++) {
      ST[index1][i] = temp[i];
    }
    STeach[index1] = Num;
    for (int i = index2; i < STnum - 1; i++) {
      for (int j = 0; j < STeach[i + 1]; j++) {
        ST[i][j] = ST[i + 1][j];
      }
      STeach[i] = STeach[i + 1];
    }
    STnum--;
  } else if (index1 != -1) {
    ST[index1][STeach[index1]] = y;
    STeach[index1]++;
  } else if (index2 != -1) {
    ST[index2][STeach[index2]] = x;
    STeach[index2]++;
  }
}

int Graph::CheckCycle(int x, int y, int ST[][101], int STeach[], int STnum) {
  int index1 = -1, index2 = -1;
  if (STnum == 0)
    return 0;

  for (int i = 0; i < STnum; i++) {
    for (int j = 0; j < STeach[i]; j++) {
      if (x == ST[i][j]) {
        index1 = i;
      }
      if (y == ST[i][j]) {
        index2 = i;
      }
    }
  }

  if (index1 != -1 && index2 != -1) {
    if (index1 == index2) {
      return 1;
    }
  }
  return 0;
}

void Graph::search(int start, string endNode, string output) {
  if (start == findIndex(endNode)) {
    output_8 = output + endNode;
    return;
  }

  output = output + AdjList[start]->label + " ";
  // Search
  for (Node *curr = AdjList[start]->next; curr != NULL; curr = curr->next) {
    if (curr->connected == 1) {
      Node *temp;
      for (Node *_curr = AdjList[findIndex(curr->label)]->next; _curr != NULL;
           _curr = _curr->next) {
        if (findIndex(_curr->label) == start) {
          temp = _curr;
          break;
        }
      }
      curr->connected = 0;
      temp->connected = 0;
      search(findIndex(curr->label), endNode, output);
      curr->connected = 1;
      temp->connected = 1;
    }
  }
}
///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

string Graph::DFS() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  string output;
  int count = 0;
  for (int i = 0; i < NodeNum; i++) {
    if (mark[i] == 0) {
      count++;
      output += '\n';
      _DFS(AdjList[i]->label, output);
    }
  }
  string com_count(to_string(count));

  return com_count + output;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

string Graph::BFS() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  string output;
  int count = 0;
  for (int i = 0; i < NodeNum; i++) {
    if (mark[i] == 0) {
      count++;
      output += '\n';
      output = output + AdjList[i]->label + " ";
      mark[i] = 1;
      _BFS(AdjList[i]->label, output);
    }
  }
  string com_count(to_string(count));

  return com_count + output;
  return "";
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int Graph::addDirectedEdge(string nodeA, string nodeB) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  /*
  if (AdjList[0] == NULL) { // Empty list
    Node *node = new Node(nodeA, nodeB);
    AdjList[0] = node;
    NodeNum = 1;

    return 0;
  }

  insertUndi(nodeA, nodeB);

  for (int i = 0; i < NodeNum; i++) {
    cout << "AdjLIst[" << i << "]: " << AdjList[i]->label;
    for (Node *curr = AdjList[i]->next; curr != NULL; curr = curr->next) {
      cout << " -> " << curr->label;
    }
    cout << endl;
  }
*/
  return 0;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int Graph::addDirectedEdge(string nodeA, string nodeB, int weight) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  return 0;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int Graph::addUndirectedEdge(string nodeA, string nodeB) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  if (nodeA == nodeB) {
    return 0;
  }

  if (AdjList[0] == NULL) { // Empty list
    Node *node1 = new Node(nodeA, nodeB);
    Node *node2 = new Node(nodeB, nodeA);

    if (nodeA > nodeB) {
      AdjList[0] = node2;
      AdjList[1] = node1;
    } else {
      AdjList[0] = node1;
      AdjList[1] = node2;
    }

    NodeNum = 2;
    return 0;
  }
  insertUndi(nodeA, nodeB);
  insertUndi(nodeB, nodeA);

  /*for (int i = 0; i < NodeNum; i++) {
    cout << "AdjLIst[" << i << "]: " << AdjList[i]->label;
    for (Node *curr = AdjList[i]->next; curr != NULL; curr = curr->next) {
      cout << " -> " << curr->label;
    }
    cout << endl;
  }*/

  return 0;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int Graph::addUndirectedEdge(string nodeA, string nodeB, int w) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  if (AdjList[0] == NULL) { // Empty list
    Node *node1 = new Node(nodeA, nodeB);
    node1->next->weight = w;
    Node *node2 = new Node(nodeB, nodeA);
    node2->next->weight = w;

    if (nodeA > nodeB) {
      AdjList[0] = node2;
      AdjList[1] = node1;
    } else {
      AdjList[0] = node1;
      AdjList[1] = node2;
    }

    NodeNum = 2;
    return 0;
  }
  WinsertUndi(nodeA, nodeB, w);
  WinsertUndi(nodeB, nodeA, w);
  return 0;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

string Graph::StronglyConnectedComponent() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  /*
  string output;
  int sccCount = 0;
  int comCount;

  for (int i = 0; i < NodeNum; i++) {
    if (mark[i] == 0) {
      SCC_DFS(AdjList[i]->label);
    }
  }

  for (int i = 0; i < _NodeNum; i++) {
    mark[i] = 0;
  }
  makeOplist();

  for (int i = _NodeNum; i >= 0; i--) {
    if (mark[i] == 0) {
      comCount = 0;
      Back_DFS(DFSstack[i], route, comCount);

      for (int k = comCount; k > 0; k--) {
        for (int j = k; j > 0; j--) {
          if (route[j] < route[j - 1]) {
            string temp = route[j];
            route[j] = route[j - 1];
            route[j - 1] = temp;
          }
        }
      }
      output += '\n';
      for (int k = 0; k < comCount; k++) {
        output = output + route[k] + ' ';
      }
      sccCount++;
    }
  }

  string com_count(to_string(sccCount)); */

  return " ";
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

string Graph::getShortestPath_task5(string source, string destination) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  string output;

  int start = findIndex(source);
  string S[NodeNum];
  Dij_Node Table[NodeNum];
  int Snum = 0;
  int Min = INF;

  // Initial
  S[Snum] = source;
  Snum++;
  int index = findIndex(source);
  mark[index] = 1;
  for (Node *curr = AdjList[index]; curr != NULL; curr = curr->next) {
    int i = findIndex(curr->label);
    if (Table[i].D > curr->weight) {
      Table[i].D = curr->weight;
      Table[i].P_count = 1;
      Table[i].P[0] = index;
    }
  }

  // Start
  while (Snum < NodeNum) {
    // Choose next node
    Min = INF;
    for (int i = 0; i < NodeNum; i++) {
      if ((mark[i] == 0) && (Min > Table[i].D)) {
        Min = Table[i].D;
        index = i;
      }
    }
    mark[index] = 1;

    if (AdjList[index]->label == destination)
      break;

    // Update table
    S[Snum] = AdjList[index]->label;
    Snum++;
    for (Node *curr = AdjList[index]->next; curr != NULL; curr = curr->next) {
      if (mark[findIndex(curr->label)] == 0) { // Check mark
        if ((Table[findIndex(curr->label)].D) >
            (Table[index].D + curr->weight)) {
          Table[findIndex(curr->label)].D = Table[index].D + curr->weight;
          Table[findIndex(curr->label)].P[0] = index;
          Table[findIndex(curr->label)].P_count = 1;
        } else if ((Table[findIndex(curr->label)].D) ==
                   (Table[index].D + curr->weight)) {
          int i = ++Table[findIndex(curr->label)].P_count;
          Table[findIndex(curr->label)].P[i] = index;
        }
      }
    }
  }

  if (Table[findIndex(destination)].P_count == 0) {
    return "error";
  }

  /*
  for (int i = 0; i < NodeNum; i++) {
    cout << AdjList[i]->label << "  ";
    cout << "distance: " << Table[i].D;
    cout << "  route:";
    for (int j = 0; j < Table[i].P_count; j++) {
      cout << " " << Table[i].P[j];
    }
    cout << endl;
  }
  cout << endl;
  */

  string path = to_string(Table[findIndex(destination)].D) + " " + destination;
  makePath(findIndex(destination), start, path, Table);

  string _output[rCount];

  for (int i = 0; i < rCount; i++) {
    for (int j = route[i].length() - 1; j >= 0; j--) {
      _output[i] += route[i][j];
    }
  }

  // Sort
  for (int i = 0; i < rCount; i++) {
    for (int j = rCount - 1; j > i; j--) {
      if (_output[j] < _output[j - 1]) {
        string temp = _output[j];
        _output[j] = _output[j - 1];
        _output[j - 1] = temp;
      }
    }
  }

  for (int i = 0; i < rCount; i++) {
    output += _output[i];
    if (i + 1 < rCount) {
      output += '\n';
    }
  }
  /*for (int i = 0; i < NodeNum; i++) {
    cout << "AdjLIst[" << i << "]: " << AdjList[i]->label;
    for (Node *curr = AdjList[i]->next; curr != NULL; curr = curr->next) {
      cout << " -> " << curr->label << '(' << curr->weight << ')';
    }
    cout << endl;
  }*/
  return output;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string Graph::getShortestPath_task6(string source, string destination) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  string output;
  int A[NodeNum][NodeNum];
  int next[NodeNum][NodeNum];
  int edge[NodeNum][NodeNum];
  int copy_edge[NodeNum][NodeNum];
  int i, j, k;

  int path[NodeNum];
  int pCount = 0;
  int start, end;

  // Initial
  for (i = 0; i < NodeNum; i++) {
    for (j = 0; j < NodeNum; j++) {
      if (i == j) {
        A[i][j] = 0;
      } else {
        A[i][j] = INF;
      }
      next[i][j] = -1;
      edge[i][j] = 0;
    }
  }
  for (i = 0; i < NodeNum; i++) {
    for (Node *curr = AdjList[i]->next; curr != NULL; curr = curr->next) {
      j = findIndex(curr->label);
      A[i][j] = curr->weight;
      next[i][j] = j;
      edge[i][j] = 1; // edge exist
    }
  }

  /*
  cout << "A[i][j]" << endl;
  for (int I = 0; I < NodeNum; I++) {
    for (int J = 0; J < NodeNum; J++) {
      cout << A[I][J] << " ";
    }
    cout << endl;
  }
  cout << "next[i][j]" << endl;
  for (int I = 0; I < NodeNum; I++) {
    for (int J = 0; J < NodeNum; J++) {
      cout << next[I][J] << " ";
    }
    cout << endl;
  }
  cout << endl;
  */

  // Start
  for (k = 0; k < NodeNum; k++) {
    for (i = 0; i < NodeNum; i++) {
      for (j = 0; j < NodeNum; j++) {
        if (A[i][k] == INF || A[k][j] == INF)
          continue;
        else if (i == j)
          continue;
        else if (A[i][j] > A[i][k] + A[k][j]) {
          /*
          // copy edge table
          for (int x = 0; x < NodeNum; x++) {
            for (int y = 0; y < NodeNum; y++) {
              copy_edge[x][y] = edge[x][y];
            }
          }
          // check duplicated
          int CheckD = 0;
          start = i;
          end = k;
          while (start != end) {
            start = next[start][end];
            if (copy_edge[start][end] == 0) {
              CheckD = 1;
              break;
            };
            copy_edge[start][end] = 0;
          }

          if (CheckD == 1) {
            continue;
          }

          start = k;
          end = j;
          while (start != end) {
            start = next[start][end];
            if (copy_edge[start][end] == 0) {
              CheckD = 1;
              break;
            };
            copy_edge[start][end] = 0;
          }

          if (CheckD == 1) {
            continue;
          }
          */

          A[i][j] = A[i][k] + A[k][j];
          next[i][j] = next[i][k];
        }
      }
    }
  }

  /*
  cout << "A[i][j]" << endl;
  for (i = 0; i < NodeNum; i++) {
    for (j = 0; j < NodeNum; j++) {
      cout << A[i][j] << " ";
    }
    cout << endl;
  }
  cout << "next[i][j]" << endl;
  for (i = 0; i < NodeNum; i++) {
    for (j = 0; j < NodeNum; j++) {
      cout << next[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
  */

  // Find path
  start = findIndex(source);
  end = findIndex(destination);
  int distance = A[start][end];

  if (distance == INF) {
    return "INF";
  }

  path[pCount] = start;
  pCount = 1;
  while (start != end) {
    start = next[start][end];
    path[pCount] = start;
    pCount++;
  }

  for (i = 0; i < pCount; i++) {
    output = output + AdjList[path[i]]->label + " ";
  }
  output += to_string(distance);

  return output;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

int Graph::primMST(ofstream &fout, string startNode) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  string output;
  int index, total = 0;
  int Min;
  int minCount = 1;
  string _Node[NodeNum];
  int _Parent[NodeNum];

  string MST[NodeNum];
  int Parent[NodeNum];
  Parent[0] = -1;
  MST[0] = startNode;
  int mstCount = 1;

  while (mstCount != NodeNum) {
    Min = INF;
    minCount = 0;
    for (int i = 0; i < mstCount; i++) {
      index = findIndex(MST[i]);
      for (Node *curr = AdjList[index]; curr != NULL; curr = curr->next) {
        if (CheckMST(curr->label, MST, mstCount) == 0) { // not in MST
          if (Min == curr->weight) {
            _Node[minCount] = curr->label;
            _Parent[minCount] = i;
            minCount++;
          } else if (Min > curr->weight) { // Find min cost
            Min = curr->weight;
            _Node[0] = curr->label;
            _Parent[0] = i;
            minCount = 1;
          }
        }
      }
    }

    string Route[NodeNum];
    int rNum;

    for (int i = 0; i < minCount; i++) {
      total += Min;
      MST[mstCount] = _Node[i];
      Parent[mstCount] = _Parent[i];
      mstCount++;
      rNum = 0;
      for (int j = mstCount - 1;; j = Parent[j]) {
        Route[rNum] = MST[j];
        rNum++;
        if (Parent[j] == -1) {
          fout << MST[0];
          for (int k = rNum - 2; k >= 0; k--) {
            fout << " " << Route[k];
          }
          fout << endl;
          break;
        }
      }
    }

    /*
    cout << mstCount << endl;
    for (int i = 0; i < minCount; i++) {
      cout << "Min: " << Min << " Label: " << _Node[i]
           << " Parent: " << _Parent[i] << endl;
    }
    */
  }

  return total;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

int Graph::kruskalMST(ofstream &fout, string endNode) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  Node *record[101];
  int Min = INF, MinCount = 0, recordCount = 0;
  int index;
  int ST[NodeNum][101];
  int STeach[NodeNum];
  for (int i = 0; i < NodeNum; i++) {
    STeach[i] = 0;
    for (int j = 0; j < 101; j++) {
      ST[i][j] = 0;
    }
  }
  int STnum = 0;

  int total = 0;

  while (recordCount != NodeNum - 1) {
    Min = INF;
    MinCount = 0;
    for (int i = 0; i < NodeNum; i++) {
      for (Node *curr = AdjList[i]->next; curr != NULL; curr = curr->next) {
        curr->parent = i;
        if (curr->connected == 0) {
          if (!CheckCycle(i, findIndex(curr->label), ST, STeach, STnum)) {
            if (Min == curr->weight) {
              record[MinCount] = curr;
              MinCount++;
            } else if (Min > curr->weight) {
              record[0] = curr;
              Min = curr->weight;
              MinCount = 1;
            }
          }
        }
      }
    }
    ////////////////////////////////
    /*
    cout << "test2" << endl;
    cout << "MinCount " << MinCount << endl;
    for (int i = 0; i < MinCount; i++) {
      cout << "i: " << i << " label: " << record[i]->label
           << " parent: " << record[i]->parent
           << " connected: " << record[i]->connected << endl;
    }
    */
    ////////////////////////////////
    for (int i = 0; i < MinCount; i++) {
      if (record[i]->connected == 0) {
        if (!CheckCycle(record[i]->parent, findIndex(record[i]->label), ST,
                        STeach, STnum)) {
          record[i]->connected = 1;

          fout << AdjList[record[i]->parent]->label << " " << record[i]->label
               << " " << record[i]->weight << endl;
          total += record[i]->weight;

          index = findIndex(record[i]->label);
          for (Node *curr = AdjList[index]->next; curr != NULL;
               curr = curr->next) {
            if (record[i]->parent == findIndex(curr->label)) {
              curr->connected = 1;
              updateST(record[i]->parent, index, ST, STeach, STnum);
              recordCount++;
            }
          }
        }
      }
    }
  }

  search(0, endNode, "");
  fout << output_8 << " ";

  return total;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}
