
namespace Task{
  /*
   * ------------------------------------------------------------
   * class SetDynamics
   * ------------------------------------------------------------
   */
  
  SetDynamics::SetDynamics() 
    : TaskBase()
  {

  }
  void SetDynamics::perform(IncomprFlowParam<T> const &param, 
			    MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
			    OnLatticeBoundaryCondition2D<T,DESCRIPTOR> &boundaryCondition)
  {
    
  };
  
  /*
   * ------------------------------------------------------------
   * class ChangeBcValue
   * ------------------------------------------------------------
   */
 
  ChangeBcValue::ChangeBcValue()
    : TaskBase()
  {

  }

  void ChangeBcValue::perform(IncomprFlowParam<T> const &param, 
			      MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
			      OnLatticeBoundaryCondition2D<T,DESCRIPTOR> &boundaryCondition)
  {
    
  };
  /*
   * ------------------------------------------------------------
   * class WriteVtk
   * ------------------------------------------------------------
   */
 
  WriteVtk::WriteVtk()
    : TaskBase()
  {

  }

  void WriteVtk::perform(IncomprFlowParam<T> const &param, 
			 MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
			 OnLatticeBoundaryCondition2D<T,DESCRIPTOR> &boundaryCondition)
  {
    
  };


};
