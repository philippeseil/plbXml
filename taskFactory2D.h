#ifndef TASKFACTORY2D_H_LBDEM
#define TASKFACTORY2D_H_LBDEM

#include "palabos2D.h"
#include "palabos2D.hh"

#include "taskClasses2D.h"
#include "task2D.h"

using namespace plb;

namespace Task {

  class TaskBase;

  TaskBase* taskFromXml(XMLreaderProxy const &t);
  TaskBase* setDynamicsFromXml(XMLreaderProxy const &r);
  TaskBase* changeBcFromXml(XMLreaderProxy const &r);
  TaskBase* writeVtkFromXml(XMLreaderProxy const &r);

  /*
   * taskText must have one more entry than taskFactoryPtr
   * to check if no task text was found
   */
  const std::string LAST_TASK_TEXT_ENTRY("end");
  const char *taskText[] = 
    {
      "setDynamics",
      "changeBc",
      "writeVtk",
      LAST_TASK_TEXT_ENTRY.c_str()
    };

  TaskBase* (*taskFactoryPtr[])(XMLreaderProxy const &r) = 
  {
    &setDynamicsFromXml,
    &changeBcFromXml,
    &writeVtkFromXml
  };


};

#include "taskFactory2D.hh"

#endif /* TASKFACTORY2D_H_LBDEM */
