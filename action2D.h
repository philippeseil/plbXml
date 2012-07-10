
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

class PlbXmlController2D;

using namespace plb;

namespace Action{
  class ActionClass2D;

  typedef std::pair<std::string,ActionClass2D*> Action2D;
  typedef std::map<std::string,ActionClass2D*> ActionList;
  typedef std::map<std::string,ActionClass2D*>::const_iterator ActionListIterator;
  
  class ActionClass2D {
  public:
    ActionClass2D(PlbXmlController2D const *controller_);
    virtual ~ActionClass2D();
    
    plint const get() const {return i;} 
    virtual bool performAtStep(plint n) const =0; 

    Task::TaskList const & getTaskList() const;

    friend Action2D actionFromXml(PlbXmlController2D const *controller, XMLreaderProxy const &a);

  protected:
    PlbXmlController2D const *controller;

  private:
    plint i;
    Task::TaskList tasklist;
    void addTask(Task::TaskBase *ptr);

  };
  
  class PeriodicAction2D : public ActionClass2D{
  public:
    PeriodicAction2D(PlbXmlController2D const *controller_, 
		     plint const start_, plint const period_, plint const end_);
    ~PeriodicAction2D();
    virtual bool performAtStep(plint n) const;

    friend Action2D actionFromXml(XMLreaderProxy const &a);
  private:
    plint start, period, end;
  };

  class OnceAction2D : public ActionClass2D{
  public:
    OnceAction2D(PlbXmlController2D const *controller_, plint const t_);
    ~OnceAction2D();
    virtual bool performAtStep(plint n) const;

    friend Action2D actionFromXml(XMLreaderProxy const &a);
  private:
    plint t;
  };

  
  Action2D actionFromXml(PlbXmlController2D const *controller, XMLreaderProxy const &a);  
};


#endif /* ACTION2D_H_LBDEM */
