#ifndef TASKFACTORY2D_H_LBDEM
#define TASKFACTORY2D_H_LBDEM

#include "plbHeaders2D.h"

#include "taskClasses2D.h"

using namespace plb;

namespace Task {

  TaskBase* taskFromXml(XMLreaderProxy const &t,
			IncomprFlowParam<T> const &param);
  TaskBase* setDynamicsFromXml(XMLreaderProxy const &r,
			       IncomprFlowParam<T> const &param);
  TaskBase* changeBcFromXml(XMLreaderProxy const &r,
			    IncomprFlowParam<T> const &param);
  TaskBase* writeVtkFromXml(XMLreaderProxy const &r,
			    IncomprFlowParam<T> const &param);

  /*
   * taskText must have one more entry than taskFactoryPtr
   * to check if no task text was found
   */


};


#endif /* TASKFACTORY2D_H_LBDEM */
