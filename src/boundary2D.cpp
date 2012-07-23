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


#include "boundary2D.h"
#include "plbHeaders2D.h"
#include "plbXmlController2D.h"

namespace plb{
  extern int colors[128][3];
};

namespace Boundary {
  BoundaryClass2D::BoundaryClass2D(PlbXmlController2D const *controller_,
				   BoundaryType const t_,
				   plb::boundary::BcType const &plbBcType_,
				   Region::ConstRegionListIterator const reg_)
    : controller(controller_), type(t_), plbBcType(plbBcType_), reg(reg_->second) {}

  plb::Box2D BoundaryClass2D::getRegion() const { return reg;}

  Boundary2D boundaryFromXml(PlbXmlController2D const *controller, XMLreaderProxy const &b)
  {
    std::string id;
    std::string regionId;
    BoundaryType bcType;
    plb::boundary::BcType plbBcType;
    Region::ConstRegionListIterator reg;

    try{
      b["id"].read(id);
    } catch (PlbIOException &e){
      throw PlbIOException("Invalid Boundary command: No id specified!");
    }

    try{
      b["regionId"].read(regionId);
      reg = (controller->getRegionList()).find(regionId);
      if(reg == (controller->getRegionList()).end())
	throw PlbIOException("dummy");
    } catch (PlbIOException &e){
      throw PlbIOException("Invalid Boundary command: Invalid or no regionId specified!");
    }

    std::vector<std::string> bcTypeRead;
    try{
      b["type"].read(bcTypeRead);
      if(bcTypeRead.size() == 0 || bcTypeRead.size() > 2) throw PlbIOException("dummy");

      if(bcTypeRead[0].compare("velocity") == 0)
	bcType = VELOCITY;
      else if(bcTypeRead[0].compare("pressure") == 0)
	bcType = PRESSURE;
      else throw PlbIOException("dummy");

      if(bcTypeRead.size() == 1 || bcTypeRead[1].compare("dirichlet") == 0)
	plbBcType = boundary::dirichlet;
      else if(bcTypeRead[1].compare("outflow") == 0 || bcTypeRead[1].compare("neumann") == 0)
	plbBcType = boundary::neumann;
      else if(bcType == VELOCITY) {
	if(bcTypeRead[1].compare("freeslip") == 0)
	  plbBcType = boundary::freeslip;
	else if(bcTypeRead[1].compare("normalOutflow") == 0)
	  plbBcType = boundary::normalOutflow;
	else throw PlbIOException("dummy");
      } else throw PlbIOException("dummy");

    } catch (PlbIOException &e){
      std::string errmsg("Invalid boundary command ");
      errmsg.append(id);
      errmsg.append(": invalid boundary type"); 
      throw PlbIOException(errmsg);
    }    

    return Boundary2D(id,BoundaryClass2D(controller,bcType,plbBcType,reg));
  }

}; /* namespace Boundary */
