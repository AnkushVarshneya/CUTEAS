//////////////////////////////////////////////////////////////////////////
// UNDERGRADUATE APPLICATION QUEUE
// Implements a singly linked list of all undergraduate applications

#include "UGradAppQueue.h"
#include "UGradApp.h"
#include "TACourseQueue.h"
#include "WorkExpQueue.h"

//////////////////////////////////////////////////////////////////////////
// Default constructor
UGradAppQueue::UGradAppQueue() 
: head(0)
{ 
  //cout << "CONSTRUCT UGradAppQueue" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Copy Constructor
UGradAppQueue::UGradAppQueue(UGradAppQueue& oldQueue) 
: head(0)
{

  Node  *currNode = oldQueue.head,
        *prevNode = 0;

  while (currNode != 0){
    Node* newNode = new Node;
    newNode->data = currNode->data;
    newNode->next = 0;

    if (!head) {
      head     = newNode;
      prevNode = head;
    } else {
        prevNode->next = newNode;
        prevNode       = newNode;
    }
    currNode = currNode->next;
  }
  //cout << "COPY CONSTRUCT UGradAppQueue" << endl;
  
}

//////////////////////////////////////////////////////////////////////////
// Destructor
UGradAppQueue::~UGradAppQueue() {
  //cout << "DESTRUCT UGradAppQueue" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Adds an item to the back of the queue
void UGradAppQueue::pushBack(UGradApp* newApp) {
  Node* tmpNode = new Node;
  tmpNode->data = newApp;
  tmpNode->next = 0;

  Node *currNode = head;

  // Adding to an empty list
  if (head == 0){
    head = tmpNode;
    return;
  }
 // Iterate all the way to the end of the linked list
  while(currNode != 0){
    if(currNode->next == 0)
       break;
    currNode = currNode->next;
  }

  currNode->next = tmpNode;
}

//////////////////////////////////////////////////////////////////////////
// Removes first item in the queue
bool UGradAppQueue::popFront() {
  Node *currNode; 

  if(head == 0)
    return 1;

  currNode = head;
  head = currNode->next;
  delete currNode;

  return 0;
}

//////////////////////////////////////////////////////////////////////////
// Return the first item in the queue
UGradAppQueue::Node* UGradAppQueue::front(){
  return head;
}

//////////////////////////////////////////////////////////////////////////
// Tests whether queue is empty or not
bool UGradAppQueue::empty(){
  if (head == 0)
    return true;
  return false;
}

//////////////////////////////////////////////////////////////////////////
// Clears the queue
void UGradAppQueue::clear(){
  Node *currNode, *nextNode;

  if (head == 0)
    return;

  currNode = head;

  while (currNode != 0) {
    nextNode = currNode->next;
    delete currNode->data->getTakenCrsQueue();
    delete currNode->data->getTACrsQueue();
    delete currNode->data->getWorkExpQueue();
    delete currNode->data;
    delete currNode;
    currNode = nextNode;
  }

  head = 0;
}

//////////////////////////////////////////////////////////////////////////
// Clears the copy of a queue
void UGradAppQueue::clearCopy(){
  Node *currNode, *nextNode;

  if (head == 0)
    return;

  currNode = head;

  while (currNode != 0) {
    nextNode = currNode->next;
    delete currNode;
    currNode = nextNode;
  }
  head = 0;
}

//////////////////////////////////////////////////////////////////////////
// Returns the size of the queue
int UGradAppQueue::size() const {
  Node* currNode = head;
  int   count = 0; 

  while (currNode != 0) {
    count++;
    currNode = currNode->next;
  }
  return count;
}

//////////////////////////////////////////////////////////////////////////
// Prints list of courses to std::cout
void UGradAppQueue::print() const {
  Node* currNode = head;

  cout << endl << endl << "ALL UNDERGRAD APPLICATIONS:" <<endl;
  
  if (currNode == 0) {
    cout << "  There are no applications" << endl;
    return;
  }

  while (currNode != 0) {
    cout << "  App #"    << currNode->data->getAppNum() << ", "
                         << currNode->data->getCourse()->getName() <<
            ", Status: " << currNode->data->getStatusString(currNode->data->getStatus()) << endl;
    currNode = currNode->next;
  }
}

//////////////////////////////////////////////////////////////////////////
// Sorts queue by major gpa
void UGradAppQueue::sortByMGPA() {
  Node *currNode, *nextNode, *prevNode, *tmpNode; 
  UGradApp* temp;

  if (head == 0) {
    cout << "There are no nodes to sort" << endl;
    return;
  }
  // If there's only one element in the list
  if (head->next == 0) 
    return;

  prevNode = 0;
  currNode = head;
  nextNode = currNode->next;

  bool swap = true;
  while(swap) {  
    swap = false;
    while(currNode !=0 && nextNode !=0){
      if (nextNode->data->getUndergrad()->getMGPA() > currNode->data->getUndergrad()->getMGPA()) {
        if(prevNode == 0){
          tmpNode = currNode;
          head = nextNode;
          tmpNode->next = nextNode->next;
          nextNode->next = tmpNode;
        }
        else {
          tmpNode = currNode;
          prevNode->next = nextNode;
          tmpNode->next = nextNode->next;
          nextNode->next = tmpNode;
        }
        swap = true;
      }
      prevNode = currNode;
      currNode = nextNode;
      nextNode = nextNode->next;
    }
    prevNode = 0;
    currNode = head;
    nextNode = currNode->next;
  } 
}

//////////////////////////////////////////////////////////////////////////
// Checks if there is an application from a given student number
// Returns true if there exists an application; false if there is none
bool UGradAppQueue::isInQueue(string n) const{
  Node* currNode =  head;

  if (currNode == 0)
    return false;

 // Iterate through linked list
  while(currNode != 0){
    if(currNode->data->getUndergrad()->getStuNum() == n) {
      cout << n << " has an existing application" << endl;
      return true;
    }
    currNode = currNode->next;
  }

  return false;
}

//////////////////////////////////////////////////////////////////////////
// Checks if there is an application from a given application num
// Returns status if assigned or closed, else student number if pending 
string UGradAppQueue::isAppNumInQueue(int n) {
  Node* currNode =  head;

  if (currNode == 0)
    return "0";

  // Iterate through linked list
  while(currNode != 0){
    if(currNode->data->getAppNum() == n) {
      if(currNode->data->getStatus() == ASSIGNED)
        return "ASSIGNED";
      if(currNode->data->getStatus() == CLOSED)
        return "CLOSED";
      return currNode->data->getUndergrad()->getStuNum();
    }
    currNode = currNode->next;
  }

  return "0";
}


//////////////////////////////////////////////////////////////////////////
// Changes status of all other apps applying to same course to CLOSED
void UGradAppQueue::closeOtherUGrad(string stuNum, int appNum) {
  Node* currNode =  head;

  if (currNode == 0)
    return;

 // Iterate through linked list
  while(currNode != 0){
    if(currNode->data->getUndergrad()->getStuNum() == stuNum) {
      if( currNode->data->getAppNum() != appNum)
        currNode->data->operator-();
    }
    currNode = currNode->next;
  }
  return; 
} 


//////////////////////////////////////////////////////////////////////////
// Returns a pointer to the application with the given application number
UGradApp* UGradAppQueue::getApp(int n) const{
  Node* currNode =  head;

  if (currNode == 0)
    return 0;

 // Iterate through linked list
  while(currNode != 0){
    if(currNode->data->getAppNum() == n) {
      return currNode->data;
    }
    currNode = currNode->next;
  }

  return 0;
}
