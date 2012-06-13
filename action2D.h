
#ifndef ACTION2D_H_LBDEM
#define ACTION2D_H_LBDEM

#include "palabos2D.h"
#include "palabos2D.hh"

#include <utility>
#include <map>
#include <string>

using namespace plb;

namespace Action{
  
  class ActionClass2D {
  public:
    ActionClass2D(plint i_) : i(i_) {}
    //  ActionClass2D(ActionClass2D const &orig) : i(orig.i) {}
    plint get() { return i;}
  private:
    plint i;
  };

  typedef std::pair<std::string,ActionClass2D> Action2D;
  typedef std::map<std::string,ActionClass2D> ActionList;
  typedef std::map<std::string,ActionClass2D>::iterator ActionListIterator;
  
  Action2D actionFromXml(XMLreaderProxy const &a)
  {
    std::string id;
    plint i;
    try{
      a["id"].read(id);
    } catch (PlbIOException &e){
      throw PlbIOException("Invalid Action command: No id specified!");
    }
    if(id.compare("") == 0)
      throw PlbIOException("Invalid Action command: Unnamed Action");

    // this is to be replaced by a creation of associated objects
    a["v"].read(i);
    return Action2D(id,ActionClass2D(i));
  }
  
};


#endif /* ACTION2D_H_LBDEM */
