/*
 * main file to test functions of plbXmlController2D
 */

#include "palabos2D.h"
#include "palabos2D.hh"

#include "plbXmlController2D.h"

#include <string>
#include <iostream>

typedef double T;

int main(int argc, char **argv)
{
  plb::plbInit(&argc,&argv);

  std::string fName;
  global::argv(1).readNoThrow(fName);

  PlbXmlController2D<T> p(fName);

  std::cout << p.i << std::endl;

  return 0;
}
