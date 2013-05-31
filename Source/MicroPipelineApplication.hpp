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
// - Poco
#include "Poco/Version.h"
#include "Poco/Util/Application.h"
#include "Poco/Util/AbstractConfiguration.h"

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
    // Hard code configuration properties - can later be moved
    // to proper config file...
    this->config().setInt("application.pocoVersion", POCO_VERSION);
    this->config().setString("logging.channels.mpconsole.class", "ConsoleChannel");
    this->config().setString("logging.channels.mpconsole.pattern", "[%q:%s] %t");
    this->config().setString("logging.loggers.mpdefault.channel", "mpconsole");
    this->config().setString("logging.loggers.mpdefault.name", "micro_pipeline");
    this->config().setString("application.logger", "${application.name}");
    
    this->config().setString("logging.loggers.root.channel.class" , "ConsoleChannel");
    this->config().setString("logging.loggers.root.channel.pattern" , "%p %t");


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
    this->logger().information("running defineOptions");
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
    this->printProperties("");
    return EXIT_OK;
  }

  //----------------------------------------------------------------------
  // Other methods
  void printProperties(const std::string& base) {
    Poco::Util::AbstractConfiguration::Keys keys;
    this->config().keys(base, keys);
    if (keys.empty()) {
      if (config().hasProperty(base)) {
        std::string msg;
        msg.append(base);
        msg.append(" = ");
        msg.append(config().getString(base));
        logger().information(msg);
      }
    }
    else {
      for (Poco::Util::AbstractConfiguration::Keys::const_iterator it = keys.begin(); 
           it != keys.end(); ++it) {
        std::string fullKey = base;
        if (!fullKey.empty()) fullKey += '.';
        fullKey.append(*it);
        printProperties(fullKey);
      }
    }
  }
};
} // namespace MicroPipeline

#endif // MICROPIPELINEAPPLICATION_HH

