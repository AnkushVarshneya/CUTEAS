//////////////////////////////////////////////////////////////////////////
// COURSEQUEUE
// Implements a singly linked list of all courses

#include "CourseQueue.h"

//////////////////////////////////////////////////////////////////////////
// Default constructor
CourseQueue::CourseQueue() 
: head(0)
{ 
  //cout << "CONSTRUCT CourseQueue" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Copy Constructor
CourseQueue::CourseQueue(CourseQueue& oldQueue)
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
 //cout << "COPY CONSTRUCT CourseQueue" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Destructor
CourseQueue::~CourseQueue() {
  //cout << "DESTRUCT CourseQueue" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Adds an item to the back of the queue
void CourseQueue::pushBack(Course* newCourse) {
  Node* tmpNode = new Node;
  tmpNode->data = newCourse;
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
bool CourseQueue::popFront() {
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
CourseQueue::Node* CourseQueue::front(){
  return head;
}


//////////////////////////////////////////////////////////////////////////
// Removes a Course from the queue with a given name
// Returns true if removed; false if not removed
bool CourseQueue::remove(string crs) {
  Node* currNode = head;
  Node* prevNode = 0;

  if (currNode == 0) { // empty list
    cout << "The queue is empty" << endl;
    return false;
  }

  while (currNode->next != 0) {
    if (currNode->data->getName() == crs) { // match found
      if (prevNode == 0)  // First element
        head = currNode->next;
      else               // Middle element
        prevNode->next = currNode->next;
      delete currNode->data->getUGradApps();
      delete currNode->data->getGradApps();
      delete currNode->data;
      delete currNode;
      return true;
    }
    prevNode = currNode;
    currNode = currNode->next;
  }

  // Last element
  if (currNode->data->getName() == crs) {
    if (prevNode == 0)
      head = 0;
    else
      prevNode->next = 0;
    delete currNode->data->getUGradApps();
    delete currNode->data->getGradApps();
    delete currNode->data;
    delete currNode;
    return true;
  }

  // crs is not in list
  return false;
}

//////////////////////////////////////////////////////////////////////////
// Tests whether queue is empty or not
bool CourseQueue::empty(){
  if (head == 0)
    return true;
  return false;
}

//////////////////////////////////////////////////////////////////////////
// Clears the queue
void CourseQueue::clear(){
  Node *currNode, *nextNode;

  if (head == 0)
    return;

  currNode = head;

  while (currNode != 0) {
    nextNode = currNode->next;
    delete currNode->data->getUGradApps();
    delete currNode->data->getGradApps();
    delete currNode->data;
    delete currNode;
    currNode = nextNode;
  }

  head = 0;
}

//////////////////////////////////////////////////////////////////////////
// Clears the copy of a queue (only deletes nodes)
void CourseQueue::clearCopy(){
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
int CourseQueue::size() const {
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
void CourseQueue::print() const {
  Node* currNode = head;

  cout << endl << "ALL COURSES:" <<endl;
  while (currNode != 0) {
    cout << "  " << currNode->data->getName() << endl;
    currNode = currNode->next;
  }
}

//////////////////////////////////////////////////////////////////////////
// Overloaded subscript operator that returns a course pointer 
//   at index given
Course* CourseQueue::operator[](int i) const {
  int  count     = 0;
  Node *currNode = head;

  while(currNode != 0){
    if (count == i)
      return currNode->data;
    
    currNode = currNode->next;
    count++;
  }
  return 0;
}

//////////////////////////////////////////////////////////////////////////
// Overloaded += operator that adds course given to this queue
CourseQueue& CourseQueue::operator+=(Course* crs) {
  pushBack(crs);
  return *this;
} 

//////////////////////////////////////////////////////////////////////////
// Overloaded += operator that adds elements of queue given to this queue
CourseQueue& CourseQueue::operator+=(CourseQueue& crsQueue) {
  Node *currNode = crsQueue.head;

  while (currNode != 0) {
    (*this) += currNode->data;
    currNode = currNode->next;
  }
  
  return *this;
}

//////////////////////////////////////////////////////////////////////////
// Overloaded + operator that returns a new queue of all elements of this 
//   queue as well as the course pointer given
CourseQueue CourseQueue::operator+(Course* crs) {
  CourseQueue newQueue = *this;
  newQueue += crs;

  return newQueue;
}

//////////////////////////////////////////////////////////////////////////
// Overloaded + operator that returns a new queue of all elements of this 
//   queue as well as all the elements of the queue given
CourseQueue CourseQueue::operator+(CourseQueue& crsQueue) {
  CourseQueue newQueue = (*this);
  newQueue += crsQueue;

  return newQueue;
}

//////////////////////////////////////////////////////////////////////////
// Overloaded -= operator that removes the course given from this queue
CourseQueue& CourseQueue::operator-=(Course* crs){
  remove(crs->getName());
  return *this;
} 

//////////////////////////////////////////////////////////////////////////
// Overloaded -= operator that removes all elements of queue given from this queue
CourseQueue& CourseQueue::operator-=(CourseQueue& crsQueue) {
  Node *currNode = crsQueue.head;
  
  // Finding a crs in empty list
  if (head == 0) {
    cout << "There are no nodes to remove" << endl;
    return *this;
  }

  while (currNode != 0) {
    (*this) -= currNode->data;
    currNode = currNode->next;
  }
  
  return *this;
}

//////////////////////////////////////////////////////////////////////////
// Overloaded - operator that returns a new queue of all elements of this 
//   queue excluding the course pointer given
CourseQueue CourseQueue::operator-(Course* crs) {
  CourseQueue newQueue;

  Node *currNode = head;

  while (currNode != 0) {
    if (currNode->data->getName() != crs->getName())
      newQueue += currNode-> data;
    currNode = currNode->next;
  }

  return newQueue;
}

//////////////////////////////////////////////////////////////////////////
// Overloaded - operator that returns a new queue of all elements of this 
//   queue excluding all the elements of the queue given
CourseQueue CourseQueue::operator-(CourseQueue& crsQueue) {
  CourseQueue newQueue;

  bool same = false;

  Node *currNode = head,  *crsNode  = crsQueue.head;
  while (currNode !=0) { 
    crsNode = crsQueue.head;
    same = false; 
    while(crsNode != 0){
      if (crsNode->data->getName() == currNode->data->getName()) {
         same = true; 
         break;   
      }
      crsNode = crsNode->next; 
    }
    if (same == false)
       newQueue += currNode-> data;
    currNode = currNode->next;
  }

  return newQueue; 
}

//////////////////////////////////////////////////////////////////////////
// Overloaded ! operator that clears the current queue 
void CourseQueue::operator!() {
  clear();
}

//////////////////////////////////////////////////////////////////////////
// Overloaded << operator that prints out the elements of the queue
ostream& operator<<(ostream& out, CourseQueue& crsQueue) {
  int index = 0;
  Course* ptr = crsQueue[index++];
  
  out << "[";

  while(ptr) {
    out << " " << *ptr;
    ptr = crsQueue[index++];
  }
  out << " ]" << endl;

  return out;
}

