// MyModuleBar - concrete class of IProcessingModule
//
// Copyright (c) 2013 by Ben Morgan <bmorgan.warwick@gmail.com> 
// Copyright (c) 2013 by The University of Warwick
#ifndef MYMODULEBAR_HH
#define MYMODULEBAR_HH
// Standard Library

// Third Party
// - MicroPipeline
#include "MicroPipeline/IProcessingModule.hpp"

// This Project

class MyModuleBar : public IProcessingModule {
 public:
  MyModuleBar();
  virtual ~MyModuleBar();

  std::string name() const;
  int process(int data) const;
};

#endif // MYMODULEBAR_HH


