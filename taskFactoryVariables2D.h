#ifndef TASKFACTORYVARIABLES2D_H_LBDEM
#define TASKFACTORYVARIABLES2D_H_LBDEM

#include "palabos2D.h"
#include "palabos2D.hh"

#include "taskClasses2D.h"

using namespace plb;

namespace Task{
  class TaskBase;

  TaskBase* taskFromXml(XMLreaderProxy const &t);
  TaskBase* setDynamicsFromXml(XMLreaderProxy const &r);
  TaskBase* changeBcFromXml(XMLreaderProxy const &r);
  TaskBase* writeVtkFromXml(XMLreaderProxy const &r);

  enum TaskType {SET_DYNAMICS, CHANGE_BC, WRITE_VTK, NUM_OF_TASKS};
  const char *taskText[] = 
    {
      "setDynamics",
      "changeBc",
      "writeVtk"
    };

  TaskBase* (*taskFactoryPtr[(int)NUM_OF_TASKS])(XMLreaderProxy const &r) = 
  {
    &setDynamicsFromXml,
    &changeBcFromXml,
    &writeVtkFromXml
  };

};


#endif /* TASKFACTORYVARIABLES2D_H_LBDEM */
