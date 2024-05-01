#include "hash_function.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int BinaryMidSquareHash::hashing(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  string _key = D2B(pow(key, 2), key_size); // Squared key
  int output = 0, i = 0;

  while (index_size > i) {
    if (_key[key_size - 1 + i] == '1') {
      output += pow(2, index_size - i);
      i++;
    } else {
      i++;
    }
  }

  return output;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

int DigitFoldingHash::hashing(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  int output=0;
  int i = key_size - 1;

  while (i >= 0) {
    if (key >= pow(2, i)) {
      key -= pow(2, i);
      i--;
      output += 1;
    } else {
      i--;
    }
  }

  return output;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

int MultiplicationHash::hashing(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  return floor(pow(2,index_size)*fmod(key*0.1,1));
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */
string BinaryMidSquareHash::D2B(int key, int size) {
  string output;
  int i = 2 * size - 1;

  while (i >= 0) {
    if (key >= pow(2, i)) {
      key -= pow(2, i);
      i--;
      output += '1';
    } else {
      i--;
      output += '0';
    }
  }

  return output;
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
