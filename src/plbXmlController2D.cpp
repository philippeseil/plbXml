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



#include "plbXmlController2D.h"
#include "ioUtils.h"
#include "units.h"
/*
 * ------------------------------------------------------------------
 * getters for various lists
 * ------------------------------------------------------------------
 */

const IncomprFlowParam<T>&  PlbXmlController2D::getParams() const
{
  return params;
}

const LBconverter<T>&  PlbXmlController2D::getUnits() const
{
  return units;
}

const RegionList& PlbXmlController2D::getRegionList() const
{
  return regionList;
}

const ActionList& PlbXmlController2D::getActionList() const
{
  return actionList;
}

const BoundaryList& PlbXmlController2D::getBoundaryList() const
{
  return boundaryList;
}

plint PlbXmlController2D::getNumSteps() const
{ 
  return nSteps;
}

/*
 * --------------------------------------------------------------
 * calculating and building functions for the various lists
 * --------------------------------------------------------------
 */

LBconverter<T> PlbXmlController2D::calcUnits()
{
  XMLreaderProxy p(plbCase["parameters"]);
  T latticeL, latticeU;
  T physL, physU, physNu, physRho, pressureLevel;

  int res;

  p["resolution"].read(res);
  p["physL"].read(physL);
  p["physU"].read(physU);
  p["latticeU"].read(latticeU);
  p["physNu"].read(physNu);
  p["physRho"].read(physRho);
  p["pressureLevel"].read(pressureLevel);

  LBconverter<T> units_(2, // dimensions
			1./((T)res)*physL, // phys. length of a lattice cell
			latticeU, // lattice velocity
			physNu, // physical viscosity
			physL, // physical characteristic length
			physU, // physical characteristic velocity
			physRho, // physical density of fluid
			pressureLevel); // an additive pressure level

  pcout << "Characteristic Length   : " << units_.getCharL() << "\n"
	<< "Characteristic Velocity : " << units_.getCharU() << "\n"
	<< "Characteristic Time     : " << units_.getCharTime() << std::endl;

  return units_;
}

IncomprFlowParam<T> PlbXmlController2D::calcParams()
{
  XMLreaderProxy p(plbCase["parameters"]);
  
  T lx(0.),ly(0.);
  plint res(1);

  p["lx"].read(lx);
  p["ly"].read(ly);
  p["resolution"].read(res);

  lx /= units.getCharL();
  ly /= units.getCharL();

  IncomprFlowParam<T> params_(1.,units.getLatticeU(),units.getRe(),1.,res,lx,ly);

  pcout << "Lattice size    : " << params_.getNx() << " " << params_.getNy() << std::endl;
  pcout << "Reynolds number : " << params_.getRe() << std::endl;
  pcout << "Lattice U       : " << params_.getLatticeU()<< std::endl;
  pcout << "omega           : " << params_.getOmega() << std::endl;

  return params_;
}

void PlbXmlController2D::buildRegionList()
{
  std::pair<RegionListIterator,bool> inserted;
  XMLreaderProxy reg(plbCase["region"]);
  for( ; reg.isValid(); reg = reg.iterId() ){
    inserted = regionList.insert(regionFromXml(reg));
    // check for duplicated entry
    if(!inserted.second)
      std::cout << "Warning: Region with duplicate ID " 
		<< (*inserted.first).first << " ignored" << std::endl;
  }
}

void PlbXmlController2D::buildActionList()
{
  std::pair<ActionListIterator,bool> inserted;
  XMLreaderProxy act(plbCase["action"]);
  for( ; act.isValid(); act = act.iterId() ){
    inserted = actionList.insert(actionFromXml(this,act));
    // check for duplicated entry
    if(!inserted.second)
      std::cout << "Warning: Action with duplicate ID " 
		<< (*inserted.first).first << " ignored" << std::endl;
  }

}

