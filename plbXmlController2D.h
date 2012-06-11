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
  XMLreaderProxy plbCase;
};

template<typename T>
PlbXmlController2D<T>::PlbXmlController2D(std::string &fname)
  : reader(fname), plbCase(reader["plbCase"])
{
  plbCase["test"].read(i);
}

template<typename T>
PlbXmlController2D<T>::~PlbXmlController2D()
{

}

template<typename T>
IncomprFlowParam<T> PlbXmlController2D<T>::getParams()
{
  XMLreaderProxy p(plbCase["parameters"]);
  
  T physU(1.),latticeU(0.),Re(0.),physLength(1.),lx(0.),ly(0.);
  plint res(1);

  p["latticeU"].read(latticeU);
  p["Re"].read(Re);
  p["lx"].read(lx);
  p["ly"].read(ly);
  p["Resolution"].read(res);

  return IncomprFlowParam<T>(physU,latticeU,Re,physLength,res,lx,ly);
}

