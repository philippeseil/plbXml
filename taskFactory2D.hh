namespace Task{

  TaskBase* taskFromXml(XMLreaderProxy const &t)
  {
    std::string type = t.getName();
    for( int i=0 ; LAST_TASK_TEXT_ENTRY.compare(taskText[i]) != 0 ; i++){
      if(type.compare(taskText[i]) == 0)
	return (*taskFactoryPtr[i])(t);
    }
    
    throw PlbIOException("Unknown task type \"" + type + "\"");

    return 0;
  }

  TaskBase* setDynamicsFromXml(XMLreaderProxy const &r)
  {
    return new SetDynamics();
  }

  TaskBase* changeBcFromXml(XMLreaderProxy const &r)
  {
    return new ChangeBcValue();
  }

  TaskBase* writeVtkFromXml(XMLreaderProxy const &r)
  {
    return new WriteVtk();
  }

};
