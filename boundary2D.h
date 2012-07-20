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


/*
 * handling of boundary conditions
 * currently, only bc on block boundaries are supported
 */

#ifndef BOUNDARY2D_H_LBDEM
#define BOUNDARY2D_H_LBDEM

#include "region2D.h"
#include "boundaryCondition/boundaryCondition.h"
#include "core/geometry2D.h"
#include "taskBase.h"
class PlbXmlController2D;

namespace plb{
  class XMLreaderProxy;
};

namespace Boundary{
    
  enum BoundaryType { VELOCITY, PRESSURE };
  class BoundaryClass2D {
  public:
    BoundaryClass2D(PlbXmlController2D const *controller_,
		    BoundaryType const t_,
		    plb::boundary::BcType const &plbBcType_,
		    Region::ConstRegionListIterator const reg_);

    const BoundaryType getBoundaryType() const { return type;}
    const plb::boundary::BcType getPlbBcType() const { return plbBcType;}
    plb::Box2D getRegion() const;

  private:
    BoundaryType type;
    plb::boundary::BcType plbBcType;
    plb::Box2D reg;
    PlbXmlController2D const *controller;
  };

  typedef std::pair<std::string,BoundaryClass2D> Boundary2D;
  typedef std::map<std::string,BoundaryClass2D> BoundaryList;
  typedef std::map<std::string,BoundaryClass2D>::iterator BoundaryListIterator;
  typedef std::map<std::string,BoundaryClass2D>::const_iterator ConstBoundaryListIterator;

  Boundary2D boundaryFromXml(PlbXmlController2D const *controller, plb::XMLreaderProxy const &b);

};

#endif /* BOUNDARY2D_H_LBDEM */
