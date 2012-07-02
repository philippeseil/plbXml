/*
 * handling of boundary conditions
 * currently, only bc on block boundaries are supported
 */

#ifndef BOUNDARY2D_H_LBDEM
#define BOUNDARY2D_H_LBDEM

#include "region2D.h"
#include "boundaryCondition/boundaryCondition.h"

class PlbXmlController2D;

namespace plb{
  class XMLreaderProxy;
};

namespace Boundary{
    
  enum BoundaryType { VELOCITY, PRESSURE };
  class BoundaryClass2D {
  public:
    BoundaryClass2D(PlbXmlController2D const *controller_,
		    BoundaryType const t_,
		    plb::boundary::BcType const &plbBcType_,
		    Region::ConstRegionListIterator const reg_)
      : controller(controller_), type(t_), plbBcType(plbBcType_), reg(reg_) {}


    const BoundaryType getBoundaryType() const { return type;}
    const plb::boundary::BcType getPlbBcType() const { return plbBcType;}
    const Region::ConstRegionListIterator& getRegion() const { return reg;}

  private:
    BoundaryType type;
    plb::boundary::BcType plbBcType;
    Region::ConstRegionListIterator reg;
    PlbXmlController2D const * controller;
  };

  typedef std::pair<std::string,BoundaryClass2D> Boundary2D;
  typedef std::map<std::string,BoundaryClass2D> BoundaryList;
  typedef std::map<std::string,BoundaryClass2D>::iterator BoundaryListIterator;
  typedef std::map<std::string,BoundaryClass2D>::const_iterator ConstBoundaryListIterator;

  Boundary2D boundaryFromXml(PlbXmlController2D const *controller, plb::XMLreaderProxy const &b);

};

#endif /* BOUNDARY2D_H_LBDEM */
