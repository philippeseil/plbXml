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


/*
 * region2D.h
 */

#ifndef REGION2D_H_LBDEM
#define REGION2D_H_LBDEM

#include <string>
#include <map>

namespace plb{
  class Box2D;
  class XMLreaderProxy;
}

using namespace plb;


namespace Region{
  typedef std::pair<std::string,Box2D> Region2D;
  typedef std::map<std::string,Box2D> RegionList;
  typedef std::map<std::string,Box2D>::iterator RegionListIterator;
  typedef std::map<std::string,Box2D>::const_iterator ConstRegionListIterator;

  Region2D regionFromXml(XMLreaderProxy const &r);
 
};

#endif /* REGION2D_H_LBDEM */
