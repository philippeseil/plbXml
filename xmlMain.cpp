/*
 * main file to test functions of plbXmlController2D
 */

#include "palabos2D.h"
#include "palabos2D.hh"

#include "plbXmlController2D.h"
#include "region2D.h"

#include <string>
#include <iostream>

typedef double T;

int main(int argc, char **argv)
{
  plb::plbInit(&argc,&argv);

  std::string fName;
  global::argv(1).readNoThrow(fName);

  PlbXmlController2D<T> p(fName);


  std::string id("id");

  Region::RegionList list(p.getRegionList());

  std::cout << list.size() << std::endl;
  for(Region::RegionListIterator it = list.begin(); it != list.end(); it++)
    std::cout << (*it).first << std::endl;
  return 0;
}
