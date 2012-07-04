#ifndef TASKFACTORY2D_H_LBDEM
#define TASKFACTORY2D_H_LBDEM

#include "plbHeaders2D.h"

#include "taskClasses2D.h"

using namespace plb;

namespace Task {

  TaskBase* taskFromXml(PlbXmlController2D const *controller,
			XMLreaderProxy const &t);
  TaskBase* setDynamicsFromXml(PlbXmlController2D const *controller,
			       XMLreaderProxy const &r);
  TaskBase* writeVtkFromXml(PlbXmlController2D const *controller,
			    XMLreaderProxy const &r);
  TaskBase* setPressureBcFromXml(PlbXmlController2D const *controller,
				 XMLreaderProxy const &r);

  /*
   * taskText must have one more entry than taskFactoryPtr
   * to check if no task text was found
   */


};


#endif /* TASKFACTORY2D_H_LBDEM */
