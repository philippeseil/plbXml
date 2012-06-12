/*
 * plbXmlController2D.h
 * provides an xml interface to palabos
 */

#ifndef PBLXMLCONTROLLER_2D_LBDEM
#define PBLXMLCONTROLLER_2D_LBDEM

#include "palabos2D.h"
#include "palabos2D.hh"

//#include "action2D.h"
#include "region2D.h"

#include <string>
#include <list>
#include <map>
#include <utility>

using namespace plb;
//using namespace Action;
using namespace Region;
template<typename T>
class PlbXmlController2D {
public:
  PlbXmlController2D(std::string &fname);
  ~PlbXmlController2D();

  const IncomprFlowParam<T>& getParams() const;
  const RegionList& getRegionList() const;

private:
  IncomprFlowParam<T> calcParams();
  void buildRegionList();
  void buildActionList();

  // here, order is highly important because of initialization!
  XMLreader reader;
  XMLreaderProxy plbCase;
  IncomprFlowParam<T> params;

  RegionList regionList;
  //  ActionList actionList;
};

#include "plbXmlController2D.hh"

#endif /* PBLXMLCONTROLLER_2D_LBDEM */
