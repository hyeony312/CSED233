#include <iostream>
#include <string>
using namespace std;

class sortAlg {

public:
    sortAlg();

    int arr_size;
    int *arr, *temp;

    void printArray(ofstream &);
    void insertionSort(ofstream &);

    void mergeSort(ofstream &, int left, int right, int &count);
    void merge(int left, int right, int &count);


};

