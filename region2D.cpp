#include "region2D.h"

#include "plbHeaders2D.h"

namespace Region{
  Region2D regionFromXml(XMLreaderProxy const &r)
  {
    std::string id;
    plint x0,x1,y0,y1;
    try{
      r["id"].read(id);
    } catch (PlbIOException &e){
      throw PlbIOException("Invalid Region command: No id specified");
    }

    try{
      r["x0"].read(x0);
      r["x1"].read(x1);
      r["y0"].read(y0);
      r["y1"].read(y1);
    } catch(PlbIOException &e){
      throw PlbIOException("Invalid Region command: size specifications missing");
    }

    if( id.compare("") == 0 )
      throw PlbIOException("Invalid Region command: Unnamed region");
    if( x0<0 || y0<0 || x1<0 || y1<0 || x1<x0 || y1<y0 ){
      std::string errmsg("Invalid Region command: Bad size in region ");
      errmsg.append(id);
      throw PlbIOException(errmsg);
    }
      
    return Region2D(id,Box2D(x0,x1,y0,y1));
  }

};
