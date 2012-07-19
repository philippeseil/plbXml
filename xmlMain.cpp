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
