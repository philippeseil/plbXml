/* --------------------------------------------------------------------- 

Copyright 2012 JKU Linz
Author: Philippe Seil (philippe.seil@jku.at)

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



#ifndef ACTION2D_H_LBDEM
#define ACTION2D_H_LBDEM

#include <utility>
#include <map>
#include <string>
#include <exception>

#include "taskBase.h"
#include "taskFactory2D.h"
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
