#ifndef IOUTILS_H_LBDEM
#define IOUTILS_H_LBDEM

#include <string>

namespace plb{
  class XMLreaderProxy;
}
namespace ioUtils{
  bool elementExists(plb::XMLreaderProxy const &reader, std::string const &elemId);
}

#endif // IOUTILS_H_LBDEM
