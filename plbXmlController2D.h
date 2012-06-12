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

  const IncomprFlowParam<T>& getParams() const;

  plint i;

private:
  IncomprFlowParam<T> calcParams();


  XMLreader reader;
  XMLreaderProxy plbCase;
  IncomprFlowParam<T> params;
};

template<typename T>
const IncomprFlowParam<T>&  PlbXmlController2D<T>::getParams() const
{
  return params;
}


template<typename T>
IncomprFlowParam<T> PlbXmlController2D<T>::calcParams()
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




template<typename T>
PlbXmlController2D<T>::PlbXmlController2D(std::string &fname)
  : reader(fname), plbCase(reader["plbCase"]),
    params(this->calcParams())
{
  plbCase["test"].read(i);
}

template<typename T>
PlbXmlController2D<T>::~PlbXmlController2D()
{

}

