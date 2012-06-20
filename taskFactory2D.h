#ifndef TASKFACTORY2D_H_LBDEM
#define TASKFACTORY2D_H_LBDEM

#include "palabos2D.h"
#include "palabos2D.hh"

#include "taskClasses2D.h"
#include "task2D.h"
#include "taskFactoryVariables2D.h"

using namespace plb;

namespace Task {

  TaskBase* taskFromXml(XMLreaderProxy const &t);
  TaskBase* setDynamicsFromXml(XMLreaderProxy const &r);
  TaskBase* changeBcFromXml(XMLreaderProxy const &r);
  TaskBase* writeVtkFromXml(XMLreaderProxy const &r);

  // insert new task types before NUM_OF_TASKS
  
  TaskBase* taskFromXml(XMLreaderProxy const &t)
  {
    std::string type = t.getName();
    for(int i=0;i<(int)NUM_OF_TASKS;i++){
      if(type.compare(taskText[i]) == 0)
	return (*taskFactoryPtr[i])(t);
    }
    
    throw PlbIOException("Unknown task type \"" + type + "\"");

    return 0;
  }

  TaskBase* setDynamicsFromXml(XMLreaderProxy const &r)
  {
    return new SetDynamics();
  }

  TaskBase* changeBcFromXml(XMLreaderProxy const &r)
  {
    return new ChangeBcValue();
  }

  TaskBase* writeVtkFromXml(XMLreaderProxy const &r)
  {
    return new WriteVtk();
  }

};

#endif /* TASKFACTORY2D_H_LBDEM */
