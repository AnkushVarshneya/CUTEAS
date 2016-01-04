#include "Types.h"
#include "WorkExp.h"
#include <fstream>

void testing_not(string[]);
void testing_subscript(string[]);
void testing_plus_equals_ptr(string[]);
void testing_plus_equals_queue(string[]);
void testing_plus_ptr(string[]);
void testing_plus_queue(string[]);
void testing_minus_equals_ptr(string[]);
void testing_minus_equals_queue(string[]);
void testing_minus_ptr(string[]);
void testing_minus_queue(string[]);


int main() {
  string   jobs[30];
  int      count=0, i;
  ifstream infile("jobs.txt", ios::in);

  if (!infile)
    cout << "Could not open file" << endl;
  while (!infile.eof()) {
    getline(infile, jobs[count]);
    count++;
  }

  cout << "********* TEST PROGRAM *********" << endl;

  // Testing the ! 
  testing_not(jobs);


  // Testing the [] subscript 
  testing_subscript(jobs);


  // Testing the += with WorkExp pointer passed in
  testing_plus_equals_ptr(jobs);

  // Testing the += with Queue<WorkExp> passed in
  testing_plus_equals_queue(jobs);


  // Testing the + with WorkExp pointer passed in
  testing_plus_ptr(jobs);

  // Testing the + with Queue<WorkExp> passed in
  testing_plus_queue(jobs);


  // Testing the -= with WorkExp pointer passed in
  testing_minus_equals_ptr(jobs);

  // Testing the -= with Queue<WorkExp> passed in
  testing_minus_equals_queue(jobs);


  // Testing the - with WorkExp pointer passed in
  testing_minus_ptr(jobs);

  // Testing the - with WorkExp queue passed in
  testing_minus_queue(jobs);


  return 0;
}

//////////////////////////////////////////////////////////////////////////
// Tests the ! which empties the queue
void testing_not(string jobs[]) {
  Queue<WorkExp> queue1;

  cout << endl << "----- Testing the ! which empties queue -----" << endl;

  for (int i=0; i<5; i++) {
    WorkExp* newWorkExp = new WorkExp(0,jobs[i]);
    queue1 += newWorkExp;
  }

  cout << "Queue: " << queue1; 
  !queue1;
  cout << "Queue after ! : " << queue1 << endl; 
}

//////////////////////////////////////////////////////////////////////////
// Tests the [] which returns the WorkExp pointer at index specified
void testing_subscript(string jobs[]) {
  Queue<WorkExp> queue1;

  cout << endl << "----- Testing the [] which returns the WorkExp pointer at index -----";
  cout << endl << "----- CASE: In bounds index -----" << endl;

  for (int i=0; i<5; i++) {
    WorkExp* newWorkExp = new WorkExp(0,jobs[i]);
    queue1 += newWorkExp;
  }

  cout << "Queue: " << queue1; 
  cout << "Element at position 2  : " << queue1[2]->getResp() << endl;
  cout << "Element at position 4  : " << queue1[4]->getResp() << endl;


  cout << endl << "----- CASE: Invalid index -----" << endl;
  cout << "Element at position -1  : " << queue1[-1] << endl;

  cout << endl << "----- CASE: Out of bounds index -----" << endl;
  cout << "Element at position 8  : " << queue1[8] << endl << endl;
  
  !queue1;
}


//////////////////////////////////////////////////////////////////////////
// Tests the += with WorkExp pointer passed in
void testing_plus_equals_ptr(string jobs[]) {
  Queue<WorkExp> queue1;

  cout << endl << "----- Testing the += for a WorkExp pointer -----" << endl;

  for (int i=0; i<5; i++) {
    WorkExp* newWorkExp = new WorkExp(0,jobs[i]);
    queue1 += newWorkExp;
  }

  cout << "Queue: " << queue1 << endl; 
  !queue1;
}


