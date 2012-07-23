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


#ifndef TASK_BASE_LBDEM
#define TASK_BASE_LBDEM

#include "plbHeaders2D.h"
#include "globalDefs.h"

class PlbXmlController2D;

using namespace plb;

namespace Task {
  class TaskBase{
  protected:
    TaskBase(PlbXmlController2D const *controller_, int id_) 
      : controller(controller_), id(id_) {}
    PlbXmlController2D const *controller;
  public:
    virtual void perform(MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
			 plint nStep) =0;
    virtual ~TaskBase() {}

    int id;

    bool operator<(TaskBase &rhs){
      return id < rhs.id;
    }
  };
} // namespace Task
#endif /* TASK_BASE_LBDEM */
