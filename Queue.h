//////////////////////////////////////////////////////////////////////////
// Queue
// Implements a singly linked list of items

#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
using namespace std;
#define MAX_BUF 105
#include <string>

template <class T>
class Queue {
  template <typename V>
  friend ostream& operator<<(ostream&, Queue<V>&);
  friend class SelectCrsUI;
  friend class StuAppFormUI;
  friend class GradAppFormUI;
  friend class CourseInfoUI;
  friend class Manager;
  friend class TakenCourse;
  friend class OneReportUI;
  friend class AllReportsUI;
  friend class TACourse;
  friend class TakenCourseInfoUI;
  friend class TACourseInfoUI;
  friend class SelectEntryUI;
  template <class N>  
  class Node {
    friend class Queue;
    friend class SelectCrsUI;
    friend class StuAppFormUI;
    friend class GradAppFormUI;
    friend class CourseInfoUI;
    friend class Manager;
    friend class TakenCourse;
    friend class OneReportUI;
    friend class AllReportsUI;
    friend class TACourse;
    friend class TakenCourseInfoUI;
    friend class TACourseInfoUI;
	friend class SelectEntryUI;
    private:
      N* data;
      Node*   next;
  };

  public:
    Queue();
    Queue(Queue&);
    ~Queue();
    
	//template <class N>
    Node<T>* 	front();
    void  		pushBack(T*);
    bool  		popFront();
	bool  		remove(T*);
    bool  		empty();
    void  		clear();
    void  		clearCopy();
    int   		size()  const;
    void  		print() const;

    T*      	operator[](int) const;
    Queue<T>& 	operator+=(T*);
    Queue<T>& 	operator+=(Queue&);
    Queue<T>  	operator+ (T*);
    Queue<T>  	operator+ (Queue&);
    Queue<T>& 	operator-=(T*);
    Queue<T>& 	operator-=(Queue&);
    Queue<T>  	operator- (T*);
    Queue<T>  	operator- (Queue&);
    Queue<T>&   operator!();

  private:
    Node<T>* head;
};


