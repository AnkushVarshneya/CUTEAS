//////////////////////////////////////////////////////////////////////////
// MANAGER FOR THE cuTAES SYSTEM
// Controls the system's applications and queues

#ifndef MANAGER_H
#define MANAGER_H

#include "Types.h"

class GradInfoQueue;
class UGradInfoQueue;
class UGradApp;
class GradApp;
class UGradAppQueue;
class GradAppQueue;
class CourseQueue;

class Manager {
  friend class AcceptWindow;
  public:
    Manager();
    ~Manager();

    UGradApp*       makeNewUGradApp();
    GradApp*        makeNewGradApp();
    UGradApp*       getCurrUGradApp();
    GradApp*        getCurrGradApp();
    CourseQueue*    getCourseQueue();
    UGradAppQueue*  getUGradApps();
    GradAppQueue*   getGradApps();
    UGradInfoQueue* getUGradInfo();
    GradInfoQueue*  getGradInfo();

    void            setCurrAppsNull();
    void            changeUAppMem();
    void            changeGAppMem();
    void            cancelApp();
    void            saveApp();
    void            setCourse(UGradApp*, string);
    void            setCourse(GradApp*, string);
    void            setUGradInfo(string, string, string, string, string, int, float, float);
    void            setGradInfo(string, string, string, string, string, string, string);
    void            overwriteInfo(UGradApp*, string, string, string, string, int, float, float); 
    void            overwriteInfo(GradApp*, string, string, string, string, string, string);

  private:
    void            assembleQueues();
    void            saveEverything();

    int             lastAppNum;
    UGradApp*       currUGradApp;
    GradApp*        currGradApp;
    CourseQueue*    allCourses;
    GradAppQueue*   allGradApps;
    UGradAppQueue*  allUGradApps;
    GradInfoQueue*  allGradInfo;
    UGradInfoQueue* allUGradInfo;
};

#endif
