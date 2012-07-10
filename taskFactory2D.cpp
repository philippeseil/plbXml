#include "taskFactory2D.h"
#include "taskClasses2D.h"
#include "ioUtils.h"

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
      "setVelocityBc",
      LAST_TASK_TEXT_ENTRY.c_str()
    };

  TaskBase* (*taskFactoryPtr[])(PlbXmlController2D const *controller,
				XMLreaderProxy const &r) = 
  {
    &setDynamicsFromXml,
    &writeVtkFromXml,
    &setPressureBcFromXml,
    &setVelocityBcFromXml
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
    try{
      r["bcId"].read(bcId);
    } catch(PlbIOException &e) {
      plbIOError("Invalid Set Pressure BC command");
    }
    ConstBoundaryListIterator b = (controller->getBoundaryList()).find(bcId);
    if(b == (controller->getBoundaryList()).end())
      plbIOError("Invalid boundary ID " + bcId);
    
    Box2D reg = (b->second).getRegion();
    if(ioUtils::elementExists(r,"bcValue")){
      T val;
      r["bcValue"].read(val);
      return new SetPressureBc(controller,reg,val);
    } else if(ioUtils::elementExists(r,"valFile")){
      std::string fname;
      r["valFile"].read(fname);
      return new SetPressureBcFromFile(controller,reg,fname);
    }

    plbIOError("Invalid Set Pressure BC command");
    return 0;
  }

  TaskBase *setVelocityBcFromXml(PlbXmlController2D const *controller,
				 XMLreaderProxy const &r)
  {
    std::string bcId;
    try{
      r["bcId"].read(bcId);
    } catch(PlbIOException &e) {
      plbIOError("Invalid Set Velocity BC command");
    }
    ConstBoundaryListIterator b = (controller->getBoundaryList()).find(bcId);
    if(b == (controller->getBoundaryList()).end())
      plbIOError("Invalid boundary ID " + bcId);

    Box2D reg = (b->second).getRegion();
    if(ioUtils::elementExists(r,"bcValue")){
      std::vector<T> val;
      r["bcValue"].read(val);
      return new SetVelocityBc(controller,reg,Array<T,2>(val[0],val[1]));
    } else if(ioUtils::elementExists(r,"valFile")){
      std::string fname;
      r["valFile"].read(fname);
      return new SetVelocityBcFromFile(controller,reg,fname);
    }

    plbIOError("Invalit Set Velocity BC command");

    return 0;

  }
};
