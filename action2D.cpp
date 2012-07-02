#include "action2D.h"

namespace Action {

  Action2D actionFromXml(XMLreaderProxy const &a)
  {
    std::string id;
    ActionClass2D *actPtr;

    try{
      a["id"].read(id);
    } catch (PlbIOException &e){
      throw PlbIOException("Invalid Action command: No id specified!");
    }
    if(id.compare("") == 0)
      throw PlbIOException("Invalid Action command: Unnamed Action");

    try{
      std::vector<std::string> typeRead;
      a["type"].read(typeRead);

      if(typeRead.at(0).compare("once") == 0){
	plint t = atoi(typeRead.at(1).c_str());

	if(t<0) throw PlbIOException("dummy");

	actPtr = new OnceAction(t);

      } else if(typeRead.at(0).compare("periodic") == 0){
	plint nStart = atoi(typeRead.at(1).c_str());
	plint nPeriod = atoi(typeRead.at(2).c_str());
	plint nEnd = atoi(typeRead.at(3).c_str());

	if(nStart<0 || nEnd<=nStart || nPeriod<1) throw PlbIOException("dummy");

	actPtr = new PeriodicAction(nStart,nPeriod,nEnd);

      } else throw PlbIOException("dummy");

    } catch (std::exception &e){
      throw PlbIOException("Invalid Action command: Unknowkn or no type specified");
    }

    std::vector<XMLreader*> v = a.getChildren();
    for(int i=0;i<v.size();i++){
      if( (v[i]->getName().compare("id") == 0)
	  || (v[i]->getName().compare("type") == 0) )
	continue;

      plint id = v[i]->getFirstId();
      do{
	XMLreaderProxy p(v[i],id);
	actPtr->addTask(Task::taskFromXml(p, plb::IncomprFlowParam<T>(1,1,1,1,1)));
      } while (v[i]->getNextId(id));
    }
    return Action2D(id,actPtr);
  }

}; // namespace Action
