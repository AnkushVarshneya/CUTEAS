//////////////////////////////////////////////////////////////////////////
// GRADUATE APPLICATION QUEUE
// Implements a singly linked list of all graduate applications


#include "GradApp.h"
#include "GradAppQueue.h"
#include "Course.h"
#include "TACourseQueue.h"
#include "WorkExpQueue.h"

//////////////////////////////////////////////////////////////////////////
// Default constructor
GradAppQueue::GradAppQueue() 
: head(0)
{ 
  //cout << "CONSTRUCT GradAppQueue" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Copy Constructor
GradAppQueue::GradAppQueue(GradAppQueue& oldQueue) 
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
  //cout << "COPY CONSTRUCT GradAppQueue" << endl;
  
}

//////////////////////////////////////////////////////////////////////////
// Destructor
GradAppQueue::~GradAppQueue() {
  //cout << "DESTRUCT GradAppQueue" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Adds an item to the back of the queue
void GradAppQueue::pushBack(GradApp* newApp) {
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
bool GradAppQueue::popFront() {
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
GradAppQueue::Node* GradAppQueue::front(){
  return head;
}

//////////////////////////////////////////////////////////////////////////
// Tests whether queue is empty or not
bool GradAppQueue::empty(){
  if (head == 0)
    return true;
  return false;
}

//////////////////////////////////////////////////////////////////////////
// Clears the queue
void GradAppQueue::clear(){
  Node *currNode, *nextNode;

  if (head == 0)
    return;

  currNode = head;

  while (currNode != 0) {
    nextNode = currNode->next;
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
void GradAppQueue::clearCopy(){
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
int GradAppQueue::size() const {
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
void GradAppQueue::print() const {
  Node* currNode = head;

  cout << endl << endl << "ALL GRAD APPLICATIONS:" << endl;
  
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
// Sorts queue by research in ABC order
void GradAppQueue::sortByResearch() {
  Node *currNode, *nextNode, *prevNode, *tmpNode; 
  GradApp* temp;

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
      if (nextNode->data->getGrad()->getResearch() < currNode->data->getGrad()->getResearch()) {
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
bool GradAppQueue::isInQueue(string n) const{
  Node* currNode =  head;

  if (currNode == 0)
    return false;

 // Iterate through linked list
  while(currNode != 0){
    if(currNode->data->getGrad()->getStuNum() == n) {
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
string GradAppQueue::isAppNumInQueue(int n) {
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
      return currNode->data->getGrad()->getStuNum();
    }
    currNode = currNode->next;
  }

  return "0";
}

//////////////////////////////////////////////////////////////////////////
// Changes status of all other apps applying to same course to CLOSED
void GradAppQueue::closeOtherGrad(string stuNum, int appNum) {
  Node* currNode =  head;
  if (currNode == 0)
    return;

 // Iterate through linked list
  while(currNode != 0){
    if(currNode->data->getGrad()->getStuNum() == stuNum) {
      if(currNode->data->getAppNum() != appNum)
        currNode->data->operator-();
    }
    currNode = currNode->next;
  }
  return; 
} 

//////////////////////////////////////////////////////////////////////////
// Returns a pointer to the application with the given application number
GradApp* GradAppQueue::getApp(int n) const{
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
