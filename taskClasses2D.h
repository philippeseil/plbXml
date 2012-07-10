#ifndef TASKCLASSES2D_H_LBDEM
#define TASKCLASSES2D_H_LBDEM

#include "plbHeaders2D.h"

#include "globalDefs.h"
#include "boundary2D.h"
#include "region2D.h"

#include <vector>

class PlbXmlController2D;
template<typename T> class LBconverter;

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

    struct PressureFromRho {
      PressureFromRho(PlbXmlController2D const *controller_);
      T operator()(T rho);
    private:
      LBconverter<T> const &units;
    };
    

  };

  class SetPressureBc : public TaskBase {
  public:
    virtual ~SetPressureBc();
    virtual void perform(MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
			 OnLatticeBoundaryCondition2D<T,DESCRIPTOR> &boundaryCondition,
			 plint nStep);
    friend TaskBase* setPressureBcFromXml(PlbXmlController2D const *controller, 
				     XMLreaderProxy const &r);
  protected:
    void setVal(T physVal);
    SetPressureBc(PlbXmlController2D const *controller, Box2D const &reg_, T val);
  private:
    Box2D reg;
    T val,physVal;
  };

  class SetPressureBcFromFile : public SetPressureBc {
  public:
    virtual ~SetPressureBcFromFile();
    virtual void perform(MultiBlockLattice2D<T,DESCRIPTOR> &lattice,
			 OnLatticeBoundaryCondition2D<T,DESCRIPTOR> &boundaryCondition,
			 plint nStep);
    friend TaskBase* setPressureBcFromXml(PlbXmlController2D const *controller,
					  XMLreaderProxy const &r);
  protected:
    SetPressureBcFromFile(PlbXmlController2D const *controller, Box2D const &reg,
			  std::string const &fname);
  private:
    std::vector<T> t,p;
    bool startFlag,endFlag,constantFlag;
    plint cursor, nStepThis, nStepNext;
  };

  class SetVelocityBc : public TaskBase {
  public:
    virtual ~SetVelocityBc();
    virtual void perform(MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
			 OnLatticeBoundaryCondition2D<T,DESCRIPTOR> &boundaryCondition,
			 plint nStep);
    friend TaskBase* setVelocityBcFromXml(PlbXmlController2D const *controller, 
					  XMLreaderProxy const &r);
  protected:
    void setVal(Array<T,2> physVal);
    SetVelocityBc(PlbXmlController2D const *controller, Box2D const &reg_, Array<T,2> const &val);
  private:
    Box2D reg;
    Array<T,2> val;    
  };

  class SetVelocityBcFromFile : public SetVelocityBc {
  public:
    virtual ~SetVelocityBcFromFile();
    virtual void perform(MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
			 OnLatticeBoundaryCondition2D<T,DESCRIPTOR> &boundaryCondition,
			 plint nStep);
    friend TaskBase* setVelocityBcFromXml(PlbXmlController2D const *controller, 
					  XMLreaderProxy const &r);
  protected:
    SetVelocityBcFromFile(PlbXmlController2D const *controller, Box2D const &reg_,
			  std::string const &fname);
  private:
    std::vector<T> t,vx,vy;
    bool startFlag,endFlag,constantFlag;
    plint cursor, nStepThis, nStepNext;

  };


};



#endif /* TASKCLASSES2D_H_LBDEM */
