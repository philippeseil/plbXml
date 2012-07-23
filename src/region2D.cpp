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


#include "region2D.h"

#include "plbHeaders2D.h"

namespace Region{
  Region2D regionFromXml(XMLreaderProxy const &r)
  {
    std::string id;
    plint x0,x1,y0,y1;
    try{
      r["id"].read(id);
    } catch (PlbIOException &e){
      throw PlbIOException("Invalid Region command: No id specified");
    }

    try{
      r["x0"].read(x0);
      r["x1"].read(x1);
      r["y0"].read(y0);
      r["y1"].read(y1);
    } catch(PlbIOException &e){
      throw PlbIOException("Invalid Region command: size specifications missing");
    }

    if( id.compare("") == 0 )
      throw PlbIOException("Invalid Region command: Unnamed region");
    if( x0<0 || y0<0 || x1<0 || y1<0 || x1<x0 || y1<y0 ){
      std::string errmsg("Invalid Region command: Bad size in region ");
      errmsg.append(id);
      throw PlbIOException(errmsg);
    }
      
    return Region2D(id,Box2D(x0,x1,y0,y1));
  }

};
