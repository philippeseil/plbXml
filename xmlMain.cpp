/*
 * main file to test functions of plbXmlController2D
 */

#include "palabos2D.h"
#include "palabos2D.hh"

#include "plbXmlController2D.h"
#include "region2D.h"
#include "globalDefs.h"
#include "task2D.h"

#include <string>
#include <iostream>


int main(int argc, char **argv)
{
  plb::plbInit(&argc,&argv);

  std::string fName;
  global::argv(1).readNoThrow(fName);

  PlbXmlController2D<T> p(fName);

  PlbXmlController2D<T>::Timeline t(p.getTimeline());
  Action::ActionList const &a = p.getActionList();
  
  Boundary::BoundaryList b(p.getBoundaryList());

  for(int i=0;i<100;i++){
    for(ActionListIterator it=a.begin(); it != a.end(); ++it){
      if((it->second)->performAtStep(i)){
	std::cout << "step " << i << " action " << (it->first);
	Task::TaskList const t = (it->second)->getTaskList();
	for(Task::TaskListConstIterator it = t.begin();
	    it != t.end(); ++it){
	}
	std::cout << std::endl;

      }
    }
  }

  return 0;
}
