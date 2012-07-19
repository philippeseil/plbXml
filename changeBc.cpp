#include "changeBc.h"
#include "plbHeaders2D.h"
#include "plbXmlController2D.h"
#include "ioUtils.h"
#include <fstream>

namespace Task{
  
  /*
   * ------------------------------------------------------------
   * class SetPressureBC
   * ------------------------------------------------------------
   */
 
  SetPressureBc::SetPressureBc(PlbXmlController2D const *controller, Box2D const &reg_, T val_)
    : TaskBase(controller), reg(reg_), physVal(0.), val(0.)
  {
    setVal(val_);
  }

  SetPressureBc::SetPressureBc(PlbXmlController2D const *controller, XMLreaderProxy const &r)
    : TaskBase(controller), reg(ioUtils::bcBoxFromXml(controller,r)), physVal(0.), val(0.)
  {
    T val_;

    try{
      r["bcValue"].read(val_);
    }catch (PlbIOException &e){
      plbIOError("No value for pressure boundary condition specified");
    }
 
    setVal(val_);
  }

  SetPressureBc::~SetPressureBc()
  {

  }

  void SetPressureBc::setVal(T physVal_)
  {
    physVal = physVal_;
    val = (controller->getUnits()).latticePressure(physVal)+1.;
  }
  void SetPressureBc::perform(MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
			      OnLatticeBoundaryCondition2D<T,DESCRIPTOR> &boundaryCondition,
			      plint nStep)
  {
    pcout << "boundary pressure set to " << physVal << " " << controller->getUnits().physPressure(val)
	  << " lattice density: " << val << std::endl;
    setBoundaryDensity(lattice, reg, val );
    initializeAtEquilibrium(lattice,reg,val,Array<T,2>(0.,0.));
  };

  /*
   * -----------------------------------------------------------
   * class SetPressureBcFromFile
   * -----------------------------------------------------------
   */

  SetPressureBcFromFile::SetPressureBcFromFile(PlbXmlController2D const *controller, 
					       XMLreaderProxy const &r)
    : SetPressureBc(controller,ioUtils::bcBoxFromXml(controller,r),0.), 
      constantFlag(false), startFlag(true), endFlag(false),
      cursor(0), nStepThis(0), nStepNext(0)
  {
    T tTmp,pTmp;
    std::string fname;
    r["valFile"].read(fname);

    std::ifstream file(fname.c_str());

    while(!file.eof()){
      file >> tTmp; file >> pTmp;
      t.push_back(tTmp); p.push_back(pTmp);
    }

    if(p.size() == 0){
      t.push_back(0.); p.push_back(0.);
    }

    if(p.size() == 1) constantFlag = true;
    else nStepNext = controller->getUnits().numTimeSteps(t[1]);

    nStepThis = controller->getUnits().numTimeSteps(t[0]);

    if(nStepThis == 0) startFlag = true;
        
    setVal(p[0]);

    file.close();
  }

  
  

  SetPressureBcFromFile::~SetPressureBcFromFile()
  {

  }

  void SetPressureBcFromFile::perform(MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
				      OnLatticeBoundaryCondition2D<T,DESCRIPTOR> &boundaryCondition,
				      plint nStep)
  {
    if(constantFlag || endFlag) return;
    
    if(!startFlag){
      if(nStepThis >= nStep)
	startFlag == true;
    } 

    if(nStep >= nStepNext){
      nStepThis = nStepNext;
      cursor++;
      if(cursor == p.size()-1){
	endFlag = true;
	setVal(p[cursor]);
      } else{
	nStepNext = controller->getUnits().numTimeSteps(t[cursor+1]);
      }
    }

    if(startFlag && !endFlag){
      T dt = ((T)(nStep - nStepThis)) /((T)(nStepNext - nStepThis));
      setVal(dt*(p[cursor+1]-p[cursor]) + p[cursor]);
    }

    if(startFlag) SetPressureBc::perform(lattice,boundaryCondition,nStep);
  }

  /*
   * ------------------------------------------------------------
   * class SetVelocityBC
   * ------------------------------------------------------------
   */
 
