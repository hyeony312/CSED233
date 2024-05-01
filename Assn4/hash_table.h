#pragma once
#include <iostream>
#include <string>
#include "hash_function.h"

using namespace std;


enum TableState {
    EMPTY,
    OCCUPIED,
    DELETED,
};

class BucketHashTable {
public:
    BucketHashTable(int table_size, int bucket_size, BinaryMidSquareHash *hf);
    ~BucketHashTable();

    void print_table(ostream &out);

    void insert(int key);
    void erase(int key);

private:
    const int table_size;
    const int bucket_size;
    BinaryMidSquareHash *hf;
    int *table;
    int *overflow;
    TableState *table_states;
    TableState *overflow_states;

    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};

class DoubleHashTable {
public:
    DoubleHashTable(int table_size, MultiplicationHash *hf_1, DigitFoldingHash *hf_2);
    ~DoubleHashTable();

    void print_table(ostream &out);

    void insert(int key);
    void erase(int key);

private:
    const int table_size;
    MultiplicationHash *hf_1;
    DigitFoldingHash *hf_2;
    int *table;
    TableState *states;

    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};

