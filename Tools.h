//////////////////////////////////////////////////////////////////////////
// TOOLS
// Tools used to assist in the code

#ifndef TOOLS_H
#define TOOLS_H

#include "Types.h"

class Tools {
  public:
    Tools();
    ~Tools();
    
    // Conversion functions
    static string floatToString(float);
    static string intToString(int);
    static float  stringToFloat(string);
    static int    stringToInt(string);

    // Error checking functions
    static int  validStuNum(string aStuNum);
    static int  validName(string aName);
    static int  validEmail(string anEmail);
    static int  validNumber(string aNum);
    static int  validGPA(string aGPA);
};

#endif

