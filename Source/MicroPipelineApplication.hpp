// MicroPipelineApplication - Concrete Poco::Util::Application
//
// Copyright (c) 2013 by Ben Morgan <bmorgan.warwick@gmail.com> 
// Copyright (c) 2013 by The University of Warwick
//
// Distributed under the OSI-approved BSD 3-Clause License (the "License");
// see accompanying file License.txt for details.
//
// This software is distributed WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the License for more information.
//
#ifndef MICROPIPELINEAPPLICATION_HH
#define MICROPIPELINEAPPLICATION_HH
// Standard Library

// Third Party
// - A
#include "Poco/Util/Application.h"

// This Project

namespace MicroPipeline {
class MicroPipelineApplication : public Poco::Util::Application {
 public:
  MicroPipelineApplication() {}
  MicroPipelineApplication(int argc, char* argv[]) 
      : Poco::Util::Application(argc, argv) {}
  virtual ~MicroPipelineApplication() {}

  virtual const char* name() const {
    return "micro_pipeline";
  }

  //----------------------------------------------------------------------
  // sequence operations that custom app must override
  //
  virtual void initialize(Application& self) {
    this->loadConfiguration();
    Application::initialize(self);
    this->logger().information("running initialize");
  }
  
  virtual void uninitialize() {
    this->logger().information("running uninitialize");
    Application::uninitialize();
  }  
  
  virtual void reinitialize(Application& self) {
    this->logger().information("running reinitialize");
    Application::reinitialize(self);
  }

  virtual void defineOptions(Poco::Util::OptionSet& options) {
    Application::defineOptions(options);
    options.addOption(
        Poco::Util::Option("help", "h", "display help")
        .required(false)
        .repeatable(false));
  }

  virtual void handleOption(const std::string& name,
                            const std::string& value) {
    Application::handleOption(name, value);
    this->logger().information("running handle option");
  }

  virtual int main(const std::vector<std::string>& args) {
    Poco::Logger& appLogger = this->logger();
    appLogger.information("running main");
    appLogger.information("name() : " + std::string(this->name()));
    appLogger.information("commandName() : " + this->commandName());
    
    appLogger.information("config : " + this->config().getString("application.configDir"));
    return EXIT_OK;
  }
};
} // namespace MicroPipeline

#endif // MICROPIPELINEAPPLICATION_HH

