#include "ioUtils.h"
#include "plbHeaders2D.h"

namespace ioUtils{
  bool elementExists(plb::XMLreaderProxy const &reader, std::string const &elemId)
  {
    std::string dummy;
    bool flag(true);
    try{
      reader[elemId].read(dummy);
    } catch (plb::PlbIOException &e){
      flag = false;
    }

    return flag;
  }
} // namespace Utils
