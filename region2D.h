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
