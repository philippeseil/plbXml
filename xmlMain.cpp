/*
 * main file to test functions of plbXmlController2D
 */

#include "plbHeaders2D.h"

#include "plbXmlController2D.h"
#include "region2D.h"
#include "globalDefs.h"
#include "task2D.h"

#include <string>
#include <iostream>


int main(int argc, char **argv)
{
  plb::plbInit(&argc,&argv);

  std::string fName;
  global::argv(1).readNoThrow(fName);

  PlbXmlController2D p(fName);

  p.run(100000);

  return 0;
}
