/////////////////////////////////////////////////////////////////////////
// UNDERGRAD APPLICATION CLASS
// Contains all of the attributes and functions of an undergraduate's application

#ifndef UGRADAPP_H
#define UGRADAPP_H

#include "Application.h"
#include "Undergraduate.h"
#include "TakenCourse.h"

#include "Queue.h"


class UGradApp : public Application {
  public:
    UGradApp();
    ~UGradApp();

    Undergraduate*     getUndergrad()     const;
    Queue<TakenCourse>*   getTakenCrsQueue() const;

    void   setUndergrad(Undergraduate*); 
    void   setTakenCrsQueue(Queue<TakenCourse>*);
    void   print() const;

  private:
    Undergraduate*    undergrad;
    // Linked lists
    Queue<TakenCourse>* takenCrsQueue;  
};

#endif
