#include "taskFactory2D.h"
#include "taskClasses2D.h"

#include "plbXmlController2D.h"
#include "plbHeaders2D.h"

using namespace plb;

namespace Task{

  const std::string LAST_TASK_TEXT_ENTRY("end");
  const char *taskText[] = 
    {
      "setDynamics",
      "writeVtk",
      "setPressureBc",
      LAST_TASK_TEXT_ENTRY.c_str()
    };

  TaskBase* (*taskFactoryPtr[])(PlbXmlController2D const *controller,
				XMLreaderProxy const &r) = 
  {
    &setDynamicsFromXml,
    &writeVtkFromXml,
    &setPressureBcFromXml
  };

  TaskBase* taskFromXml(PlbXmlController2D const *controller,
			XMLreaderProxy const &t)
  {
    std::string type = t.getName();
    for( int i=0 ; LAST_TASK_TEXT_ENTRY.compare(taskText[i]) != 0 ; i++){
      if(type.compare(taskText[i]) == 0)
	return (*taskFactoryPtr[i])(controller,t);
    }
    
    plbIOError("Unknown task type \"" + type + "\"");

    return 0;
  }

  TaskBase* setDynamicsFromXml(PlbXmlController2D const *controller,
			       XMLreaderProxy const &r)
  {
    plb::Dynamics<T,DESCRIPTOR> *dyn = 0;
    std::string type, regionId;
    try{
      r["type"].read(type);
    } catch (PlbIOException &e){
      plbIOError("Invalid dynamics type in " + r.getName());
    }
    if(type.compare("BGKdynamics") == 0)
      dyn = new plb::BGKdynamics<T,DESCRIPTOR>(controller->getParams().getOmega());
    else if(type.compare("BounceBack") == 0)
      dyn = new BounceBack<T,DESCRIPTOR>();
    else if(type.compare("NoDynamics") == 0)
      dyn = new NoDynamics<T,DESCRIPTOR>();
    else
      plbIOError("Unknown dynamics type " + type);

    r["regionId"].read(regionId);

    return new SetDynamics(controller,regionId,dyn->clone());
  }

  TaskBase* writeVtkFromXml(PlbXmlController2D const *controller,
			    XMLreaderProxy const &r)
  {
    std::string prefix;
    try{
      r["fileName"].read(prefix);
    } catch(PlbIOException &e) {
      plbIOError("No file name for VTK output specified");
    }
    
    return new WriteVtk(controller,prefix);
  }

  TaskBase* setPressureBcFromXml(PlbXmlController2D const *controller,
				 XMLreaderProxy const &r)
  { 
    std::string bcId;
    T val;
    try{
      r["bcId"].read(bcId);
      r["bcValue"].read(val);
    } catch(PlbIOException &e) {
      plbIOError("Invalid Set Pressure BC command");
    }
    ConstBoundaryListIterator b = (controller->getBoundaryList()).find(bcId);
    if(b == (controller->getBoundaryList()).end())
      plbIOError("Invalid boundary ID " + bcId);

    Box2D reg = (b->second).getRegion();
    return new SetPressureBc(controller,reg,val);
  }

  TaskBase *setVelocityBcFromXml(PlbXmlController2D const *controller,
				 XMLreaderProxy const &r)
  {
    return 0;
  }
};
