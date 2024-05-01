#include "utils.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

/*
    [Task 1] Choose the TIGHT bound of the following arrayInsert function

    *arrayInsert*
        Input
        - int n: the length of the input arrays (n >=1)
        - int* A: an array storing n integers
        - int x: an element to insert
        - int pos : index position to insert element
        Output
        - int: The maximum product of elements from each A and B
        void arrayInsert(int n, int* A, int x, int pos) {
            n++;
            for (int i = n; i >= pos; i--)
                A[i] = A[i-1];
            A[pos – 1] = x;
            return;
        }

    Choices
        1: O( 1 )
        2: O( n )
        3: O( n log(n) )
        4: O( n^2 )
*/
void task_1(ofstream &fout) {
  int answer = 2; // TODO: Change to your answer

  fout << "[Task 1]" << endl;
  fout << answer << endl;

  return;
}

/*
    [Task 2] Choose the TIGHT bound of the following maxSubarraySum function

    *maxSubarraySum*
        Input
        - int n: the length of the input array (n >=1)
        - int* A: an array with n >=1 integers
        Output
        - int: maximum value of sum of subarray of A. Define subarray as { A[i],
   A[i+1], …, A[j] } for all integer i <= j < n. int maxSubarraySum(int n, int
   *A) { int max_sum = 0; for (int i = 0; i < n; i++) { for (int j = i; j < n;
   j++) { int cur_sum = 0; for (int k = i; k <= j; k++) { cur_sum += A[k];
                    }
                    if (cur_sum > max_sum){
                        max_sum = cur_sum;
                    }
                }
            }
            return max_sum;
        }

    Choices
        1: O( n log(n) )
        2: O( n )
        3: O( n^2 )
        4: O( n^3 )
*/
void task_2(ofstream &fout) {
  int answer = 4; // TODO: Change to your answer

  fout << "[Task 2]" << endl;
  fout << answer << endl;

  return;
}

/*
    [Task 3] List

    Description:
        Implement a function that can insert or replace an integer in the list.
        A user can insert or replace an element at the specific index.
        If the specified index is out of range of the given list, print “error”.

    Input:
        Sequence of commands, which is one of the following
        - (‘insert’,i): insert i into the i-th index in the list. i-th index
   indicates zero-based index.
        - (‘replace_at’,index): replace an element at the index to 0. index
   indicates zero-based index.

    Output:
        - An array after insertion/deletion in a string separated with the
   spacebar
        - “error” if the index is out of range
*/
void task_3(ofstream &fout, InstructionSequence *instr_seq) {
  string answer;

  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  int myList[100000] = {0};
  int num = 0;

  for (int i = 0; i < instr_seq->length; i++) {
    string command = instr_seq->instructions[i].command;
    int value = instr_seq->instructions[i].value;
    if (command.compare("insert") == 0) {
      /* TODO: Implement */
      if (value > num) {
        answer = "error";
      } else {
        for (int j = num - 1; j >= value; j--) {
          myList[j + 1] = myList[j];
        }
        myList[value] = value;
      }
      num++;
    } else if (command.compare("replace_at") == 0) {
      /* TODO: Implement */
      if (value > num) {
        answer = "error";
      }
      myList[value] = 0;

    } else {
      cerr << "Invalid command" << endl;
      exit(-1);
    }
  }

  if(answer.compare("error") != 0){
    answer = char(myList[0] + 48);
    for (int k = 1; k < num; k++) {
    answer = answer + " " + char(myList[k] + 48);
    }
  }
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////

  fout << "[Task 3]" << endl;
  fout << answer << endl;
}

/*
    [Task 4] Stack

    Description:
        Implement a function that prints the top values of the stack when “top”
   operation is called after the sequence of “push” or “pop” operations. If the
   “top” operation is called for an empty stack, print “-1”, If “pop” operation
   is called for an empty stack, print “error” and the program terminates. The
   stack can contain positive integers.

    Input:
        Sequence of commands, which is one of the following,
        - (‘push’,integer): push integer into the current stack, if integer is
   negative, skip the push step
        - (‘pop’,NULL): pop the top value of the current stack (this operation
   will print nothing)
        - (‘top’,NULL): print the top value of the current stack (print ‘-1’ if
   the current stack is empty)

    Output:
        - Expected printed values after processing the whole sequence, in a
   string separated with the spacebar
        - “error” if the pop operation is executed on an empty stack, and then
   the program terminates.

*/
void task_4(ofstream &fout, InstructionSequence *instr_seq) {
  string answer;

  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  int arr[100000] = {0};
  int num = 0, k, j = 0; // j는 pop할 때 첫 번째 출력인지 여부 판단

  for (int i = 0; i < instr_seq->length; i++) {
    string command = instr_seq->instructions[i].command;
    int value = instr_seq->instructions[i].value;
    if (command.compare("push") == 0) {
      /* TODO: Implement */
      if (value < 0)
        continue;
      for (k = num - 1; k >= 0; k--) {
        arr[k + 1] = arr[k];
      }
      arr[num] = value;
      num++;

    } else if (command.compare("pop") == 0) {
      /* TODO: Implement */
      if (num == 0) {
        answer = "error";
        break;
      }
      for (k = 1; k <= num - 1; k++) {
        arr[k - 1] = arr[k];
      }
      num--;

    } else if (command.compare("top") == 0) {
      /* TODO: Implement */
      if (j == 0) {
        if (num == 0) {
          answer = answer + "-1";
        } else {
          answer = answer + char(arr[0] + 48);
        }
        j++;
      } else {
        if (num == 0) {
          answer = answer + " " + "-1";
        } else {
          answer = answer + " " + char(arr[0] + 48);
        }
      }

    } else {
      cerr << "Invalid command" << endl;
      exit(-1);
    }
  }
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////

  fout << "[Task 4]" << endl;
  fout << answer << endl;
}