//////////////////////////////////////////////////////////////////////////
// Default constructor
template <class T>
Queue<T>::Queue() 
: head(0)
{ 
  //cout << "CONSTRUCT Queue" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Copy Constructor
template <class T>
Queue<T>::Queue(Queue<T>& oldQueue)
: head(0)
{
  Node<T>  *currNode = oldQueue.head,
        *prevNode = 0;

  while (currNode != 0){
    Node<T>* newNode = new Node<T>;
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
 //cout << "COPY CONSTRUCT Queue" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Destructor
template <class T>
Queue<T>::~Queue() {
  //cout << "DESTRUCT Queue" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Adds an item to the back of the queue
template <class T>
void Queue<T>::pushBack(T* newDataNode) {
  Node<T>* tmpNode = new Node<T>;
  tmpNode->data = newDataNode;
  tmpNode->next = 0;
  Node<T> *currNode = head;

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
template <class T>
bool Queue<T>::popFront() {
  Node<T> *currNode; 

  if(head == 0)
    return 1;

  currNode = head;
  head = currNode->next;
  delete currNode;

  return 0;
}

//////////////////////////////////////////////////////////////////////////
// Return the first item in the queue
template <class T>
//template <class N>
Queue<T>::Node<T>* Queue<T>::front(){
  return head;
}


//////////////////////////////////////////////////////////////////////////
// Removes a Course from the queue with a given name
// Returns true if removed; false if not removed
template <class T>
bool Queue<T>::remove(T* item) {
  Node<T>* currNode = head;
  Node<T>* prevNode = 0;

  if (currNode == 0) { // empty list
    cout << "The queue is empty" << endl;
    return false;
  }

  while (currNode->next != 0) {
    if (*(currNode->data) == item) { // match found
      if (prevNode == 0)  // First element
        head = currNode->next;
      else               // Middle element
        prevNode->next = currNode->next;
      delete currNode->data;
      delete currNode;
      return true;
    }
    prevNode = currNode;
    currNode = currNode->next;
  }

  // Last element
  if (*(currNode->data) == item) {
    if (prevNode == 0)
      head = 0;
    else
      prevNode->next = 0;
    delete currNode->data;
    delete currNode;
    return true;
  }

  // crs is not in list
  return false;
}

//////////////////////////////////////////////////////////////////////////
// Tests whether queue is empty or not
template <class T>
bool Queue<T>::empty(){
  if (head == 0)
    return true;
  return false;
}

//////////////////////////////////////////////////////////////////////////
// Clears the queue
template <class T>
void Queue<T>::clear(){
  Node<T> *currNode, *nextNode;

  if (head == 0)
    return;

  currNode = head;

  while (currNode != 0) {
    nextNode = currNode->next;
	if(currNode->data != NULL){
		delete currNode->data;
	}
    delete currNode;
    currNode = nextNode;
  }

  head = 0;
}

//////////////////////////////////////////////////////////////////////////
// Clears the copy of a queue (only deletes nodes)
template <class T>
void Queue<T>::clearCopy(){
  Node<T> *currNode, *nextNode;

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
template <class T>
int Queue<T>::size() const {
  Node<T>* currNode = head;
  int   count = 0; 

  while (currNode != 0) {
    count++;
    currNode = currNode->next;
  }
  return count;
}

//////////////////////////////////////////////////////////////////////////
// Prints list of items to std::cout
template <class T>
void Queue<T>::print() const {
  Node<T>* currNode = head;

  cout << endl << " " <<endl;
  while (currNode != 0) {
    currNode->data->print();
    currNode = currNode->next;
  }
}

//////////////////////////////////////////////////////////////////////////
// Overloaded subscript operator that returns a course pointer 
//   at index given
template <class T>
T* Queue<T>::operator[](int i) const {
  int  count     = 0;
  Node<T> *currNode = head;

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
template <class T>
Queue<T>& Queue<T>::operator+=(T* aNodeData) {
  pushBack(aNodeData);
  return *this;
} 

//////////////////////////////////////////////////////////////////////////
// Overloaded += operator that adds elements of queue given to this queue
template <class T>
Queue<T>& Queue<T>::operator+=(Queue<T>& crsQueue) {
  Node<T> *currNode = crsQueue.head;

  while (currNode != 0) {
    (*this) += currNode->data;
    currNode = currNode->next;
  }
  
  return *this;
}

//////////////////////////////////////////////////////////////////////////
// Overloaded + operator that returns a new queue of all elements of this 
//   queue as well as the course pointer given
template <class T>
Queue<T> Queue<T>::operator+(T* aNodeData) {
  Queue<T> newQueue = *this;
  newQueue += aNodeData;
  
  return newQueue;
}

//////////////////////////////////////////////////////////////////////////
// Overloaded + operator that returns a new queue of all elements of this 
//   queue as well as all the elements of the queue given
template <class T>
Queue<T> Queue<T>::operator+(Queue<T>& crsQueue) {
  Queue<T> newQueue = (*this);
  newQueue += crsQueue;

  return newQueue;
}

//////////////////////////////////////////////////////////////////////////
// Overloaded -= operator that removes the course given from this queue
template <class T>
Queue<T>& Queue<T>::operator-=(T* aNodeData){
  remove(aNodeData);
  return *this;
} 

//////////////////////////////////////////////////////////////////////////
// Overloaded -= operator that removes all elements of queue given from this queue
template <class T>
Queue<T>& Queue<T>::operator-=(Queue<T>& crsQueue) {
  Node<T> *currNode = crsQueue.head;
  
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
template <class T>
Queue<T> Queue<T>::operator-(T* aNodeData) {
  Queue<T> newQueue;

  Node<T> *currNode = head;

  while (currNode != 0) {
    if (*(currNode->data) != aNodeData)
      newQueue += currNode-> data;
    currNode = currNode->next;
  }

  return newQueue;
}

//////////////////////////////////////////////////////////////////////////
// Overloaded - operator that returns a new queue of all elements of this 
//   queue excluding all the elements of the queue given
template <class T>
Queue<T> Queue<T>::operator-(Queue<T>& crsQueue) {
  Queue<T> newQueue;

  bool same = false;

  Node<T> *currNode = head,  *crsNode  = crsQueue.head;
  while (currNode !=0) { 
    crsNode = crsQueue.head;
    same = false; 
    while(crsNode != 0){
      if (*(crsNode->data) == (currNode->data)) {
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
template <class T>
Queue<T>& Queue<T>::operator!() {
  clear();
}

//////////////////////////////////////////////////////////////////////////
// Overloaded << operator that prints out the elements of the queue
template <class T>
ostream& operator<<(ostream& out, Queue<T>& crsQueue) {
  int index = 0;
  T* ptr = crsQueue[index++];
  
  out << "[";

  while(ptr) {
    out << " " << *ptr;
    ptr = crsQueue[index++];
  }
  out << " ]" << endl;

  return out;
}







#endif