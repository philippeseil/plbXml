#ifndef TASKCLASSES2D_H_LBDEM
#define TASKCLASSES2D_H_LBDEM

#include "plbHeaders2D.h"

#include "globalDefs.h"
#include "boundary2D.h"
#include "region2D.h"

namespace Task {
  
  class TaskBase{
  protected:
    TaskBase() {}
    virtual ~TaskBase() {}
  public:
    virtual void perform(IncomprFlowParam<T> const &param, 
			 MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
			 OnLatticeBoundaryCondition2D<T,DESCRIPTOR> &boundaryCondition,
			 Boundary::BoundaryList const &b,
			 Region::RegionList const &r) =0;
  };

  class SetDynamics : public TaskBase{
  public:
    virtual ~SetDynamics();
    virtual void perform(IncomprFlowParam<T> const &param, 
			 MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
			 OnLatticeBoundaryCondition2D<T,DESCRIPTOR> &boundaryCondition,
			 Boundary::BoundaryList const &b,
			 Region::RegionList const &r);
    friend TaskBase* setDynamicsFromXml(XMLreaderProxy const &r, IncomprFlowParam<T> const &param);
  private:
    SetDynamics(std::string regionId_, plb::Dynamics<T,DESCRIPTOR> *dyn_);
    std::string regionId;
    plb::Dynamics<T,DESCRIPTOR> *dyn;
  };

  class ChangeBcValue : public TaskBase {
  public:
    virtual ~ChangeBcValue();
    virtual void perform(IncomprFlowParam<T> const &param, 
			 MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
			 OnLatticeBoundaryCondition2D<T,DESCRIPTOR> &boundaryCondition,
			 Boundary::BoundaryList const &b,
			 Region::RegionList const &r);
    friend TaskBase* changeBcFromXml(XMLreaderProxy const &r, IncomprFlowParam<T> const &param);
  private:
    ChangeBcValue();
    int i;
  };

  class WriteVtk : public TaskBase {
  public:
    virtual ~WriteVtk();
    virtual void perform(IncomprFlowParam<T> const &param, 
			 MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
			 OnLatticeBoundaryCondition2D<T,DESCRIPTOR> &boundaryCondition,
			 Boundary::BoundaryList const &b,
			 Region::RegionList const &r);
    friend TaskBase* writeVtkFromXml(XMLreaderProxy const &r, IncomprFlowParam<T> const &param);
  private:
    WriteVtk();
    int i;
  };
};


#endif /* TASKCLASSES2D_H_LBDEM */
