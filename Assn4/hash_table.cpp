#include "hash_table.h"
#include "hash_function.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

BucketHashTable::BucketHashTable(int table_size, int bucket_size,
                                 BinaryMidSquareHash *hf)
    : table_size(table_size), bucket_size(bucket_size) {
  this->hf = hf;
  this->table = new int[this->table_size * this->bucket_size];
  this->overflow = new int[this->table_size];
  this->table_states =
      new TableState[this->table_size * this->bucket_size]{EMPTY};
  this->overflow_states = new TableState[this->table_size]{EMPTY};

  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  /*  Write your codes if you need  */

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

BucketHashTable::~BucketHashTable() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  /*  Write your codes if you need  */

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////

  delete[] this->table;
  delete[] this->overflow;
  delete[] this->table_states;
  delete[] this->overflow_states;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
void BucketHashTable::print_table(ostream &out) {

  out << "Hash table" << endl;
  int state;
  for (int i = 0; i < table_size; i++) {
    out << i << ": ";
    for (int j = 0; j < bucket_size; j++) {
      state = table_states[i * bucket_size + j];
      if (state == EMPTY)
        out << "empty";
      else if (state == DELETED)
        out << "deleted";
      else if (state == OCCUPIED)
        out << table[i * bucket_size + j];
      else
        out << "unknown state";
      if (j < bucket_size - 1)
        out << ",";
    }
    out << endl;
  }
  out << "----------" << endl << "Overflow" << endl;
  for (int i = 0; i < table_size; i++) {
    out << i << ": ";
    state = overflow_states[i];
    if (state == EMPTY)
      out << "empty" << endl;
    else if (state == DELETED)
      out << "deleted" << endl;
    else if (state == OCCUPIED)
      out << overflow[i] << endl;
    else
      out << "unknown state" << endl;
  }
}

void BucketHashTable::insert(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  int Hcode = hf->hashing(key);
  int i = 0;

  while (i < bucket_size) {
    if (table_states[Hcode + i] == EMPTY) {
      table[Hcode + i] = key;
      table_states[Hcode + i] = OCCUPIED;
      return;
    }
    i++;
  }

  i = 0;
  while (1) {
    if (overflow_states[i] == EMPTY) {
      overflow[i] = key;
      overflow_states[i] = OCCUPIED;
      return;
    }
    i++;
  }
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

void BucketHashTable::erase(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  int Hcode = hf->hashing(key);
  int i = 0;

  while (i < bucket_size) {
    if (table_states[Hcode + i] == DELETED) {
      i++;
    } else if (table_states[Hcode + i] == EMPTY) {
      break;
    } else {
      if (table[Hcode + i] == key) {
        table[Hcode + i] = -1;
        table_states[Hcode + i] = DELETED;
        return;
      }
      i++;
    }
  }

  i = 0;
  while (1) {
    if (overflow_states[i] == DELETED) {
      i++;
    } else {
      if (overflow[i] == key) {
        overflow[i] = -1;
        overflow_states[i] = DELETED;
        return;
      }
      i++;
    }
  }

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

DoubleHashTable::DoubleHashTable(int table_size, MultiplicationHash *hf_1,
                                 DigitFoldingHash *hf_2)
    : table_size(table_size) {
  this->hf_1 = hf_1;
  this->hf_2 = hf_2;
  this->table = new int[this->table_size];
  this->states = new TableState[this->table_size]{EMPTY};

  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  /*  Write your codes if you need  */

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

DoubleHashTable::~DoubleHashTable() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  /*  Write your codes if you need  */

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////

  delete[] this->table;
  delete[] this->states;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
void DoubleHashTable::print_table(ostream &out) {
  for (int i = 0; i < this->table_size; i++) {
    out << i << ": ";
    int state = this->states[i];
    if (state == EMPTY)
      out << "empty" << endl;
    else if (state == DELETED)
      out << "deleted" << endl;
    else if (state == OCCUPIED)
      out << this->table[i] << endl;
    else
      out << "unknown state" << endl;
  }
}

void DoubleHashTable::insert(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  int Hcode = hf_1->hashing(key);
  int i = 1;

  while (1) {
    if (states[Hcode] == EMPTY) {
      table[Hcode] = key;
      states[Hcode] = OCCUPIED;
      return;
    } else {
      Hcode = fmod(hf_1->hashing(key) + i * hf_2->hashing(key), table_size);
      i++;
    }
  }

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

void DoubleHashTable::erase(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  int Hcode = hf_1->hashing(key);
  int i = 1;

  while (1) {
    if (table[Hcode] == key) {
      table[Hcode] = -1;
      states[Hcode] = DELETED;
      return;
    } else {
      Hcode = fmod(hf_1->hashing(key) + i * hf_2->hashing(key), table_size);
      i++;
    }
  }
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
