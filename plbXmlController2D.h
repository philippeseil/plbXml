/*
 * plbXmlController2D.h
 * provides an xml interface to palabos
 */

#ifndef PBLXMLCONTROLLER_2D_LBDEM
#define PBLXMLCONTROLLER_2D_LBDEM

#include "palabos2D.h"
#include "palabos2D.hh"

#include <string>
#include <list>
#include <map>
#include <utility>

using namespace plb;

template<typename T>
class PlbXmlController2D {
public:
  PlbXmlController2D(std::string &fname);
  ~PlbXmlController2D();

  // typedefs for regions
  typedef std::pair<std::string,Box2D> Region2D;
  typedef std::map<std::string,Box2D> RegionList;
  typedef std::map<std::string,Box2D>::iterator RegionListIterator;

  const IncomprFlowParam<T>& getParams() const;
  const RegionList& getRegionList() const;

private:
  IncomprFlowParam<T> calcParams();
  void buildRegionList();

  // here, order is highly important because of initialization!
  XMLreader reader;
  XMLreaderProxy plbCase;
  IncomprFlowParam<T> params;

  RegionList regionList;

};

#include "plbXmlController2D.hh"

#endif /* PBLXMLCONTROLLER_2D_LBDEM */
