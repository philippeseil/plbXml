/* --------------------------------------------------------------------- 

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


/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2006, 2007, 2011 Jonas Latt, Mathias J. Krause,
 *  Jonas Kratzke
 *  E-mail contact: info@openlb.net
 *  The most recent release of OpenLB can be downloaded at
 *  <http://www.openlb.net/>
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public
 *  License along with this program; if not, write to the Free
 *  Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA  02110-1301, USA.
*/

/** \file
 * Unit handling -- header file.
 */

#ifndef UNITS_H_
#define UNITS_H_

#include <string>
#include <fstream>
#include <cmath>

/// Conversion between lattice units and physical units
/// physXYZ(lattice quantity XYZ) returns the physical size of a lattice quantity XYZ
template<typename T>
class LBconverter {
public:
  /// Constructor
  /** \param dim_ dimension of the domain (2D or 3D)
   *  \param latticeL_ length of a lattice cell in meter (proportional to Knudsen number)
   *  \param latticeU_ velocity in dimensionless lattice units (proportional to Mach number)
   *  \param charNu_ kinematic viscosity in m^2/s
   *  \param charL_ characteristical length in meter
   *  \param charU_ characteristical speed in m/s
   *  \param charRho_ density factor in kg/m^d (latticeRho can be multplied by this factor
   *                  to get the local physical density)
   *  \param pressureLevel_ additive pressure constant in Pa (added to the relative pressure
   *                       result of the computation to get the absolute value)
   */
  LBconverter(int dim_, T latticeL_, T latticeU_,
              T charNu_, T charL_ = 1, T charU_ = 1, T charRho_ = 1, T pressureLevel_ = 0 )
    : dim(dim_), latticeL(latticeL_), latticeU(latticeU_), charNu(charNu_),
      charL(charL_), charU(charU_), charRho(charRho_), pressureLevel(pressureLevel_)
  { }
  /// dimension of the domain (2D or 3D)
  int getDim() const
  { return dim; }
  /// length of a lattice cell in meter
  T getLatticeL() const
  { return latticeL; }
  /// characteristical length in meter
  T getCharL(T dL = 1) const
  { return charL * dL; }
  /// characteristical speed in m/s
  T getCharU(T dU = 1) const
  { return charU * dU; }
  /// characteristical time in s
  T getCharTime(T dT = 1) const
  { return charL/charU * dT; }
  /// kinematic viscosity in m^2/s
  T getCharNu() const
  { return charNu; }
  /// density factor in kg/m^d
  T getCharRho(T dRho = 1) const
  { return charRho * dRho; }
  /// characteristical mass in kg
  T getCharMass(T dM = 1) const
  { return charRho*pow(charL,dim) * dM; }
  /// characteristical force in Newton = kg*m/s^2
  T getCharForce(T dF = 1) const
  { return getCharMass()*charL / (getCharTime()*getCharTime()) * dF; }
  /// characteristical pressure in Pascal = N/m^(d-1) = rho*m^2/t^2
  T getCharPressure(T dP = 1) const
  { return getCharForce() / pow(charL, dim-1 ) * dP + pressureLevel; }
  /// characteristical Pressure in Pa
  T getPressureLevel() const
  { return pressureLevel; }

  /// Reynolds number
  T getRe() const
  { return charL * charU / charNu; }
  /// dimensionless kinematic viscosity
  T getDimlessNu() const
  { return 1 / getRe(); }
  /// discretization parameter for grid-spacing (proportional to Knudsen number)
  T getDeltaX() const
  { return latticeL / charL; }
  /// discretization parameter for velocity (proportional to Mach number)
  T getLatticeU() const
  { return latticeU; }
  /// discretization parameter for time
  T getDeltaT() const
  { return latticeU * getDeltaX(); }
  /// lattice kinematic viscosity used for computation
  T getLatticeNu() const
  { return getDeltaT()/ (getDeltaX() * getDeltaX() * getRe()); }
  /// relaxation time
  T getTau() const
  { return (T)3*getLatticeNu()+(T)0.5; }
  /// relaxation frequency
  T getOmega() const
  { return (T)1 / getTau(); }

  /// physical length of a number of cells
  T physLength(T latticeLength = 1) const
  { return charL * getDeltaX() * latticeLength; }
  /// length of a lattice time period in seconds
  /// default: get conversion factor -> lattice to physical time
  T physTime(T latticeTime = 1) const
  { return charL/charU * getDeltaT() * latticeTime; }
  /// convert lattice velocity to physical velocity in m/s
  /// default: get conversion factor -> lattice to physical velocity
  T physVelocity(T latticeVelocity = 1) const
  { return charU / latticeU * latticeVelocity; }
  /// convert lattice flow rate to physical flow rate
  /// default: get conversion factor -> lattice to physical flow rate
  T physFlowRate(T latticeFlowRate = 1) const
  { return latticeFlowRate*pow(physLength(),dim) / physTime(); }
  /// convert lattice to physical density
  /// default: get conversion factor -> lattice to physical density
  T physRho(T latticeRho = 1) const
  { return charRho*latticeRho; }
  /// convert lattice density to physical mass in kg
  /// default: get conversion factor -> lattice to physical mass
  T physMass(T latticeRho = 1) const
  { return physRho(latticeRho)*pow(physLength(),dim); }
  /// convert lattice to physical force in Newton
  /// default: get conversion factor -> lattice to physical force
  T physForce(T latticeForce = 1) const
  { return physMass() * physLength() / (physTime() * physTime()) * latticeForce; }
  /// convert lattice to physical massless force in Newton/kg
  /// default: get conversion factor -> lattice to physical massless force
  T physMasslessForce(T latticeForce = 1) const
  { return physForce(latticeForce) / physMass(); }
  /// convert: lattice rho to physical pressure in Pa
  /// physicalPressure = (rho-1)/3)*pressureFactor
  T physPressure(T rho) const
  { return ((rho - 1) / 3.)*physForce() / (pow(physLength(),dim-1)) + pressureLevel; }

  /// convert: physical length to lattice length
  T latticeLength(T physicalLength = 1) const
  { return physicalLength / physLength(); }
  /// convert: physical velocity to lattice velocity
  T latticeVelocity(T physicalVelocity = 1) const
  { return physicalVelocity / physVelocity(); }
  /// returns number of lattice cells within a length l
  int numCells(T physicalLength = -1) const {
    if (physicalLength == -1) physicalLength = charL;
    return (int)(physicalLength / physLength()+0.5);
  }
  /// returns number of lattice nodes of a physical length l
  int numNodes(T physicalLength = -1) const {
    if (physicalLength == -1) physicalLength = charL;
    return (int)(physicalLength / physLength()+1.5);
  }
  /// returns number of lattice time steps within a period physicalT
  int numTimeSteps(T physicalTime) const
  { return (int)(physicalTime / physTime()+0.5); }
  /// convert physical to lattice pressure
  /// default: get conversion factor -> physical to lattice pressure
  
  /*
  T latticePressure(T physicalPressure = 1) const
  { return (physicalPressure - pressureLevel) * (pow(physLength(),dim-1))/physForce();}
  */
  // modification P.S. there should be a factor of 3 in the conversion
  T latticePressure(T physicalPressure = 1) const
  { return 3.*(physicalPressure - pressureLevel) * (pow(physLength(),dim-1))/physForce();}


private:
  int dim;
  T latticeL, latticeU, charNu, charL, charU, charRho, pressureLevel;
};

#endif
