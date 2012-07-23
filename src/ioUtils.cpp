/* --------------------------------------------------------------------- 

Copyright 2012 JKU Linz
Author: Philippe Seil (philippe.seil@jku.at)

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


#include "ioUtils.h"
#include "plbHeaders2D.h"
#include "plbXmlController2D.h"
namespace ioUtils{
  bool elementExists(plb::XMLreaderProxy const &reader, std::string const &elemId)
  {
    std::string dummy;
    bool flag(true);
    try{
      reader[elemId].read(dummy);
    } catch (plb::PlbIOException &e){
      flag = false;
    }

    return flag;
  }

  plb::Box2D bcBoxFromXml(PlbXmlController2D const *controller, XMLreaderProxy const &r)
  {
    std::string bcId;
    try{
      r["bcId"].read(bcId);
    } catch(PlbIOException &e) {
      plbIOError("Invalid Set Pressure BC command");
    }
    ConstBoundaryListIterator b = (controller->getBoundaryList()).find(bcId);
    if(b == (controller->getBoundaryList()).end())
      plbIOError("Invalid boundary ID " + bcId);
    
    return (b->second).getRegion();
  }

  SetValueFromFile::SetValueFromFile(PlbXmlController2D const *controller_, std::string const &fname)
    : controller(controller_)
  {

    plint nx = controller->getParams().getNx(), ny =  controller->getParams().getNy();
    global::mpi().bCast(&nx, 1);
    global::mpi().bCast(&ny, 1);
    val = new MultiScalarField2D<T>(nx,ny);
    plb_ifstream ifile(fname.c_str());
    if(ifile.is_open())
      ifile >> *val;
    else
      plb::plbIOError("File " + fname + " not found.");
  }
  SetValueFromFile::~SetValueFromFile()
  {
    delete val;
  }

  SetValueFromFile::SetValueFromFile(SetValueFromFile const &orig)
    : controller(orig.controller)
  {
    val = new MultiScalarField2D<T>(*(orig.val));
  }


  SetPressureFromFile::SetPressureFromFile(PlbXmlController2D const *controller, std::string const &fname)
    : SetValueFromFile(controller,fname) {}
  
  SetPressureFromFile::SetPressureFromFile(SetPressureFromFile const &orig)
    : SetValueFromFile(orig) {}

  void SetPressureFromFile::operator() (plint iX, plint iY, T& density, Array<T,2>& velocity) const
  {
    density = controller->getUnits().latticePressure((*val).get(iX,iY))+1;
  }

  SetVelocityFromFile::SetVelocityFromFile(PlbXmlController2D const *controller, 
					   std::string const &fname, plint dim_)
    : SetValueFromFile(controller,fname), dim(dim_) {}

  SetVelocityFromFile::SetVelocityFromFile(SetVelocityFromFile const &orig)
    : SetValueFromFile(orig), dim(orig.dim) {}

  void SetVelocityFromFile::operator() (plint iX, plint iY, T& density, Array<T,2>& velocity) const
  {
    velocity[dim] = controller->getUnits().latticeVelocity((*val).get(iX,iY));
  }
  


} // namespace Utils