//////////////////////////////////////////////////////////////////////////
// Tests the += with WorkExp queue passed in
void testing_plus_equals_queue(string jobs[]) {
  Queue<WorkExp> queue1, queue2;

  cout << endl << "----- Testing the += for a new queue -----" << endl;

  for (int i=0; i<5; i++) {
    WorkExp* newWorkExp  = new WorkExp(0,jobs[i]);
    WorkExp* newWorkExp2 = new WorkExp(0,jobs[i+2]);
    queue1 += newWorkExp;
    queue2 += newWorkExp2;
  }

  cout << "Queue 1: " << queue1; 
  cout << "Queue 2: " << queue2;

  queue1 += queue2;

  cout << "Queue 1 after adding Queue 2: " << queue1;
  !queue1;
  queue2.clearCopy();

  cout << endl << "----- Testing the += for a new queue *CASCADING* -----" << endl;
  Queue<WorkExp> q1, q2, q3;
  for (int i=0; i<5; i++) {
    WorkExp* newWorkExp  = new WorkExp(0,jobs[i]);
    WorkExp* newWorkExp2 = new WorkExp(0,jobs[i+2]);
    WorkExp* newWorkExp3 = new WorkExp(0,jobs[i+3]);
    q1 += newWorkExp;
    q2 += newWorkExp2;
    q3 += newWorkExp3;
  }

  cout << "Queue 1: " << q1; 
  cout << "Queue 2: " << q2;
  cout << "Queue 3: " << q3;
  
  q1 += q2 += q3;

  cout << "Queue 1 after cascading: " << q1;
  cout << "Queue 2 after cascading: " << q2;
  cout << "Queue 3 after cascading: " << q3 << endl;

  !q1;
  q2.clearCopy();
  q3.clearCopy();
}


//////////////////////////////////////////////////////////////////////////
// Tests the + with WorkExp pointer passed in
void testing_plus_ptr(string jobs[]) {
  Queue<WorkExp> queue1;

  cout << endl << "----- Testing the + for a WorkExp pointer -----" << endl;

  for (int i=0; i<5; i++) {
    WorkExp* newWorkExp = new WorkExp(0,jobs[i]);
    queue1 += newWorkExp;
  }

  cout << "Original queue: " << queue1; 
  cout << "Adding WorkExp: " << jobs[7];
  WorkExp* newWorkExp = new WorkExp(0,jobs[7]);
  Queue<WorkExp> newQueue;

  newQueue = queue1 + newWorkExp;

  cout << endl << "New queue: " << newQueue;

  !newQueue;
  queue1.clearCopy();


  cout << endl << "----- Testing the + for a WorkExp pointer *CASCADING* -----" << endl;

  for (int i=0; i<5; i++) {
    WorkExp* newWorkExp = new WorkExp(0,jobs[i]);
    queue1 += newWorkExp;
  }
  cout << "Queue 1: " << queue1; 

  cout << "Adding WorkExp: " << jobs[7] << ", then adding WorkExp: " << jobs[6] << endl;
  WorkExp* newWorkExp2 = new WorkExp(0,jobs[7]);
  WorkExp* newWorkExp3 = new WorkExp(0,jobs[6]);

  //////////////////////// ** MEMORY LEAK ** /////////////////////////////////
  newQueue = queue1 + newWorkExp2 + newWorkExp3;  
  ////////////////////////////////////////////////////////////////////////////

  cout << "New queue after cascading: " << newQueue << endl;

  !newQueue;
  queue1.clearCopy();
}


