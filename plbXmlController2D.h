/*
 * plbXmlController2D.h
 * provides an xml interface to palabos
 */

#include "palabos2D.h"
#include "palabos2D.hh"

#include <string>

using namespace plb;

template<typename T>
class PlbXmlController2D {
public:
  PlbXmlController2D(std::string &fname);
  ~PlbXmlController2D();

  IncomprFlowParam<T> getParams();

  plint i;

private:
  XMLreader reader;
};

template<typename T>
PlbXmlController2D<T>::PlbXmlController2D(std::string &fname)
  : reader(fname)
{
  reader["plbCase"]["test"].read(i);
}

template<typename T>
PlbXmlController2D<T>::~PlbXmlController2D()
{

}

template<typename T>
PlbXmlController2D<T>::getParams()
{
  
}
