/////////////////////////////////////////////////////////////////////////
// GRAD APPLICATION CLASS
// Contains all of the attributes and functions of a graduate's application

#ifndef GRADAPP_H
#define GRADAPP_H

#include "Application.h"
#include "Graduate.h"

class Application;

class GradApp : public Application {
  public:
    GradApp();
    ~GradApp();

    Graduate* getGrad() const;
    void      setGrad(Graduate*); 
    void      print()   const;

  private:
    Graduate*  grad; 
};

#endif
