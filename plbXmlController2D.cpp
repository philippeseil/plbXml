
#include "plbXmlController2D.h"
#include "ioUtils.h"
/*
 * ------------------------------------------------------------------
 * getters for various lists
 * ------------------------------------------------------------------
 */

const IncomprFlowParam<T>&  PlbXmlController2D::getParams() const
{
  return params;
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

IncomprFlowParam<T> PlbXmlController2D::calcParams()
{
  XMLreaderProxy p(plbCase["parameters"]);
  
  T physU(1.),latticeU(0.),Re(0.),physLength(1.),lx(0.),ly(0.);
  plint res(1);

  p["latticeU"].read(latticeU);
  p["Re"].read(Re);
  p["lx"].read(lx);
  p["ly"].read(ly);
  p["Resolution"].read(res);

  return IncomprFlowParam<T>(physU,latticeU,Re,physLength,res,lx,ly);
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
 * lattice initializer
 * ---------------------------------------------------------------
 */

void PlbXmlController2D::initializeLattice()
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
  initializeAtEquilibrium(lattice,lattice.getBoundingBox(),1.,Array<T,2>(0.,0.));

  lattice.initialize();
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
      for(Task::TaskListConstIterator tlIt = t.begin();
	 tlIt != t.end(); ++tlIt){
	(*tlIt)->perform(lattice,*boundaryCondition,step);
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
    params(calcParams()), 
    lattice(params.getNx(),params.getNy(),new NoDynamics<T,DESCRIPTOR>()),
    boundaryCondition(createBoundaryCondition()),
    nSteps(0), iStep(0)
{
  buildRegionList();
  buildBoundaryList();
  buildActionList();

  initializeLattice();
  plbCase["run"].read(nSteps);

  pcout << "Lattice size: " << params.getNx() << " " << params.getNy() << std::endl;
  pcout << "Lattice U   : " << params.getLatticeU()<< std::endl;
  pcout << "omega       : " << params.getOmega() << std::endl;
}

PlbXmlController2D::~PlbXmlController2D()
{

}

