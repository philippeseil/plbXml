
#ifndef ACTION2D_H_LBDEM
#define ACTION2D_H_LBDEM

#include "palabos2D.h"
#include "palabos2D.hh"

#include <utility>
#include <map>
#include <string>
#include <exception>

#include "taskFactory2D.h"

using namespace plb;

namespace Action{
  class ActionClass2D;

  typedef std::pair<std::string,ActionClass2D*> Action2D;
  typedef std::map<std::string,ActionClass2D*> ActionList;
  typedef std::map<std::string,ActionClass2D*>::const_iterator ActionListIterator;
  
  class ActionClass2D {
  public:
    ActionClass2D() {}
    virtual ~ActionClass2D() {}
    ActionClass2D(ActionClass2D const &orig) : i(orig.i) {}
    
    plint const get() const {return i;} 
    virtual bool performAtStep(plint n) const =0; 

    Task::TaskList const getTaskList() const { return tasklist; }

    friend Action2D actionFromXml(XMLreaderProxy const &a);
  private:
    plint i;
    Task::TaskList tasklist;

    void addTask(Task::TaskBase *ptr) { tasklist.push_back(ptr); }

  };

  class PeriodicAction : public ActionClass2D{
  public:
    PeriodicAction(plint const start_, plint const period_, plint const end_)
      : ActionClass2D (), start(start_),period(period_),end(end_) {}
    ~PeriodicAction() {}
    virtual bool performAtStep(plint n) const { return (n>=start && n<end && n%period==0);}

    friend Action2D actionFromXml(XMLreaderProxy const &a);
  private:
    plint start, period, end;
  };

  class OnceAction : public ActionClass2D{
  public:
    OnceAction(plint const t_)
      : ActionClass2D (), t(t_) {}
    ~OnceAction() {}
    virtual bool performAtStep(plint n) const { return (n==t);}

    friend Action2D actionFromXml(XMLreaderProxy const &a);
  private:
    plint t;
  };

  
  Action2D actionFromXml(XMLreaderProxy const &a)
  {
    std::string id;
    ActionClass2D *actPtr;

    try{
      a["id"].read(id);
    } catch (PlbIOException &e){
      throw PlbIOException("Invalid Action command: No id specified!");
    }
    if(id.compare("") == 0)
      throw PlbIOException("Invalid Action command: Unnamed Action");

    try{
      std::vector<std::string> typeRead;
      a["type"].read(typeRead);

      if(typeRead.at(0).compare("once") == 0){
	plint t = atoi(typeRead.at(1).c_str());

	if(t<0) throw PlbIOException("dummy");

	actPtr = new OnceAction(t);

      } else if(typeRead.at(0).compare("periodic") == 0){
	plint nStart = atoi(typeRead.at(1).c_str());
	plint nPeriod = atoi(typeRead.at(2).c_str());
	plint nEnd = atoi(typeRead.at(3).c_str());

	if(nStart<0 || nEnd<=nStart || nPeriod<1) throw PlbIOException("dummy");

	actPtr = new PeriodicAction(nStart,nPeriod,nEnd);

      } else throw PlbIOException("dummy");

    } catch (std::exception &e){
      throw PlbIOException("Invalid Action command: Unknowkn or no type specified");
    }

    std::vector<XMLreader*> v = a.getChildren();
    for(int i=0;i<v.size();i++){
      if( (v[i]->getName().compare("id") == 0)
	  || (v[i]->getName().compare("type") == 0) )
	continue;

      plint id = v[i]->getFirstId();
      do{
	XMLreaderProxy p(v[i],id);
	actPtr->addTask(Task::taskFromXml(p));
      } while (v[i]->getNextId(id));
    }
    return Action2D(id,actPtr);
  }
  
};


#endif /* ACTION2D_H_LBDEM */
