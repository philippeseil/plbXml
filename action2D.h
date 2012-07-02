
#ifndef ACTION2D_H_LBDEM
#define ACTION2D_H_LBDEM

#include <utility>
#include <map>
#include <string>
#include <exception>

#include "task2D.h"

namespace plb{
  class XMLreaderProxy;
};

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

  
  Action2D actionFromXml(XMLreaderProxy const &a);  
};


#endif /* ACTION2D_H_LBDEM */