void PlbXmlController2D::buildBoundaryList()
{
  std::pair<BoundaryListIterator,bool> inserted;
  XMLreaderProxy b(plbCase["boundary"]);
  for( ; b.isValid(); b = b.iterId() ){
    inserted = boundaryList.insert(boundaryFromXml(this,b));
    if(!inserted.second)
      std::cout << "Warning: Boundary with duplicate ID "
		<< (inserted.first)->first << " ignored" << std::endl;
  }
}

Dynamics<T,DESCRIPTOR>* PlbXmlController2D::dynamicsFromXML(XMLreaderProxy dyn)
{
  std::vector<std::string> type;
  dyn.read(type);
  if(type[0].compare("BGKdynamics") == 0)
    return new BGKdynamics<T,DESCRIPTOR>(params.getOmega());
  if(type[0].compare("RegularizedBGK") == 0)
    return new RegularizedBGKdynamics<T,DESCRIPTOR>(params.getOmega());
  if(type[0].compare("SmagorinskyRegularized") == 0){
    if(type.size()<2)
      throw PlbIOException("Missing Smagorinsky constant");
    T cs = atof(type[1].c_str());
    return new SmagorinskyRegularizedDynamics<T,DESCRIPTOR>(params.getOmega(),cs);
  }
  if(type[0].compare("SmagorinskyBGK") == 0){
    throw PlbIOException("Missing Smagorinsky constant");
    T cs = atof(type[1].c_str());
    return new SmagorinskyBGKdynamics<T,DESCRIPTOR>(params.getOmega(),cs);
  }
  if(type[0].compare("BounceBack") == 0)
    return new BounceBack<T,DESCRIPTOR>();
  if(type[0].compare("NoDynamics") == 0)
    return new NoDynamics<T,DESCRIPTOR>();
  
  return 0;
}

OnLatticeBoundaryCondition2D<T,DESCRIPTOR>* PlbXmlController2D::createBoundaryCondition()
{
  std::string type;
  try{
    plbCase["bcType"].read(type);
  } catch(PlbIOException &e) {
    plbIOError("No boundary condition type specified");
  }

  if(type.compare("regularized") == 0)
    return createLocalBoundaryCondition2D<T,DESCRIPTOR>();

  if(type.compare("interpolation") == 0)
    return createInterpBoundaryCondition2D<T,DESCRIPTOR>();

  if(type.compare("zou/he") == 0)
    return createZouHeBoundaryCondition2D<T,DESCRIPTOR>();
  
  if(type.compare("inamuro") == 0)
     return createInamuroBoundaryCondition2D<T,DESCRIPTOR>();

  plbIOError("Invalid boundary condition type specified");

  return 0;
}

/*
 * ---------------------------------------------------------------
 * lattice initializer functions
 * ---------------------------------------------------------------
 */

void PlbXmlController2D::initializeLattice()
{
  setDynamics();
  setBoundaries();

  initializeAtEquilibrium(lattice,lattice.getBoundingBox(),1.,Array<T,2>(0.,0.));

  if(ioUtils::elementExists(plbCase,"initValues"))
    setInitValsFromFile();

  lattice.initialize();
}

void PlbXmlController2D::setDynamics()
{
  bool dummy, flag(true);
  if(ioUtils::elementExists(plbCase,"dynamicsFromRegion")){
    XMLreaderProxy dyn = plbCase["dynamicsFromRegion"];
    for (; dyn.isValid(); dyn = dyn.iterId()) {
      std::string regionId;
      dyn["regionId"].read(regionId);
      Box2D reg = (regionList.find(regionId))->second;
      defineDynamics(lattice,reg,
		     dynamicsFromXML(dyn["type"]));
    }
  }
  if(ioUtils::elementExists(plbCase,"dynamicsFromFile")){
    XMLreaderProxy dyn = plbCase["dynamicsFromFile"];
    for (; dyn.isValid(); dyn = dyn.iterId()) {
      std::string fname;
      plint maskVal;
      dyn["fileName"].read(fname);
      dyn["maskVal"].read(maskVal);
      MultiScalarField2D<int> intMask(params.getNx(), params.getNy());
      
      plb_ifstream ifile(fname.c_str());
      ifile >> intMask;
      
      defineDynamics(lattice, intMask, dynamicsFromXML(dyn["type"]), maskVal);
    }
  }
  

}

