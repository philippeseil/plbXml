#ifndef TASKCLASSES2D_H_LBDEM
#define TASKCLASSES2D_H_LBDEM

#include "plbHeaders2D.h"

#include "globalDefs.h"
#include "boundary2D.h"
#include "region2D.h"

class PlbXmlController2D;

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

  class SetDynamics : public TaskBase{
  public:
    virtual ~SetDynamics();
    virtual void perform(MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
			 OnLatticeBoundaryCondition2D<T,DESCRIPTOR> &boundaryCondition,
			 plint nStep);
    friend TaskBase* setDynamicsFromXml(PlbXmlController2D const *controller, 
					XMLreaderProxy const &r);
  private:
    SetDynamics(PlbXmlController2D const *controller, 
		std::string regionId_, plb::Dynamics<T,DESCRIPTOR> *dyn_);
    std::string regionId;
    plb::Dynamics<T,DESCRIPTOR> *dyn;
  };

  class WriteVtk : public TaskBase {
  public:
    virtual ~WriteVtk();
    virtual void perform(MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
			 OnLatticeBoundaryCondition2D<T,DESCRIPTOR> &boundaryCondition,
			 plint nStep);
    friend TaskBase* writeVtkFromXml(PlbXmlController2D const *controller, 
				     XMLreaderProxy const &r);
  private:
    WriteVtk(PlbXmlController2D const *controller, std::string const &prefix_);
    std::string prefix;
  };

  class SetPressureBc : public TaskBase {
  public:
    virtual ~SetPressureBc();
    virtual void perform(MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
			 OnLatticeBoundaryCondition2D<T,DESCRIPTOR> &boundaryCondition,
			 plint nStep);
    friend TaskBase* setPressureBcFromXml(PlbXmlController2D const *controller, 
				     XMLreaderProxy const &r);
  private:
    SetPressureBc(PlbXmlController2D const *controller, Box2D const &reg_, T val);
    Box2D reg;
    T val;
  };


};


#endif /* TASKCLASSES2D_H_LBDEM */
