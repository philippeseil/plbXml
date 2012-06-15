/*
 * task object hierarchy
 */

#include "palabos2D.h"
#include "palabos2D.hh"

#include "globalDefs.h"

namespace Task{

  class TaskBase{
  protected:
    TaskBase() {}
    virtual ~TaskBase() {}
  public:
    virtual void do(IncomprFlowParam<T> const &param, 
		    MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
		    OnLatticeBoundaryCondition2D<T,DESCRIPTOR> &boundaryCondition) =0;
  };

  class ScheduledTask : TaskBase{
  protected:
    ScheduledTask() : TaskBase() {};
    virtual ~TaskBase() {};

  public:
    virtual void do(IncomprFlowParam<T> const &param, 
		    MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
		    OnLatticeBoundaryCondition2D<T,DESCRIPTOR> &boundaryCondition) =0;
  };
  class Run : public TaskBase{
  public:
    Run() : TaskBase();
    virtual ~TaskBase() {}

    virtual void do(IncomprFlowParam<T> const &param, 
		    MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
		    OnLatticeBoundaryCondition2D<T,DESCRIPTOR> &boundaryCondition);
  };


  class ChangeBcValue : public TaskBase{
  public:
    ChangeBcValue() : TaskBase();
    virtual ~ChangeBcValue();
    virtual void do(IncomprFlowParam<T> const &param, 
		    MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
		    OnLatticeBoundaryCondition2D<T,DESCRIPTOR> &boundaryCondition);
  };

};