void PlbXmlController2D::setBoundaries()
{
  // iterate over boundary list to create boundary blocks
  BoundaryListIterator b;
  for(b = boundaryList.begin(); b != boundaryList.end(); b++){
    BoundaryClass2D const &bc = b->second;
    Box2D reg = bc.getRegion();
    if(bc.getBoundaryType() == VELOCITY){
      pcout << "Velocity boundary condition set" << std::endl;
      boundaryCondition->setVelocityConditionOnBlockBoundaries(lattice,reg,bc.getPlbBcType());
    }
    else if(bc.getBoundaryType() == PRESSURE){
      pcout << "Pressure boundary condition set" << std::endl;
      boundaryCondition->setPressureConditionOnBlockBoundaries(lattice,reg,bc.getPlbBcType());
    }
  }

}

void PlbXmlController2D::setInitValsFromFile()
{
  XMLreaderProxy x = plbCase["initValues"];
  std::string fname;
  
  if(ioUtils::elementExists(x,"pressureFile")){
    x["pressureFile"].read(fname);
    initializeAtEquilibrium(lattice,lattice.getBoundingBox(),
			    ioUtils::SetPressureFromFile(this,fname));
  }
  if(ioUtils::elementExists(x,"vxFile")){
    x["vxFile"].read(fname);
    initializeAtEquilibrium(lattice,lattice.getBoundingBox(),
			    ioUtils::SetVelocityFromFile(this,fname,0));
  }
  if(ioUtils::elementExists(x,"vyFile")){
    x["vyFile"].read(fname);
    initializeAtEquilibrium(lattice,lattice.getBoundingBox(),
			    ioUtils::SetVelocityFromFile(this,fname,1));
  }
    
}

/*
 * -----------------------------------------------------------------
 * run
 * -----------------------------------------------------------------
 */

void PlbXmlController2D::doStep()
{
  static bool init = true;
  if(init){
    performActions(0);
    iStep = 1;
    init=false;
  }

  lattice.collideAndStream();
  performActions(iStep++);
}

void PlbXmlController2D::run(plint nSteps_)
{
  for(plint i=1;i<=nSteps_;i++){
    doStep();
  }
}

void PlbXmlController2D::performActions(plint step)
{
  
  for(ActionListIterator it=actionList.begin(); it != actionList.end(); ++it){
    if((it->second)->performAtStep(step)){
      Task::TaskList const t = (it->second)->getTaskList();
      pcout << "Performing action " << it->first << " at step " << step << std::endl;
      for(Task::TaskListConstIterator tlIt = t.begin();
	 tlIt != t.end(); ++tlIt){
	(*tlIt)->perform(lattice,step);
      }
    }
  }
}

/*
 * -----------------------------------------------------------------
 * constructor and destructor
 * -----------------------------------------------------------------
 */

PlbXmlController2D::PlbXmlController2D(std::string &fname)
  : reader(fname), plbCase(reader["plbCase"]),
    units(calcUnits()), params(calcParams()), 
    lattice(params.getNx(),params.getNy(),new NoDynamics<T,DESCRIPTOR>()),
    boundaryCondition(createBoundaryCondition()),
    nSteps(0), iStep(0)
{
  buildRegionList();
  buildBoundaryList();
  buildActionList();

  initializeLattice();
  T time;
  plbCase["run"].read(time);
  nSteps = units.numTimeSteps(time);
  
  pcout << "Running for " << time << " seconds of physical time\n"
	<< units.numTimeSteps(1) << " steps per second, " << nSteps << " total" << std::endl;

  if(params.getOmega() < 0.5)
    plbIOError("Omega too small (< 0.5)!");
}

PlbXmlController2D::~PlbXmlController2D()
{

}

