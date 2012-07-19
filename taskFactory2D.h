#ifndef TASKFACTORY2D_H_LBDEM
#define TASKFACTORY2D_H_LBDEM

#include "plbHeaders2D.h"

#include "taskBase.h"

using namespace plb;

namespace Task {

  typedef std::list<TaskBase*> TaskList;
  typedef std::list<TaskBase*>::iterator TaskListIterator;
  typedef std::list<TaskBase*>::const_iterator TaskListConstIterator;

  struct SingleTaskFactoryBase{
    virtual TaskBase* create(PlbXmlController2D const *controller,
			     XMLreaderProxy const &t) =0;
    virtual ~SingleTaskFactoryBase() {};
  };

  template<typename T>
  struct SingleTaskFactory : public SingleTaskFactoryBase {
    virtual TaskBase* create(PlbXmlController2D const *controller,
			     XMLreaderProxy const &t);
  };

  class TaskFactory {
  public:
    TaskFactory();
    TaskBase* create(PlbXmlController2D const *controller,
		     XMLreaderProxy const &t);

  private:
    typedef std::map<std::string,SingleTaskFactoryBase*> TaskMap;
    TaskMap taskMap;
    template<typename T>
    void addToTaskMap(std::string const &id)
    {
      taskMap.insert(std::make_pair(id,new SingleTaskFactory<T>));
    }
  };
  
  template<typename T>
  TaskBase* SingleTaskFactory<T>::create(PlbXmlController2D const *controller,
					 XMLreaderProxy const &t)
  {
    return new T(controller,t);
  }


  struct TaskFactoryContainer {
    TaskFactory f;
  };

  static TaskFactoryContainer cont;
};


#endif /* TASKFACTORY2D_H_LBDEM */
