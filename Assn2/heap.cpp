#include "heap.h"
#include <iostream>
#include <string>

using namespace std;

MaxHeap::MaxHeap() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string MaxHeap::printHeap() {
  string answer;
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  answer = heap[0];
  for (int i = 1; i < in_length; i++) {
    answer = answer + " " + heap[i];
  }
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
  return answer;
}

void MaxHeap::insertKey(string sen) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  in_length += sen.length();
  int j = 0;
  for (int i = new_node; i < in_length; i++) {
    heap[i] = sen[j];
    maxHeapProp();
    new_node++;
    j++;
  }
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

void MaxHeap::deleteMax() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  new_node--;
  heap[0] = heap[new_node];
  in_length--;

  int curr = 0, pre;
  int num = 1;
  while (new_node > num - 1) {
    num *= 2;
  }

  while (1) {
    pre = curr;
    if (heap[curr] > heap[curr * 2 + 1] || heap[curr] > heap[curr * 2 + 2]) {
      if (heap[curr * 2 + 1] <= heap[curr * 2 + 2]) {
        string temp = heap[curr];
        heap[curr] = heap[curr * 2 + 1];
        heap[curr * 2 + 1] = temp;
        curr = curr * 2 + 1;
      } else {
        string temp = heap[curr];
        heap[curr] = heap[curr * 2 + 2];
        heap[curr * 2 + 2] = temp;
        curr = curr * 2 + 2;
      }
    }
    cout << new_node << " "<<curr << endl;
    if (pre == curr || new_node-1 < curr * 2 + 1)
      break;
  }
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

void MaxHeap::maxHeapProp(/*your heap array*/) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here   /////////////
  if (new_node == 0)
    return;

  int pre, curr;
  pre = new_node;
  if (new_node % 2 == 1)
    curr = (new_node - 1) / 2;
  else
    curr = (new_node - 2) / 2;

  while (1) {
    if (heap[pre] < heap[curr]) {
      string temp = heap[pre];
      heap[pre] = heap[curr];
      heap[curr] = temp;
    }
    pre = curr;
    if (curr % 2 == 1)
      curr = (curr - 1) / 2;
    else
      curr = (curr - 2) / 2;

    if (pre == 0)
      break;
  }
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}