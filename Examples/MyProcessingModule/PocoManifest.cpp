// PocoExport - Generate manifest and load/unload functions
//
// Copyright (c) 2013 by Ben Morgan <bmorgan.warwick@gmail.com> 
// Copyright (c) 2013 by The University of Warwick
#ifndef POCOMANIFEST_HH
#define POCOMANIFEST_HH
// Standard Library
#include <iostream>
// Third Party
// - Poco
#include "Poco/ClassLibrary.h"

// This Project
#include "MyModuleFoo.hpp"
#include "MyModuleBar.hpp"

//----------------------------------------------------------------------
// Manifests
//
POCO_BEGIN_MANIFEST(IProcessingModule)
  POCO_EXPORT_CLASS(MyProcessingModule::MyModuleFoo)
  POCO_EXPORT_CLASS(MyModuleBar)
POCO_END_MANIFEST

//----------------------------------------------------------------------
// Set/Clean Up functions
//
void pocoInitializeLibrary() {
  std::cout << "[MyProcessingModule] Loading... " << std::endl;
}

void pocoUninitializeLibrary() {
  std::cout << "[MyProcessingModule] Unloading... " << std::endl;
}

#endif // POCOMANIFEST_HH
