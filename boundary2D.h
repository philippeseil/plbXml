/*
 * handling of boundary conditions
 * currently, only bc on block boundaries are supported
 */

#ifndef BOUNDARY2D_H_LBDEM
#define BOUNDARY2D_H_LBDEM

#include "region2D.h"
#include "boundaryCondition/boundaryCondition.h"
#include "core/geometry2D.h"

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
		    Region::ConstRegionListIterator const reg_);

    const BoundaryType getBoundaryType() const { return type;}
    const plb::boundary::BcType getPlbBcType() const { return plbBcType;}
    plb::Box2D getRegion() const;

  private:
    BoundaryType type;
    plb::boundary::BcType plbBcType;
    plb::Box2D reg;
    PlbXmlController2D const *controller;
  };

  typedef std::pair<std::string,BoundaryClass2D> Boundary2D;
  typedef std::map<std::string,BoundaryClass2D> BoundaryList;
  typedef std::map<std::string,BoundaryClass2D>::iterator BoundaryListIterator;
  typedef std::map<std::string,BoundaryClass2D>::const_iterator ConstBoundaryListIterator;

  Boundary2D boundaryFromXml(PlbXmlController2D const *controller, plb::XMLreaderProxy const &b);

};

#endif /* BOUNDARY2D_H_LBDEM */
