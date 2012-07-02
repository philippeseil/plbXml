#include "taskFactory2D.h"
#include "taskClasses2D.h"

namespace Task{

  const std::string LAST_TASK_TEXT_ENTRY("end");
  const char *taskText[] = 
    {
      "setDynamics",
      "changeBc",
      "writeVtk",
      LAST_TASK_TEXT_ENTRY.c_str()
    };

  TaskBase* (*taskFactoryPtr[])(XMLreaderProxy const &r, IncomprFlowParam<T> const &param) = 
  {
    &setDynamicsFromXml,
    &changeBcFromXml,
    &writeVtkFromXml
  };

  TaskBase* taskFromXml(XMLreaderProxy const &t,
			IncomprFlowParam<T> const &param)
  {
    std::string type = t.getName();
    for( int i=0 ; LAST_TASK_TEXT_ENTRY.compare(taskText[i]) != 0 ; i++){
      if(type.compare(taskText[i]) == 0)
	return (*taskFactoryPtr[i])(t,param);
    }
    
    throw PlbIOException("Unknown task type \"" + type + "\"");

    return 0;
  }

  TaskBase* setDynamicsFromXml(XMLreaderProxy const &r,
			       IncomprFlowParam<T> const &param)
  {
    plb::Dynamics<T,DESCRIPTOR> *dyn = 0;
    std::string type, regionId;
    r["type"].read(type);
    if(type.compare("BGKdynamics"))
      dyn = new plb::BGKdynamics<T,DESCRIPTOR>(1.);
    return new SetDynamics(regionId,dyn);
  }

  TaskBase* changeBcFromXml(XMLreaderProxy const &r,
			    IncomprFlowParam<T> const &param)
  {
    return new ChangeBcValue();
  }

  TaskBase* writeVtkFromXml(XMLreaderProxy const &r,
			    IncomprFlowParam<T> const &param)
  {
    return new WriteVtk();
  }

};
