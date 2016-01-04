//////////////////////////////////////////////////////////////////////////
// GENERFAL INFORMATION CLASS
// Contains all the attributes and functions of a student's information 

#include "GenInfo.h"
#include "Types.h"

//////////////////////////////////////////////////////////////////////////
// Default Constructor
GenInfo::GenInfo(string num, string fn, string sn, string em)
   : stuNum(num), firstName(fn), surname(sn), email(em)
{
  //cout << "CONSTRUCT GenInfo" << endl;
}

//////////////////////////////////////////////////////////////////////////
// Destructor
GenInfo::~GenInfo() {
  //cout << "DESTRUCT GenInfo StuNum #" << stuNum << endl;
}

//////////////////////////////////////////////////////////////////////////
// Get functions
string GenInfo::getStuNum()   { return stuNum; }
string GenInfo::getFirstName(){ return firstName; }
string GenInfo::getSurname()  { return surname; }
string GenInfo::getEmail()    { return email; }

//////////////////////////////////////////////////////////////////////////
// Set functions
void GenInfo::setStuNum(string num)   { stuNum       = num; }
void GenInfo::setFirstName(string fn) { firstName    = fn;  }
void GenInfo::setSurname(string sn)   { surname      = sn;  }
void GenInfo::setEmail(string em)     { email        = em;  }
