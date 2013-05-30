// IProcessingModule - Pure abstract class for a processing module
//
// Copyright (c) 2013 by Ben Morgan <bmorgan.warwick@gmail.com> 
// Copyright (c) 2013 by The University of Warwick
#ifndef IPROCESSINGMODULE_HH
#define IPROCESSINGMODULE_HH
// Standard Library
#include <string>

// Third Party
// - A

// This Project

class IProcessingModule {
 public:
  IProcessingModule() {}
  virtual ~IProcessingModule() {}

  virtual std::string name() const =0;
  virtual int process(int data) const =0;
};

#endif // IPROCESSINGMODULE_HH


