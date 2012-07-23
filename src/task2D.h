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


/*
 * aggregate header for task mechanism
 */

#ifndef TASK2D_H_LBDEM
#define TASK2D_H_LBDEM

#include <list>

#include "taskClasses2D.h"
#include "taskFactory2D.h"

using namespace plb;

namespace Task{

  typedef std::list<TaskBase*> TaskList;
  typedef std::list<TaskBase*>::iterator TaskListIterator;
  typedef std::list<TaskBase*>::const_iterator TaskListConstIterator;

};

#endif /* TASK2D_H_LBDEM */
