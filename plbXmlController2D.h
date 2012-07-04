/*
 * plbXmlController2D.h
 * provides an xml interface to palabos
 */

#ifndef PBLXMLCONTROLLER_2D_LBDEM
#define PBLXMLCONTROLLER_2D_LBDEM

#include "action2D.h"
#include "region2D.h"
#include "boundary2D.h"
#include "globalDefs.h"

#include <string>
#include <list>
#include <map>
#include <utility>
#include <vector>

namespace plb{
  template<typename U> class IncomprFlowParam;
  template<typename U, template<typename V> class Desc > class OnLatticeBoundaryCondition2D;
  template<typename U, template<typename V> class Desc > class MultiBlockLattice2D;
  class XMLreader;
  class XMLreaderProxy;
};

using namespace plb;
using namespace Action;
using namespace Region;
using namespace Boundary;

class PlbXmlController2D {
public:
  PlbXmlController2D(std::string &fname);
  ~PlbXmlController2D();

  const IncomprFlowParam<T>& getParams() const;
  const RegionList& getRegionList() const;
  const ActionList& getActionList() const;
  const BoundaryList& getBoundaryList() const;

  void run(plint nSteps);
private:
  IncomprFlowParam<T> calcParams();
  void buildRegionList();
  void buildActionList();
  void buildTimeline();
  void buildBoundaryList();

  void initializeLattice();
  OnLatticeBoundaryCondition2D<T,DESCRIPTOR>* createBoundaryCondition();

  void performActions(plint step);

  // here, order is highly important because of initialization!
  XMLreader reader;
  XMLreaderProxy plbCase;
  IncomprFlowParam<T> params;
  OnLatticeBoundaryCondition2D<T,DESCRIPTOR> *boundaryCondition;

  RegionList regionList;
  ActionList actionList;
  BoundaryList boundaryList;
  
  MultiBlockLattice2D<T,DESCRIPTOR> lattice;
  
};

#endif /* PBLXMLCONTROLLER_2D_LBDEM */
