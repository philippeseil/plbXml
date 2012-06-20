/*
 * task object hierarchy
 */

#ifndef TASK2D_H_LBDEM
#define TASK2D_H_LBDEM

#include "palabos2D.h"
#include "palabos2D.hh"

#include "globalDefs.h"
#include "taskFactoryVariables2D.h"

#include <list>

using namespace plb;

namespace Task{
  enum TaskType;
  
  class TaskBase{
  protected:
    TaskBase(TaskType const t_) : type(t_) {}
    virtual ~TaskBase() {}
    TaskType type;
  public:
    TaskType getType() { return type; }
    virtual void perform(IncomprFlowParam<T> const &param, 
			 MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
			 OnLatticeBoundaryCondition2D<T,DESCRIPTOR> &boundaryCondition) =0;
  };

  typedef std::list<TaskBase*> TaskList;
  typedef std::list<TaskBase*>::iterator TaskListIterator;
  typedef std::list<TaskBase*>::const_iterator TaskListConstIterator;

};

#endif /* TASK2D_H_LBDEM */