//////////////////////////////////////////////////////////////////////////
// Tests the + with WorkExp queue passed in
void testing_plus_queue(string jobs[]) {
  Queue<WorkExp> queue1, queue2;

  cout << endl << "----- Testing the + for a new queue -----" << endl;

  for (int i=0; i<5; i++) {
    WorkExp* newWorkExp  = new WorkExp(0,jobs[i]);
    WorkExp* newWorkExp2 = new WorkExp(0,jobs[i+2]);
    queue1 += newWorkExp;
    queue2 += newWorkExp2;
  }

  cout << "Queue 1: " << queue1; 
  cout << "Queue 2: " << queue2;

  Queue<WorkExp> newQueue;
  newQueue = queue1 + queue2;

  cout << "New queue: " << newQueue;
  !newQueue;
  queue1.clearCopy();
  queue2.clearCopy();

  cout << endl << "----- Testing the + for a new queue *CASCADING* -----" << endl;
  Queue<WorkExp> q1, q2, q3;
  for (int i=0; i<5; i++) {
    WorkExp* newWorkExp  = new WorkExp(0,jobs[i]);
    WorkExp* newWorkExp2 = new WorkExp(0,jobs[i+2]);
    WorkExp* newWorkExp3 = new WorkExp(0,jobs[i+3]);
    q1 += newWorkExp;
    q2 += newWorkExp2;
    q3 += newWorkExp3;
  }

  cout << "Queue 1: " << q1; 
  cout << "Queue 2: " << q2;
  cout << "Queue 3: " << q3;


  //////////////////////// ** MEMORY LEAK ** /////////////////////////////////
  newQueue = q1 + q2 + q3; 
  ////////////////////////////////////////////////////////////////////////////

  cout << "New queue after cascading: " << newQueue << endl;

  !newQueue;
  q1.clearCopy();
  q2.clearCopy();
  q3.clearCopy();
}


//////////////////////////////////////////////////////////////////////////
// Tests the -= with WorkExp pointer passed in
void testing_minus_equals_ptr(string jobs[]) {
  Queue<WorkExp> queue1;

  cout << endl << "----- Testing the -= for a WorkExp pointer -----" << endl;

  cout << "----- EMPTY LIST CASE -----" << endl;

  WorkExp* newWorkExp = new WorkExp(0,jobs[0]);
  queue1 -= newWorkExp;
  delete newWorkExp;

  cout << endl << "----- MIDDLE OF LIST CASE -----" << endl;
  for (int i=0; i<4; i++) {
    WorkExp* newWorkExp = new WorkExp(0,jobs[i]);
    queue1 += newWorkExp;
  }

  cout << "Queue: " << queue1; 
  cout << "Removing " << jobs[2] << endl;
  newWorkExp = new WorkExp(0,jobs[2]);
  queue1 -= newWorkExp;

  delete newWorkExp;

  cout << "Queue after: " << queue1;

  cout << endl << "----- FRONT OF LIST CASE -----" << endl;
  cout << "Removing " << jobs[0] << endl;
  newWorkExp = new WorkExp(0,jobs[0]);
  queue1 -= newWorkExp;


  delete newWorkExp;

  cout << "Queue after: " << queue1;

  cout << endl << "----- END OF LIST CASE -----" << endl;
  cout << "Removing " << jobs[3] << endl;
  newWorkExp = new WorkExp(0,jobs[3]);
  queue1 -= newWorkExp;


  delete newWorkExp;

  cout << "Queue after: " << queue1;

  cout << endl << "----- LAST ELEMENT OF LIST CASE -----" << endl;

  cout << "Removing " << jobs[1] << endl;
  newWorkExp = new WorkExp(0,jobs[1]);
  queue1 -= newWorkExp;


  delete newWorkExp;

  cout << "Queue after: " << queue1 << endl;
}


