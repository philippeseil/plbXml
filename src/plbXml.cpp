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
 * main file to test functions of plbXmlController2D
 */

#include "plbHeaders2D.h"

#include "plbXmlController2D.h"
#include "region2D.h"
#include "globalDefs.h"
#include "taskFactory2D.h"

#include <string>
#include <iostream>


int main(int argc, char **argv)
{
  plb::plbInit(&argc,&argv);

  std::string fName;
  global::argv(1).readNoThrow(fName);

  PlbXmlController2D p(fName);
  plint n = p.getNumSteps();
  p.run(n);

  return 0;
}
