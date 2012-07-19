#include "writeVtk.h"
#include "plbXmlController2D.h"
namespace Task {
  WriteVtk::WriteVtk(PlbXmlController2D const *controller, XMLreaderProxy const &r)
    : TaskBase(controller)
  {
    try{
      r["fileName"].read(prefix);
    } catch(PlbIOException &e) {
      plbIOError("No file name for VTK output specified");
    }
  }

  WriteVtk::~WriteVtk()
  {

  }

  WriteVtk::PressureFromRho::PressureFromRho(PlbXmlController2D const *controller_)
    : units(controller_->getUnits()) {}
  T WriteVtk::PressureFromRho::operator() (T rho)
  {
    return units.physPressure(rho);
  }

  void WriteVtk::perform(MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
			 OnLatticeBoundaryCondition2D<T,DESCRIPTOR> &boundaryCondition,
			 plint nStep)
  {
    T dx = controller->getParams().getDeltaX();
    T physU = controller->getUnits().physVelocity();
    std::string fname = createFileName(prefix, nStep, 12);
    VtkImageOutput2D<T> vtkOut(fname, dx);
    
    std::auto_ptr<MultiScalarField2D<T> > density = computeDensity(lattice);
    PressureFromRho p(controller);

    apply(p,*density);
    
    vtkOut.writeData<float>(*density, "pressure", 1);
    vtkOut.writeData<2,float>(*computeVelocity(lattice), "velocity", physU);
    pcout << "vtk file " << fname << " written" << std::endl;
  };

  
} // namespace Task