//////////////////////////////////////////////////////////////////////////
// Tests the -= with WorkExp queue passed in
void testing_minus_equals_queue(string jobs[]) {
  Queue<WorkExp> queue1, queue2;

  cout << endl << "----- Testing the -= for a new queue -----";
  cout << endl << "----- CASE: queue1 and queue2 are the same -----" << endl;

  for (int i=0; i<5; i++) {
    WorkExp* newWorkExp  = new WorkExp(0,jobs[i]);
    WorkExp* newWorkExp2 = new WorkExp(0,jobs[i]);
    queue1 += newWorkExp;
    queue2 += newWorkExp2;
  }
  cout << "Queue 1: " << queue1; 
  cout << "Queue 2: " << queue2;

  queue1 -= queue2;

  cout << "Queue 1 after removing Queue 2: " << queue1;
  !queue2;


  cout << endl << "----- CASE: all jobs in queue2 are found in queue1 -----" << endl;

  for (int i=0; i<5; i++) {
    WorkExp* newWorkExp  = new WorkExp(0,jobs[i]);
    queue1 += newWorkExp;
  }
  for (int i=0; i<5; i+=2) {
    WorkExp* newWorkExp  = new WorkExp(0,jobs[i]);
    queue2 += newWorkExp;
  }
  cout << "Queue 1: " << queue1; 
  cout << "Queue 2: " << queue2;

  queue1 -= queue2;

  cout << "Queue 1 after removing Queue 2: " << queue1;
  !queue1;
  !queue2;


  cout << endl << "----- CASE: queue2 has jobs that aren't in queue1 and aren't in order -----" << endl;
  for (int i=0; i<5; i++) {
    WorkExp* newWorkExp  = new WorkExp(0,jobs[i]);
    queue1 += newWorkExp;
  }
  for (int i=0; i<3; i++) {
    WorkExp* newWorkExp = new WorkExp(0,jobs[i+4]);
    queue2 += newWorkExp;
  }
  for (int i=0; i<2; i++) {
    WorkExp* newWorkExp = new WorkExp(0,jobs[i]);
    queue2 += newWorkExp;
  }
  cout << "Queue 1: " << queue1; 
  cout << "Queue 2: " << queue2;

  queue1 -= queue2;

  cout << "Queue 1 after removing Queue 2: " << queue1;
  !queue1;
  !queue2;


  cout << endl << "----- CASE: queue 2 is empty -----" << endl;
  for (int i=0; i<5; i++) {
    WorkExp* newWorkExp  = new WorkExp(0,jobs[i]);
    queue1 += newWorkExp;
  }
  cout << "Queue 1: " << queue1; 
  cout << "Queue 2: " << queue2;

  queue1 -= queue2;

  cout << "Queue 1 after removing Queue 2: " << queue1;
  !queue1;


  cout << endl << "----- CASE: queue 1 is empty -----" << endl;
  for (int i=0; i<5; i++) {
    WorkExp* newWorkExp  = new WorkExp(0,jobs[i]);
    queue2 += newWorkExp;
  }
  cout << "Queue 1: " << queue1; 
  cout << "Queue 2: " << queue2;

  queue1 -= queue2;

  cout << "Queue 1 after removing Queue 2: " << queue1;
  !queue2;


  cout << endl << "----- Testing the -= for a new queue *CASCADING* -----" << endl;
  Queue<WorkExp> q1, q2, q3;
  for (int i=0; i<5; i++) {
    WorkExp* newWorkExp  = new WorkExp(0,jobs[i]);
    WorkExp* newWorkExp2 = new WorkExp(0,jobs[i+2]);
    WorkExp* newWorkExp3 = new WorkExp(0,jobs[i+3]);
    q1 += newWorkExp;
    q2 += newWorkExp2;
    q3 += newWorkExp3;
  }

  cout << "Queue 1: " << q1; 
  cout << "Queue 2: " << q2;
  cout << "Queue 3: " << q3;
  
  q1 -= q2 -= q3;

  cout << "Queue 1 after cascading: " << q1;
  cout << "Queue 2 after cascading: " << q2;
  cout << "Queue 3 after cascading: " << q3 << endl;

  !q1;
  !q2;
  !q3;
}


