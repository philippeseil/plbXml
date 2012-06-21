#ifndef TASKCLASSES2D_H_LBDEM
#define TASKCLASSES2D_H_LBDEM

#include "palabos2D.h"
#include "palabos2D.hh"

#include "globalDefs.h"

namespace Task {
  
  class TaskBase{
  protected:
    TaskBase() {}
    virtual ~TaskBase() {}
  public:
    virtual void perform(IncomprFlowParam<T> const &param, 
			 MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
			 OnLatticeBoundaryCondition2D<T,DESCRIPTOR> &boundaryCondition) =0;
  };

  class SetDynamics : public TaskBase{
  public:
    virtual ~SetDynamics() {}
    virtual void perform(IncomprFlowParam<T> const &param, 
			 MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
			 OnLatticeBoundaryCondition2D<T,DESCRIPTOR> &boundaryCondition);
    friend TaskBase* setDynamicsFromXml(XMLreaderProxy const &r);
  private:
    SetDynamics();
  };

  class ChangeBcValue : public TaskBase{
  public:
    virtual ~ChangeBcValue() {}
    virtual void perform(IncomprFlowParam<T> const &param, 
			 MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
			 OnLatticeBoundaryCondition2D<T,DESCRIPTOR> &boundaryCondition);
    friend TaskBase* changeBcFromXml(XMLreaderProxy const &r);
  private:
    ChangeBcValue();
  };

  class WriteVtk : public TaskBase{
  public:
    virtual ~WriteVtk() {}
    virtual void perform(IncomprFlowParam<T> const &param, 
			 MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
			 OnLatticeBoundaryCondition2D<T,DESCRIPTOR> &boundaryCondition);
    friend TaskBase* writeVtkFromXml(XMLreaderProxy const &r);
  private:
    WriteVtk();
  };

};

#include "taskClasses2D.hh"

#endif /* TASKCLASSES2D_H_LBDEM */
