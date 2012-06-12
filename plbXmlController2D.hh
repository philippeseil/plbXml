
using namespace Region;

template<typename T>
const IncomprFlowParam<T>&  PlbXmlController2D<T>::getParams() const
{
  return params;
}

template<typename T>
const RegionList& PlbXmlController2D<T>::getRegionList() const
{
  return regionList;
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
void PlbXmlController2D<T>::buildRegionList()
{
  std::pair<RegionListIterator,bool> inserted;
  XMLreaderProxy reg(plbCase["region"]);
  for( ; reg.isValid(); reg = reg.iterId() ){
    inserted = regionList.insert(regionFromXml(reg));
    // check for duplicated entry
    if(!inserted.second)
      std::cout << "Warning: Region with duplicate ID " 
		<< (*inserted.first).first << " ignored" << std::endl;
  }
}

template<typename T>
void PlbXmlController2D<T>::buildActionList()
{

}

template<typename T>
PlbXmlController2D<T>::PlbXmlController2D(std::string &fname)
  : reader(fname), plbCase(reader["plbCase"]),
    params(this->calcParams())
{
  buildRegionList();
}

template<typename T>
PlbXmlController2D<T>::~PlbXmlController2D()
{

}