//////////////////////////////////////////////////////////////////////////
// Tests the - with WorkExp pointer passed in
void testing_minus_ptr(string jobs[]) {
  Queue<WorkExp> queue1;

  cout << endl << "----- Testing the - for a WorkExp pointer -----";
  cout << endl << "----- CASE: empty list -----" << endl;

  cout << "Original queue: " << queue1; 
  cout << "Removing WorkExp: " << jobs[1] << endl;
  WorkExp* newWorkExp = new WorkExp(0,jobs[1]);
  Queue<WorkExp> newQueue;
  newQueue = queue1 - newWorkExp;

  cout << "New queue: " << newQueue;


  delete newWorkExp;


  cout << endl << "----- CASE: middle of the list -----" << endl;

  for (int i=0; i<5; i++) {
    WorkExp* newWorkExp = new WorkExp(0,jobs[i]);
    queue1 += newWorkExp;
  }
  cout << "Original queue: " << queue1; 
  cout << "Removing WorkExp: " << jobs[2];
  newWorkExp = new WorkExp(0,jobs[2]);
  newQueue = queue1 - newWorkExp;

  cout << endl << "New queue: " << newQueue;


  delete newWorkExp;

  newQueue.clearCopy();


  cout << endl << "----- CASE: front of the list -----" << endl;

  cout << "Original queue: " << queue1; 
  cout << "Removing WorkExp: " << jobs[0];
  newWorkExp = new WorkExp(0,jobs[0]);
  newQueue = queue1 - newWorkExp;

  cout << endl << "New queue: " << newQueue;

  delete newWorkExp;

  newQueue.clearCopy();


  cout << endl << "----- CASE: end of the list -----" << endl;

  cout << "Original queue: " << queue1; 
  cout << "Removing WorkExp: " << jobs[4];
  newWorkExp = new WorkExp(0,jobs[4]);
  newQueue = queue1 - newWorkExp;

  cout << endl << "New queue: " << newQueue;

  delete newWorkExp;
  newQueue.clearCopy();


  cout << endl << "----- CASE: element not in list -----" << endl;

  cout << "Original queue: " << queue1; 
  cout << "Removing WorkExp: " << jobs[8];
  newWorkExp = new WorkExp(0,jobs[8]);
  newQueue = queue1 - newWorkExp;

  cout << endl << "New queue: " << newQueue;

  delete newWorkExp;

  newQueue.clearCopy();
  

  cout << endl << "----- CASE: last element of the list -----" << endl;

  !queue1;
  newWorkExp = new WorkExp(0,jobs[0]);
  queue1 += newWorkExp;

  cout << "Original queue: " << queue1; 
  cout << "Removing WorkExp: " << jobs[0];
  newWorkExp = new WorkExp(0,jobs[0]);
  newQueue = queue1 - newWorkExp;

  cout << endl << "New queue: " << newQueue;


  delete newWorkExp;

  newQueue.clearCopy();
  !queue1;


  cout << endl << "----- Testing the - for a WorkExp pointer *CASCADING* -----" << endl;
  Queue<WorkExp> q1;
  for (int i=0; i<5; i++) {
    WorkExp* newWorkExp  = new WorkExp(0,jobs[i]);
    q1 += newWorkExp;
  }
  
  cout << "Queue 1: " << q1; 

  cout << "Removing WorkExp: " << jobs[1] << ", then removing WorkExp: " << jobs[2] << endl;
  WorkExp* newWorkExp2 = new WorkExp(0,jobs[1]);
  WorkExp* newWorkExp3 = new WorkExp(0,jobs[2]);

  //////////////////////// ** MEMORY LEAK ** /////////////////////////////////
  newQueue = q1 - newWorkExp2 - newWorkExp3;  
  ////////////////////////////////////////////////////////////////////////////

  cout << "New queue after cascading: " << newQueue << endl;
 

  delete newWorkExp2;
  delete newWorkExp3;

  !q1;
  newQueue.clearCopy();
}


