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


#ifndef IOUTILS_H_LBDEM
#define IOUTILS_H_LBDEM

#include <string>
#include "plbHeaders2D.h"
#include "globalDefs.h"
class PlbXmlController2D;

namespace plb{
  class XMLreaderProxy;
}
namespace ioUtils{
  bool elementExists(plb::XMLreaderProxy const &reader, std::string const &elemId);
  plb::Box2D bcBoxFromXml(PlbXmlController2D const *controller, XMLreaderProxy const &r);
  

  class SetValueFromFile{
  public:
    SetValueFromFile(PlbXmlController2D const *controller, std::string const &fname);
    SetValueFromFile(SetValueFromFile const &orig);
    virtual ~SetValueFromFile();
    virtual void operator() (plb::plint iX, plb::plint iY, T& density, 
			     plb::Array<T,2>& velocity) const =0;
  protected:
    plb::MultiScalarField2D<T> *val;
    PlbXmlController2D const *controller;
  };

  class SetPressureFromFile : public SetValueFromFile {
  public:
    SetPressureFromFile(PlbXmlController2D const *controller, std::string const &fname);
    SetPressureFromFile(SetPressureFromFile const &orig);
    virtual void operator() (plb::plint iX, plb::plint iY, T& density, plb::Array<T,2>& velocity) const;
  };

  class SetVelocityFromFile : public SetValueFromFile {
  public:
    SetVelocityFromFile(PlbXmlController2D const *controller, std::string const &fname, plint dim);
    SetVelocityFromFile(SetVelocityFromFile const &orig);
    virtual void operator() (plb::plint iX, plb::plint iY, T& density, plb::Array<T,2>& velocity) const;
  private:
    plint dim;
  };
}

#endif // IOUTILS_H_LBDEM
