/*
 * main file to test functions of plbXmlController2D
 */

#include "palabos2D.h"
#include "palabos2D.hh"

#include "plbXmlController2D.h"
#include "region2D.h"

#include <string>
#include <iostream>

typedef double T;

int main(int argc, char **argv)
{
  plb::plbInit(&argc,&argv);

  std::string fName;
  global::argv(1).readNoThrow(fName);

  PlbXmlController2D<T> p(fName);

  PlbXmlController2D<T>::Timeline t(p.getTimeline());
  Action::ActionList a(p.getActionList());
  
  for(int i=0;i<t.size();i++){
    //  std::cout << t[i] << " " << a[t[i]].get() << std::endl;
    std::cout << t[i] << " " 
	      << a.find(t[i])->first << " "
	      << a.find(t[i])->second.get() << std::endl;
    // need this workaround to access elements because
    // map::operator[] requires a default constructor....
  }
  

  for(Action::ActionListIterator it = a.begin(); it != a.end(); it++)
    std::cout << (*it).first << " " << (*it).second.get()
	      << " " << (*it).first.compare(t[0]) 
	      << " " << (*it).first.compare("act1") << std::endl;

  std::cout << (*(a.find(t[0]))).second.get() << std::endl;

  return 0;
}
