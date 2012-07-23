/* --------------------------------------------------------------------- 

Copyright 2012 Philippe Seil

This file is part of plbXml.

plbXml is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation, either version 2 of the License, or (at
your option) any later version.

plbXml is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with plbXml. If not, see http://www.gnu.org/licenses/.

---------------------------------------------------------------------- */


#include "writeVtk.h"
#include "plbXmlController2D.h"
#include "ioUtils.h"

namespace Task {
  WriteVtk::WriteVtk(PlbXmlController2D const *controller, XMLreaderProxy const &r)
    : TaskBase(controller,r.getId()), fileNameLength(8)
  {
    try{
      r["fileName"].read(prefix);
    } catch(PlbIOException &e) {
      plbIOError("No file name for VTK output specified");
    }
    if(ioUtils::elementExists(r,"fileNameLength"))
      r["fileNameLength"].read(fileNameLength);
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
			 plint nStep)
  {
    T dx = controller->getParams().getDeltaX();
    T physU = controller->getUnits().physVelocity();
    std::string fname = createFileName(prefix, nStep, fileNameLength);
    VtkImageOutput2D<T> vtkOut(fname, dx);
    
    std::auto_ptr<MultiScalarField2D<T> > density = computeDensity(lattice);
    PressureFromRho p(controller);

    apply(p,*density);
    
    vtkOut.writeData<float>(*density, "pressure", 1);
    vtkOut.writeData<2,float>(*computeVelocity(lattice), "velocity", physU);
    pcout << "vtk file " << fname << " written" << std::endl;
  };

  
} // namespace Task
