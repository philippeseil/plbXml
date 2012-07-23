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
 * plbXmlController2D.h
 * provides an xml interface to palabos
 */

#ifndef PBLXMLCONTROLLER_2D_LBDEM
#define PBLXMLCONTROLLER_2D_LBDEM

#include "action2D.h"
#include "region2D.h"
#include "boundary2D.h"
#include "globalDefs.h"
#include "units.h"

#include <string>
#include <list>
#include <map>
#include <utility>
#include <vector>

namespace plb{
  template<typename U> class IncomprFlowParam;
  template<typename U, template<typename V> class Desc > class OnLatticeBoundaryCondition2D;
  template<typename U, template<typename V> class Desc > class MultiBlockLattice2D;
  template<typename U, template<typename V> class Desc > class OnLatticeBoundaryCondition2D;
  class XMLreader;
  class XMLreaderProxy;
};

template<typename U> class LBconverter;

using namespace plb;
using namespace Action;
using namespace Region;
using namespace Boundary;

class PlbXmlController2D {
public:
  PlbXmlController2D(std::string &fname);
  ~PlbXmlController2D();

  const IncomprFlowParam<T>& getParams() const;
  const LBconverter<T>& getUnits() const;
  const RegionList& getRegionList() const;
  const ActionList& getActionList() const;
  const BoundaryList& getBoundaryList() const;

  

  void run(plint nSteps);
  void doStep();
  plint getNumSteps() const;
private:
  IncomprFlowParam<T> calcParams();
  LBconverter<T> calcUnits();
  void buildRegionList();
  void buildActionList();
  void buildTimeline();
  void buildBoundaryList();

  void initializeLattice();
  void setDynamics();
  void setBoundaries();
  void setInitValsFromFile();
  OnLatticeBoundaryCondition2D<T,DESCRIPTOR>* createBoundaryCondition();
  Dynamics<T,DESCRIPTOR>* dynamicsFromXML(XMLreaderProxy dyn);

  void performActions(plint step);

  // here, order is highly important because of initialization!
  XMLreader reader;
  XMLreaderProxy plbCase;
  LBconverter<T> units;
  IncomprFlowParam<T> params;
  OnLatticeBoundaryCondition2D<T,DESCRIPTOR> *boundaryCondition;

  RegionList regionList;
  ActionList actionList;
  BoundaryList boundaryList;
  
  int nSteps, iStep;
  MultiBlockLattice2D<T,DESCRIPTOR> lattice;
  
};

#endif /* PBLXMLCONTROLLER_2D_LBDEM */
