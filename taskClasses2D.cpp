#include "taskClasses2D.h"
#include "plbHeaders2D.h"
#include "plbXmlController2D.h"

namespace Task{
  /*
   * ------------------------------------------------------------
   * class SetDynamics
   * ------------------------------------------------------------
   */
  
  SetDynamics::SetDynamics(PlbXmlController2D const *controller_, 
			   std::string regionId_, plb::Dynamics<T,DESCRIPTOR> *dyn_) 
    : TaskBase(controller_), regionId(regionId_), dyn(dyn_)
  {
    
  }

  SetDynamics::~SetDynamics()
  {
    delete dyn;
  }
  void SetDynamics::perform(MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
			    OnLatticeBoundaryCondition2D<T,DESCRIPTOR> &boundaryCondition,
			    plint nStep)
  {
    Box2D reg( (controller->getRegionList()).find(regionId)->second );
    defineDynamics(lattice, reg, dyn->clone());
    std::cout << "Defined dynamics" << std::endl;
  };
  
  /*
   * ------------------------------------------------------------
   * class SetPressureBC
   * ------------------------------------------------------------
   */
 
  SetPressureBc::SetPressureBc(PlbXmlController2D const *controller, Box2D const &reg_, T val_)
    : TaskBase(controller), reg(reg_), val(val_)
  {
    
  }

  SetPressureBc::~SetPressureBc()
  {

  }

  void SetPressureBc::perform(MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
			      OnLatticeBoundaryCondition2D<T,DESCRIPTOR> &boundaryCondition,
			      plint nStep)
  {
    pcout << "boundary density set to " << val << std::endl;
    setBoundaryDensity(lattice, reg, val );
    initializeAtEquilibrium(lattice,reg,val,Array<T,2>(0.,0.));
  };


  /*
   * ------------------------------------------------------------
   * class SetVelocityBC
   * ------------------------------------------------------------
   */
 
  SetVelocityBc::SetVelocityBc(PlbXmlController2D const *controller, Box2D const &reg_, Array<T,2> const &val_)
    : TaskBase(controller), reg(reg_), val(val_)
  {
    
  }

  SetVelocityBc::~SetVelocityBc()
  {

  }

  void SetVelocityBc::perform(MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
			      OnLatticeBoundaryCondition2D<T,DESCRIPTOR> &boundaryCondition,
			      plint nStep)
  {
    pcout << "boundary velocity set to " << val[0] << " " << val[1] << std::endl;
    setBoundaryVelocity(lattice, reg, val );
    initializeAtEquilibrium(lattice,reg,1.,val);
  };


  /*
   * ------------------------------------------------------------
   * class WriteVtk
   * ------------------------------------------------------------
   */
 
  WriteVtk::WriteVtk(PlbXmlController2D const *controller, std::string const &prefix_)
    : TaskBase(controller), prefix(prefix_)
  {

  }

  WriteVtk::~WriteVtk()
  {

  }

  void WriteVtk::perform(MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
			 OnLatticeBoundaryCondition2D<T,DESCRIPTOR> &boundaryCondition,
			 plint nStep)
  {
    T dx = controller->getParams().getDeltaX();
    T dt = controller->getParams().getDeltaT();
    std::string fname = createFileName(prefix, nStep, 8);
    VtkImageOutput2D<T> vtkOut(fname, dx);
    vtkOut.writeData<float>(*computeVelocityNorm(lattice), "velocityNorm", dx/dt);
    vtkOut.writeData<float>(*computeDensity(lattice), "density", 1);
    vtkOut.writeData<2,float>(*computeVelocity(lattice), "velocity", dx/dt);
    pcout << "vtk file " << fname << " written" << std::endl;
  };


};