/*
    [Task 5] Circular Queue

    Desctiption:
        Implement a function that shows the values in a circular queue with a
   Boolean indicator. If the queue after the operations is empty, print “empty”.
        If “enqueue” operates on a full queue or if “dequeue” operates on an
   empty queue, print “error”. The maximum number of elements (n) in the queue
   is four.

    Input:
        Sequence of commands, which is one of the following,
        - (‘enqueue’,integer): enqueue integer into the current queue
        - (‘dequeue’,NULL): dequeue from the current queue

    Output
        - Values in the circular queue (mod size n = 4), from the front to the
   rear. String separated with the spacebar, empty memory shows NULL
        - “empty” if the queue is empty when the operations are terminated
   normally
        - “error” if the “dequeue” operation is executed on an empty queue or if
   the “enqueue” operation is executed on a full queue
*/
void task_5(ofstream &fout, InstructionSequence *instr_seq) {
  string answer;
  int queue_size = 4;
  int queue[4] = {};
  bool is_empty = true;

  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  int cnt = 0;
  int front = 0, rear = -1;

  for (int i = 0; i < instr_seq->length; i++) {
    string command = instr_seq->instructions[i].command;
    int value = instr_seq->instructions[i].value;
    if (command.compare("enqueue") == 0) {
      /* TODO: Implement */
      if (cnt == 4) {
        cnt = -1;
        break;
      }
      rear++;
      cnt++;
      queue[(rear) % 4] = value;

    } else if (command.compare("dequeue") == 0) {
      /* TODO: Implement */
      if (cnt == 0) {
        cnt = -1;
        break;
      }
      queue[(front) % 4] = 0; // NULL
      cnt--;
      front++;

    } else {
      cerr << "Invalid command" << endl;
      exit(-1);
    }
  }

  if (cnt == 0)
    answer = "empty";
  else if (cnt == -1)
    answer = "error";
  else {
    answer = char(queue[(front) % 4] + 48);
    front++;
    for (int j = front; front <= rear; front++) {
      answer = answer + " " + char(queue[(front) % 4] + 48);
    }
  }
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////

  fout << "[Task 5]" << endl;
  fout << answer << endl;
}

/*
    [Task 6] Double-Ended Queue

    Description:
        Implement a function that shows the values in a double-ended queue
   (deque) whose maximum number of elements is four. If “insert” is called for
   an already full deque or the “erase” operation is called for an empty deque,
   there should be no changes to the queue.

    Input:
        Sequence of commands, which is one of the following,
        - (‘insert_front’,integer): insert integer at the beginning of the
   deque.
        - (‘insert_back’,integer): insert integer at the end of the deque.
        - (‘erase_front’,NULL): erase the first element the queue.
        - (‘erase_back’,NULL): erase the last element the queue.

    Output
        - Values in the queue from the beggining to the end, in a string
   separated with spacebar
        - “empty” if the queue is empty
*/
void task_6(ofstream &fout, InstructionSequence *instr_seq) {
  string answer;

  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  int arr[4];
  int num = 0, j;

  for (int i = 0; i < instr_seq->length; i++) {
    string command = instr_seq->instructions[i].command;
    int value = instr_seq->instructions[i].value;
    if (command.compare("insert_front") == 0) {
      /* TODO: Implement */
      if (num == 4)
        continue;
      for (j = num - 1; j >= 0; j--) {
        arr[j + 1] = arr[j];
      }
      arr[0] = value;
      num++;

    } else if (command.compare("insert_back") == 0) {
      /* TODO: Implement */
      if (num == 4)
        continue;
      arr[num] = value;
      num++;

    } else if (command.compare("erase_front") == 0) {
      /* TODO: Implement */
      if (num == 0)
        continue;
      for (j = 1; j < num; j++) {
        arr[j - 1] = arr[j];
      }
      num--;

    } else if (command.compare("erase_back") == 0) {
      /* TODO: Implement */
      if (num == 0)
        continue;
      num--;

    } else {
      cerr << "Invalid command" << endl;
      exit(-1);
    }
  }

  answer = char(arr[0] + 48);
  for (j = 1; j < num; j++) {
    answer = answer + " " + char(arr[j] + 48);
  }

  if (num == 0)
    answer = "empty";
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////

  fout << "[Task 6]" << endl;
  fout << answer << endl;
}

int main(int argc, char **argv) {
  string filename = "submit.txt";
  int task_num = 0;
  InstructionSequence *instr_seq;

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
      instr_seq = ParseInstructions(argv[2]);
    } catch (const char *e) {
      cerr << e << endl;
      return -1;
    }
  }

  // Running the task(s)
  switch (task_num) {
  case 1:
    task_1(fout);
    break;
  case 2:
    task_2(fout);
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
    task_1(fout);
    task_2(fout);

    InstructionSequence *instr_seq_3;
    instr_seq_3 = ParseInstructions(TASK_3_DEFAULT_ARGUMENT);
    task_3(fout, instr_seq_3);

    InstructionSequence *instr_seq_4;
    instr_seq_4 = ParseInstructions(TASK_4_DEFAULT_ARGUMENT);
    task_4(fout, instr_seq_4);

    InstructionSequence *instr_seq_5;
    instr_seq_5 = ParseInstructions(TASK_5_DEFAULT_ARGUMENT);
    task_5(fout, instr_seq_5);

    InstructionSequence *instr_seq_6;
    instr_seq_6 = ParseInstructions(TASK_6_DEFAULT_ARGUMENT);
    task_6(fout, instr_seq_6);
    break;
  default:
    cout << "Wrong task number" << endl;
  }

  fout.close();
  return 0;
}
