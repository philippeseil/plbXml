
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
    plint get() { return i;}
  private:
    plint i
  };

  class CompareActions {
  public:
    CompareActions(std::vector<std::string> &v_);
    bool operator() (std::string const &lhs, std::string const &rhs);
  private:
    std::vector<std::string> v;
    plint getIndex(std::string const &s);
  };

  

  typedef std::pair<std::string,ActionClass2D> Action2D;
  typedef std::map<std::string,ActionClass2D,CompareActions> ActionList;
  typedef std::map<std::string,ActionClass2D,CompareActions>::iterator ActionListIterator;
  
  typename Action2D actionFromXml(XMLreaderProxy const &a)
  {
    std::string id;
    plint i;
    a["id"].read(id);
    a["v"].read(i);
    return Action2D(id,ActionClass2D(i));
  }
  
  CompareActions::CompareActions(std::vector<std::string> &v_)
    : v(v_) {}

  bool CompareActions::operator() (std::string const &lhs, std::string const &rhs)
  {
    plint i1 = getIndex(lhs);
    plint i2 = getIndex(rhs);
    
    if(i1 == -1 || i2 == -1){
      // do something...
    }
      
    return (i1 > i2);
  }

  plint CompareActions::getIndex(std::string const &s)
  {
    plint ind = -1;

    for(plint i=0;i<v.size();i++)
      if(s.compare(v[i]) == 0){
	ind=i;
	break;
      }

    return ind;
  }
};


#endif /* ACTION2D_H_LBDEM */
