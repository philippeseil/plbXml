/*
 * aggregate header for task mechanism
 */

#ifndef TASK2D_H_LBDEM
#define TASK2D_H_LBDEM

#include "palabos2D.h"
#include "palabos2D.hh"

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
