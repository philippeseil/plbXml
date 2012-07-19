#ifndef TASK_BASE_LBDEM
#define TASK_BASE_LBDEM

#include "plbHeaders2D.h"
#include "globalDefs.h"

class PlbXmlController2D;

using namespace plb;

namespace Task {
  class TaskBase{
  protected:
    TaskBase(PlbXmlController2D const *controller_) : controller(controller_) {}
    virtual ~TaskBase() {}
    PlbXmlController2D const *controller;
  public:
    virtual void perform(MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
			 OnLatticeBoundaryCondition2D<T,DESCRIPTOR> &boundaryCondition,
			 plint nStep) =0;
  };
} // namespace Task
#endif /* TASK_BASE_LBDEM */
