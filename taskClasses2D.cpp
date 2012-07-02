#include "taskClasses2D.h"
#include "plbHeaders2D.h"

namespace Task{
  /*
   * ------------------------------------------------------------
   * class SetDynamics
   * ------------------------------------------------------------
   */
  
  SetDynamics::SetDynamics(std::string regionId_, plb::Dynamics<T,DESCRIPTOR> *dyn_) 
    : TaskBase(), regionId(regionId_), dyn(dyn_)
  {
    
  }

  SetDynamics::~SetDynamics()
  {
    delete dyn;
  }
  void SetDynamics::perform(IncomprFlowParam<T> const &param, 
			    MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
			    OnLatticeBoundaryCondition2D<T,DESCRIPTOR> &boundaryCondition,
			    Boundary::BoundaryList const &b,
			    Region::RegionList const &r)
  {
    
  };
  
  /*
   * ------------------------------------------------------------
   * class ChangeBcValue
   * ------------------------------------------------------------
   */
 
  ChangeBcValue::ChangeBcValue()
    : TaskBase(), i(1)
  {

  }

  ChangeBcValue::~ChangeBcValue()
  {

  }

  void ChangeBcValue::perform(IncomprFlowParam<T> const &param, 
			      MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
			      OnLatticeBoundaryCondition2D<T,DESCRIPTOR> &boundaryCondition,
			      Boundary::BoundaryList const &b,
			      Region::RegionList const &r)
  {
    
  };
  /*
   * ------------------------------------------------------------
   * class WriteVtk
   * ------------------------------------------------------------
   */
 
  WriteVtk::WriteVtk()
    : TaskBase(), i(1)
  {

  }

  WriteVtk::~WriteVtk()
  {

  }

  void WriteVtk::perform(IncomprFlowParam<T> const &param, 
			 MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
			 OnLatticeBoundaryCondition2D<T,DESCRIPTOR> &boundaryCondition,
			 Boundary::BoundaryList const &b,
			 Region::RegionList const &r)
  {
    i++;
  };


};
