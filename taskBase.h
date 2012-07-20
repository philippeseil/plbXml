#ifndef TASK_BASE_LBDEM
#define TASK_BASE_LBDEM

#include "plbHeaders2D.h"
#include "globalDefs.h"

class PlbXmlController2D;

using namespace plb;

namespace Task {
  class TaskBase{
  protected:
    TaskBase(PlbXmlController2D const *controller_, int id_) 
      : controller(controller_), id(id_) {}
    virtual ~TaskBase() {}
    PlbXmlController2D const *controller;
  public:
    virtual void perform(MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
			 plint nStep) =0;

    int id;

    bool operator<(TaskBase &rhs){
      return id < rhs.id;
    }
  };
} // namespace Task
#endif /* TASK_BASE_LBDEM */
