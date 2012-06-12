/*
 * region2D.h
 */

#ifndef REGION2D_H_LBDEM
#define REGION2D_H_LBDEM

#include "palabos2D.h"
#include "palabos2D.hh"

#include <string>

using namespace plb;

namespace Region{
  typedef std::pair<std::string,Box2D> Region2D;
  typedef std::map<std::string,Box2D> RegionList;
  typedef std::map<std::string,Box2D>::iterator RegionListIterator;

  Region2D regionFromXml(XMLreaderProxy const &r)
  {
    std::string id;
    plint x0,x1,y0,y1;
    r["id"].read(id);
    r["x0"].read(x0);
    r["x1"].read(x1);
    r["y0"].read(y0);
    r["y1"].read(y1);

    return Region2D(id,Box2D(x0,x1,y0,y1));
  }
};

#endif /* REGION2D_H_LBDEM */