  SetVelocityBc::SetVelocityBc(PlbXmlController2D const *controller, Box2D const &reg_, Array<T,2> const &val_)
    : TaskBase(controller), reg(reg_)
  {
    setVal(val_);
  }

  SetVelocityBc::SetVelocityBc(PlbXmlController2D const *controller, XMLreaderProxy const &r)
    : TaskBase(controller), reg(ioUtils::bcBoxFromXml(controller,r))
  {
    std::vector<T> val;
    r["bcValue"].read(val);
    setVal(Array<T,2>(val[0],val[1]));
  }
  SetVelocityBc::~SetVelocityBc()
  {

  }

  void SetVelocityBc::setVal(Array<T,2> physVal)
  {
    val[0] = (controller->getUnits()).latticeVelocity(physVal[0]);
    val[1] = (controller->getUnits()).latticeVelocity(physVal[1]);
  }
  void SetVelocityBc::perform(MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
			      OnLatticeBoundaryCondition2D<T,DESCRIPTOR> &boundaryCondition,
			      plint nStep)
  {
    pcout << "boundary velocity set to " << val[0] << " " << val[1] << std::endl;
    setBoundaryVelocity(lattice, reg, val );
    initializeAtEquilibrium(lattice,reg,1.,val);
  };
  
  /*
   * ---------------------------------------------------------------
   * class SetVelocityBcFromFile
   * ---------------------------------------------------------------
   */

  SetVelocityBcFromFile::SetVelocityBcFromFile(PlbXmlController2D const *controller, 
					       XMLreaderProxy const &r)
    : SetVelocityBc(controller,ioUtils::bcBoxFromXml(controller,r),Array<T,2>(0.,0.)), 
      constantFlag(false), startFlag(true), endFlag(false),
      cursor(0), nStepThis(0), nStepNext(0)
  {
    T tTmp,vxTmp,vyTmp;

    std::string fname;
    r["valFile"].read(fname);
    std::ifstream file(fname.c_str());

    while(!file.eof()){
      file >> tTmp; file >> vxTmp; file >> vyTmp;
      t.push_back(tTmp); vx.push_back(vxTmp); vy.push_back(vyTmp);
    }

    if(vx.size() == 0){
      t.push_back(0.); vx.push_back(0.); vy.push_back(0.);
    }

    if(vx.size() == 1) constantFlag = true;
    else nStepNext = controller->getUnits().numTimeSteps(t[1]);

    nStepThis = controller->getUnits().numTimeSteps(t[0]);

    if(nStepThis == 0) startFlag = true;
        
    setVal(Array<T,2>(vx[0],vy[0]));

    file.close();
  }

  SetVelocityBcFromFile::~SetVelocityBcFromFile()
  {
    
  }

  void SetVelocityBcFromFile::perform(MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
				      OnLatticeBoundaryCondition2D<T,DESCRIPTOR> &boundaryCondition,
				      plint nStep)
  {
    if(constantFlag || endFlag) return;
    
    if(!startFlag){
      if(nStepThis >= nStep)
	startFlag == true;
    } 

    if(nStep >= nStepNext){
      nStepThis = nStepNext;
      cursor++;
      if(cursor == vx.size()-1){
	endFlag = true;
	setVal(Array<T,2>(vx[cursor],vy[cursor]));
      } else{
	nStepNext = controller->getUnits().numTimeSteps(t[cursor+1]);
      }
    }

    if(startFlag && !endFlag){
      T dt = ((T)(nStep - nStepThis)) /((T)(nStepNext - nStepThis));
      T vxTmp = dt*(vx[cursor+1]-vx[cursor]) + vx[cursor];
      T vyTmp = dt*(vy[cursor+1]-vy[cursor]) + vy[cursor];
      setVal(Array<T,2>(vxTmp,vyTmp));
    }

    if(startFlag) SetVelocityBc::perform(lattice,boundaryCondition,nStep);
  }



  /*
   * ------------------------------------------------------------
   * class WriteVtk
   * ------------------------------------------------------------
   */

};
