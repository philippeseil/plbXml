#ifndef TASKCLASSES2D_H_LBDEM
#define TASKCLASSES2D_H_LBDEM

#include "palabos2D.h"
#include "palabos2D.hh"

#include "task2D.h"


namespace Task {

  class SetDynamics : public TaskBase{
  public:
    virtual ~SetDynamics() {}
    virtual void perform(IncomprFlowParam<T> const &param, 
			 MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
			 OnLatticeBoundaryCondition2D<T,DESCRIPTOR> &boundaryCondition) {};
    friend TaskBase* setDynamicsFromXml(XMLreaderProxy const &r);
  private:
    SetDynamics() : TaskBase(SET_DYNAMICS) {}
  };

  class ChangeBcValue : public TaskBase{
  public:
    virtual ~ChangeBcValue() {}
    virtual void perform(IncomprFlowParam<T> const &param, 
			 MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
			 OnLatticeBoundaryCondition2D<T,DESCRIPTOR> &boundaryCondition) {};
    friend TaskBase* changeBcFromXml(XMLreaderProxy const &r);
  private:
    ChangeBcValue() : TaskBase(CHANGE_BC) {}
  };

  class WriteVtk : public TaskBase{
  public:
    virtual ~WriteVtk() {}
    virtual void perform(IncomprFlowParam<T> const &param, 
			 MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
			 OnLatticeBoundaryCondition2D<T,DESCRIPTOR> &boundaryCondition) {};
    friend TaskBase* writeVtkFromXml(XMLreaderProxy const &r);
  private:
    WriteVtk() : TaskBase(WRITE_VTK) {}    
  };

};

#endif /* TASKCLASSES2D_H_LBDEM */
