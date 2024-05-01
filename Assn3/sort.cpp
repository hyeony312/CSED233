#include "sort.h"
#include <fstream>
#include <iostream>
#include <string>

sortAlg::sortAlg() {
  arr_size = 0;
  arr = new int[100];  // Each test case will be less than 100 values
  temp = new int[100]; // Each test case will be less than 100 values
}

using namespace std;

void sortAlg::printArray(ofstream &fout) {
  string answer;
  for (int i = 0; i < arr_size - 1; i++)
    answer += to_string(arr[i]) + " ";
  answer += to_string(arr[arr_size - 1]);
  fout << answer << endl;
}

void sortAlg::insertionSort(ofstream &fout) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  for (int i = 1; i < arr_size; i++) {
    for (int j = 0; j < i; j++) {
      if (arr[i] > arr[j])
        continue;
      else if (arr[i] <= arr[j]) {
        int _temp = arr[i];
        for (int k = i - 1; k >= j; k--)
          arr[k + 1] = arr[k];
        arr[j] = _temp;
      }
    }
    printArray(fout); // DO NOT ERASE THIS LINE
  }
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

void sortAlg::merge(int left, int right, int &count) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  int mid = (left + right) / 2;
  int _size = (right - left + 1) / 2;
  int *A = new int[_size];
  int *B = new int[_size];
  int countA = _size;
  int countB = _size;
  int index, k = arr[left];

  if (left == right)
    return;

  for (int i = 0; i < _size; i++) {
    A[i] = arr[left + i];
    B[i] = arr[mid + 1 + i];
  }

  for (int i = 0; i < right - left + 1; i++) {
    for (int j = 0; j < countA; j++) { // loop for A
      if (k >= A[j]) {
        k = A[j];
        index = j;
      }
    }
    for (int j = 0; j < countB; j++) { // loop for B
      if (k >= B[j]) {
        k = B[j];
        index = j + _size;
      }
    }

    temp[i] = k;
    if (countA > 0 && index >= _size)
      count++;

    if (index < _size) {
      for (int i = index; i < _size; i++)
        A[i] = A[i + 1];
      countA--;
    } else {
      for (int i = index - _size; i < _size; i++)
        B[i] = B[i + 1];
      countB--;
    }

    for (int i = left; i <= right; i++) {
      if (k < arr[i])
        k = arr[i];
    }
  }

  for (int i = left; i <= right; i++) {
    arr[i] = temp[i - left];
  }
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

void sortAlg::mergeSort(ofstream &fout, int left, int right, int &count) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  if (left < right) {
    int mid = (left + right) / 2;
    mergeSort(fout, left, mid, count);
    mergeSort(fout, mid + 1, right, count);
    merge(left, right, count);
    printArray(fout); // DO NOT ERASE THIS LINE
  }
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}
