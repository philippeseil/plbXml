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
  try{
    global::argv(1).readNoThrow(fName);
  } catch(PlbIOException &e) {
    pcout << "No input file specified" << std::endl;
    return 1;
  }

  std::ifstream test(fName.c_str());
  if(test.good()){
    test.close();
  } else{
    pcout << "Input file " << fName 
	  << " not found. Usage: plbXml [infile.xml]" << std::endl;
    return 1;
  }
  PlbXmlController2D p(fName);
  plint n = p.getNumSteps();
  p.run(n);

  return 0;
}
