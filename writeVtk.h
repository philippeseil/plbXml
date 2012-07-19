#ifndef WRITE_VTK_LBDEM
#define WRITE_VTK_LBDEM

#ifdef TASK_LIST
addToTaskMap<WriteVtk>("writeVtk");
#else


#include "taskBase.h"
#include "units.h"

namespace Task {

class WriteVtk : public TaskBase {
public:
  WriteVtk(PlbXmlController2D const *controller, XMLreaderProxy const &r);
  virtual ~WriteVtk();
  virtual void perform(MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
		       plint nStep);
private:
  std::string prefix;
  
  struct PressureFromRho {
    PressureFromRho(PlbXmlController2D const *controller_);
    T operator()(T rho);
  private:
    LBconverter<T> const &units;
  };
    

};

} // namespace Task

#endif /* TASK_LIST */
#endif /* WRITE_VTK_LBDEM */
