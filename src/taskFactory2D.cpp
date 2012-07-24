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


#include "taskFactory2D.h"
#include "ioUtils.h"
#include "taskFactoryAggregateHeader2D.hh"

#include "plbXmlController2D.h"
#include "plbHeaders2D.h"

using namespace plb;

namespace Task{
  
  TaskFactory::TaskFactory()
  {
    #include "taskFactoryInitializer2D.hh"
  }
  TaskFactory::~TaskFactory()
  {
    for ( TaskMap::iterator it=taskMap.begin() ; it != taskMap.end(); it++ )
      delete it->second;
  }

  TaskBase* TaskFactory::create(PlbXmlController2D const *controller,
				XMLreaderProxy const &t)
  {
    std::string type = t.getName();
    TaskMap::iterator pos = taskMap.find(type);
    if(pos != taskMap.end()){
      pcout << "Creating task of type " << type << std::endl;
      return pos->second->create(controller,t);
    } else{
      pcout << "Task type " << type << " not found" << std::endl;
      return 0;
    }
  }



};
