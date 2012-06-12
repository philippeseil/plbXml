/*
 * region2D.h
 */

#include "palabos2D.h"
#include "palabos2D.hh"

#include <string>

struct Region2D : plb::Box2D {
  Region2D() : Box2D() {}
  Region2D(plint x0_, plint x1_, plint y0_, plint y1_)
    : Box2D(x0_,x1_,y0_,y1_) {} 
  std::string id
}
