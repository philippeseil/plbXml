#include "taskFactory2D.h"
#include "ioUtils.h"
#include "taskFactoryAggregateHeader2D.hh"

#include "plbXmlController2D.h"
#include "plbHeaders2D.h"

using namespace plb;

namespace Task{

  TaskFactory::TaskFactory()
  {
    #include "taskFactoryInitializer2D.hh"
  }

  TaskBase* TaskFactory::create(PlbXmlController2D const *controller,
				XMLreaderProxy const &t)
  {
    std::string type = t.getName();
    TaskMap::iterator pos = taskMap.find(type);
    if(pos != taskMap.end()){
      return pos->second->create(controller,t);
    } else{
      return 0;
    }
  }



};
