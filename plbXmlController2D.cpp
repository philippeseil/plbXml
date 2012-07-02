
#include "plbXmlController2D.h"

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

const PlbXmlController2D::Timeline& PlbXmlController2D::getTimeline() const
{
  return timeline;
}

const BoundaryList& PlbXmlController2D::getBoundaryList() const
{
  return boundaryList;
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
    inserted = actionList.insert(actionFromXml(act));
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
void PlbXmlController2D::buildTimeline()
{
  try{
    plbCase["timeline"].read(timeline);
  } catch (PlbIOException &e){
    throw PlbIOException("Error: No timeline specified");
  }
}

/*
 * -----------------------------------------------------------------
 * constructor and destructor
 * -----------------------------------------------------------------
 */

PlbXmlController2D::PlbXmlController2D(std::string &fname)
  : reader(fname), plbCase(reader["plbCase"]),
    params(this->calcParams())
{
  buildRegionList();
  //  buildActionList();
  buildBoundaryList();
  //  buildTimeline();
  // TODO check correctness of case ...
}

PlbXmlController2D::~PlbXmlController2D()
{

}

