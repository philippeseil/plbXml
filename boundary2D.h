/*
 * handling of boundary conditions
 * currently, only bc on block boundaries are supported
 */

#include "palabos2D.h"
#include "palabos2D.hh"

#include "region2D.h"

namespace Boundary{

  enum BoundaryType { VELOCITY, PRESSURE };
  class BoundaryClass2D {
  public:
    BoundaryClass2D(BoundaryType const t_,
		    plb::boundary::BcType const &plbBcType_,
		    Region::ConstRegionListIterator const reg_)
      : type(t_), plbBcType(plbBcType_), reg(reg_) {}


    const BoundaryType getBoundaryType() const { return type;}
    const plb::boundary::BcType getPlbBcType() const { return plbBcType;}
    const Region::ConstRegionListIterator& getRegion() const { return reg;}

  private:
    BoundaryType type;
    plb::boundary::BcType plbBcType;
    Region::ConstRegionListIterator reg;
  };

  typedef std::pair<std::string,BoundaryClass2D> Boundary2D;
  typedef std::map<std::string,BoundaryClass2D> BoundaryList;
  typedef std::map<std::string,BoundaryClass2D>::iterator BoundaryListIterator;
  typedef std::map<std::string,BoundaryClass2D>::const_iterator ConstBoundaryListIterator;

  Boundary2D boundaryFromXml(XMLreaderProxy const &b, Region::RegionList const &l)
  {
    std::string id;
    std::string regionId;
    BoundaryType bcType;
    plb::boundary::BcType plbBcType;
    Region::ConstRegionListIterator reg;

    try{
      b["id"].read(id);
    } catch (PlbIOException &e){
      throw PlbIOException("Invalid Boundary command: No id specified!");
    }

    try{
      b["regionId"].read(regionId);
      reg = l.find(regionId);
      if(reg == l.end())
	throw PlbIOException("dummy");
    } catch (PlbIOException &e){
      throw PlbIOException("Invalid Boundary command: Invalid or no regionId specified!");
    }

    std::vector<std::string> bcTypeRead;
    try{
      b["type"].read(bcTypeRead);
      if(bcTypeRead.size() == 0 || bcTypeRead.size() > 2) throw PlbIOException("dummy");

      if(bcTypeRead[0].compare("velocity") == 0)
	bcType = VELOCITY;
      else if(bcTypeRead[0].compare("pressure") == 0)
	bcType = PRESSURE;
      else throw PlbIOException("dummy");

      if(bcTypeRead.size() == 1 || bcTypeRead[1].compare("dirichlet") == 0)
	plbBcType = boundary::dirichlet;
      else if(bcTypeRead[1].compare("outflow") == 0 || bcTypeRead[1].compare("neumann") == 0)
	plbBcType = boundary::neumann;
      else if(bcType == VELOCITY) {
	if(bcTypeRead[1].compare("freeslip") == 0)
	  plbBcType = boundary::freeslip;
	else if(bcTypeRead[1].compare("normalOutflow") == 0)
	  plbBcType = boundary::normalOutflow;
	else throw PlbIOException("dummy");
      } else throw PlbIOException("dummy");

    } catch (PlbIOException &e){
      std::string errmsg("Invalid boundary command ");
      errmsg.append(id);
      errmsg.append(": invalid boundary type"); 
      throw PlbIOException(errmsg);
    }    

    return Boundary2D(id,BoundaryClass2D(bcType,plbBcType,reg));
  }

};
