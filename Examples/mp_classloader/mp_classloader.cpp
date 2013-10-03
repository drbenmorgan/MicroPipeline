// mp_classloader - test of Poco's ClassLoader and Manifest
//
// Copyright (c) 2013 by Ben Morgan <bmorgan.warwick@gmail.com> 
// Copyright (c) 2013 by The University of Warwick
// Standard Library
#include <iostream>
#include <vector>

// Third Party
// - Poco
#include "Poco/ClassLoader.h"
#include "Poco/Manifest.h"

#include "Poco/SharedPtr.h"

// This Project
#include "MicroPipeline/IProcessingModule.hpp"

namespace MicroPipeline {
typedef std::vector<int> DataStream;
typedef std::vector<Poco::SharedPtr<IProcessingModule> > Pipeline;

typedef Poco::ClassLoader<IProcessingModule> ProcessingModuleLoader;
typedef ProcessingModuleLoader::Iterator ProcessingModuleLoaderIterator;

typedef Poco::Manifest<IProcessingModule> ProcessingModuleManifest;
typedef ProcessingModuleManifest::Iterator ProcessingModuleManifestIterator;
} // namespace MicroPipeline

int main(int argc, char *argv[]) {
  MicroPipeline::ProcessingModuleLoader loader;

  std::string myLib("libMyProcessingModule.so");
  loader.loadLibrary(myLib);

  // Print manifest...
  MicroPipeline::ProcessingModuleLoaderIterator it(loader.begin());
  MicroPipeline::ProcessingModuleLoaderIterator end(loader.end());

  while (it != end) {
    std::cout << "[Library:" << it->first << "]" << std::endl;

    std::cout << "|- [ManifestOf:" << it->second->className() << "]" << std::endl;
    MicroPipeline::ProcessingModuleManifestIterator itMf(it->second->begin());
    MicroPipeline::ProcessingModuleManifestIterator endMf(it->second->end());

    while (itMf != endMf) {
      std::cout << "  |- [Class:" << itMf->name() << "]" << std::endl;
      ++itMf;
    }
    ++it;
  }

  // Create classes, stick them in a vector and process 10 integers
  MicroPipeline::Pipeline MP;
  MP.push_back(MicroPipeline::Pipeline::value_type(loader.create("MyProcessingModule::MyModuleFoo")));
  MP.push_back(MicroPipeline::Pipeline::value_type(loader.create("MyModuleBar")));
  
  MicroPipeline::DataStream dataStream(100);
  for (int i = 0; i < 100; i++) dataStream[i] = i;

  for (MicroPipeline::DataStream::iterator it(dataStream.begin()); it != dataStream.end(); ++it) {
    MicroPipeline::DataStream::value_type datum = *it;
    std::cout << "[Pipeline] INPUT(" << datum << ")" << std::endl;
    for (MicroPipeline::Pipeline::iterator jt(MP.begin()); jt != MP.end(); ++jt) {
      datum = (*jt)->process(datum);
    }
    std::cout << "[Pipeline] OUTPUT(" << datum << ")" << std::endl;    
  }

  // Need to destruct objects before libs can be unloaded...
  MP.clear();

  loader.unloadLibrary(myLib);
  return 0;
}

