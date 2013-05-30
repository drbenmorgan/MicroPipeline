// MyModuleFoo - concrete class of IProcessingModule
//
// Copyright (c) 2013 by Ben Morgan <bmorgan.warwick@gmail.com> 
// Copyright (c) 2013 by The University of Warwick
#ifndef MYMODULEFOO_HH
#define MYMODULEFOO_HH
// Standard Library

// Third Party
// - MicroPipeline
#include "MicroPipeline/IProcessingModule.hpp"

// This Project

class MyModuleFoo : public IProcessingModule {
 public:
  MyModuleFoo();
  virtual ~MyModuleFoo();

  std::string name() const;
  int process(int data) const;
};

#endif // MYMODULEFOO_HH


