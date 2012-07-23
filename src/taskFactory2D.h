/* --------------------------------------------------------------------- 

Copyright 2012 Philippe Seil

This file is part of plbXml.

plbXml is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation, either version 2 of the License, or (at
your option) any later version.

plbXml is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with plbXml. If not, see http://www.gnu.org/licenses/.

---------------------------------------------------------------------- */


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
