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


#ifndef WRITE_VTK_LBDEM
#define WRITE_VTK_LBDEM

#ifdef TASK_LIST
addToTaskMap<WriteVtk>("writeVtk");
#else


#include "taskBase.h"
#include "units.h"

namespace Task {

class WriteVtk : public TaskBase {
public:
  WriteVtk(PlbXmlController2D const *controller, XMLreaderProxy const &r);
  virtual ~WriteVtk();
  virtual void perform(MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
		       plint nStep);
private:
  std::string prefix;
  
  struct PressureFromRho {
    PressureFromRho(PlbXmlController2D const *controller_);
    T operator()(T rho);
  private:
    LBconverter<T> const &units;
  };
    

};

} // namespace Task

#endif /* TASK_LIST */
#endif /* WRITE_VTK_LBDEM */
