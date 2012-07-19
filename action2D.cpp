#include "action2D.h"
#include "plbXmlController2D.h"
#include "units.h"
namespace Action {

  /*
   * implementation of ActionClass2D
   */
  ActionClass2D::ActionClass2D(PlbXmlController2D const *controller_)
    : controller(controller_) {}

  ActionClass2D::~ActionClass2D() {}

  Task::TaskList const & ActionClass2D::getTaskList() const
  {
    return tasklist;
  }

  void ActionClass2D::addTask(Task::TaskBase *ptr)
  {
    tasklist.push_back(ptr);
  }

  /*
   * implementation of PeriodicAction2D
   */

  PeriodicAction2D::PeriodicAction2D(PlbXmlController2D const *controller_, 
		     plint const start_, plint const period_, plint const end_)
      : ActionClass2D(controller_), start(start_),period(period_),end(end_) {}
  PeriodicAction2D::~PeriodicAction2D() {}
  bool PeriodicAction2D::performAtStep(plint n) const 
  { 
    return n%period==0 && (n>=start || start == -1) && (n<end || end == -1);
  }

  /*
   * implementation of OnceAction2D
   */
  OnceAction2D::OnceAction2D(PlbXmlController2D const *controller_, plint const t_)
      : ActionClass2D(controller_), t(t_) {}
  OnceAction2D::~OnceAction2D() {}
  bool OnceAction2D::performAtStep(plint n) const { return (n==t);}


  Action2D actionFromXml(PlbXmlController2D const  *controller, XMLreaderProxy const &a)
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
	T physT = atof(typeRead.at(1).c_str());
	plint t = controller->getUnits().numTimeSteps(physT);

	if(t<0) throw PlbIOException("dummy");

	actPtr = new OnceAction2D(controller,t);

      } else if(typeRead.at(0).compare("periodic") == 0){
	T tStart = atof(typeRead.at(1).c_str());
	T tPeriod = atof(typeRead.at(2).c_str());
	T tEnd = atof(typeRead.at(3).c_str());
	
	plint nStart = tStart < 0 ? -1 : controller->getUnits().numTimeSteps(tStart);
	plint nPeriod = controller->getUnits().numTimeSteps(tPeriod);
	plint nEnd = tEnd < 0 ? -1 : controller->getUnits().numTimeSteps(tEnd);

	if(nPeriod < 1) nPeriod == 1;
	
	if( nStart<-1 || (nEnd<=nStart && nEnd != -1) ) throw PlbIOException("dummy");

	actPtr = new PeriodicAction2D(controller,nStart,nPeriod,nEnd);

      } else throw PlbIOException("dummy");

    } catch (std::exception &e){
      throw PlbIOException("Invalid Action command with id " + id + ": Unknowkn or no type specified");
    }

    std::vector<XMLreader*> v = a.getChildren();
    for(int i=0;i<v.size();i++){
      if( (v[i]->getName().compare("id") == 0)
	  || (v[i]->getName().compare("type") == 0) )
	continue;

      plint id = v[i]->getFirstId();
      do{
	XMLreaderProxy p(v[i],id);
	actPtr->addTask(Task::cont.f.create(controller, p));
      } while (v[i]->getNextId(id));
    }
    return Action2D(id,actPtr);
  }

}; // namespace Action