//////////////////////////////////////////////////////////////////////////
// Tests the - with WorkExp queue passed in
void testing_minus_queue(string jobs[]) {
  Queue<WorkExp> queue1, queue2;

  cout << endl << "----- Testing the - for a new queue -----";
  cout << endl << "----- CASE: queue1 and queue2 are the same -----" << endl;

  for (int i=0; i<5; i++) {
    WorkExp* newWorkExp  = new WorkExp(0,jobs[i]);
    WorkExp* newWorkExp2  = new WorkExp(0,jobs[i]);
    queue1 += newWorkExp;
    queue2 += newWorkExp2;
  }
  cout << "Queue 1: " << queue1; 
  cout << "Queue 2: " << queue2;

  Queue<WorkExp> newQueue;
  newQueue = queue1 - queue2;

  cout << "New queue after removing Queue2 from Queue1 : " << newQueue;
  !queue2;


  cout << endl << "----- CASE: all jobs in queue2 are found in queue1 -----" << endl;

  for (int i=0; i<5; i+=2) {
    WorkExp* newWorkExp  = new WorkExp(0,jobs[i]);
    queue2 += newWorkExp;
  }
  cout << "Queue 1: " << queue1; 
  cout << "Queue 2: " << queue2;

  newQueue = queue1 - queue2;

  cout << "New queue after removing Queue2 from Queue1 : " << newQueue;

  !queue2;
  newQueue.clearCopy();


  cout << endl << "----- CASE: queue2 has jobs that aren't in queue1 and aren't in order -----" << endl;
  for (int i=0; i<3; i++) {
    WorkExp* newWorkExp = new WorkExp(0,jobs[i+4]);
    queue2 += newWorkExp;
  }
  for (int i=0; i<2; i++) {
    WorkExp* newWorkExp = new WorkExp(0,jobs[i]);
    queue2 += newWorkExp;
  }
  cout << "Queue 1: " << queue1; 
  cout << "Queue 2: " << queue2;

  newQueue = queue1 - queue2;

  cout << "New queue after removing Queue2 from Queue1 : " << newQueue;

  !queue2;
  newQueue.clearCopy();


  cout << endl << "----- CASE: queue 2 is empty -----" << endl;

  cout << "Queue 1: " << queue1; 
  cout << "Queue 2: " << queue2;

  newQueue = queue1 - queue2;

  cout << "New queue after removing Queue2 from Queue1 : " << newQueue;

  newQueue.clearCopy();


  cout << endl << "----- CASE: queue 1 is empty -----" << endl;
  !queue1;
  for (int i=0; i<5; i++) {
    WorkExp* newWorkExp  = new WorkExp(0,jobs[i]);
    queue2 += newWorkExp;
  }
  cout << "Queue 1: " << queue1; 
  cout << "Queue 2: " << queue2;

  newQueue = queue1 - queue2;

  cout << "New queue after removing Queue2 from Queue1 : " << newQueue;
  !queue2;


  cout << endl << "----- Testing the - for a new queue *CASCADING* -----" << endl;
  Queue<WorkExp> q1, q2, q3;
  for (int i=0; i<5; i++) {
    WorkExp* newWorkExp  = new WorkExp(0,jobs[i]);
    q1 += newWorkExp;
  }
  for (int i=0; i<8; i+=3) {
    WorkExp* newWorkExp2 = new WorkExp(0,jobs[i]);
    q2 += newWorkExp2;
  }
  for (int i=0; i<10; i+=2) {
    WorkExp* newWorkExp3 = new WorkExp(0,jobs[i]);
    q3 += newWorkExp3;
  }
  cout << "Queue 1: " << q1; 
  cout << "Queue 2: " << q2;
  cout << "Queue 3: " << q3;

  //////////////////////// ** MEMORY LEAK ** /////////////////////////////////
  newQueue = q1 - q2 - q3;   
  ////////////////////////////////////////////////////////////////////////////

  cout << "New queue after cascading: " << newQueue << endl;

  !q1;
  !q2;
  !q3;
  newQueue.clearCopy();
}
