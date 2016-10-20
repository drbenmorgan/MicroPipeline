// MPSApplication - implementation
//
// Copyright (c) 2013 by Ben Morgan <bmorgan.warwick@gmail.com>
// Copyright (c) 2013 by The University of Warwick

// Ourselves
#include "MPSApplication.h"

// Standard Library
#include <iostream>
#include <regex>

// Third Party
// - Poco
#include "Poco/LogStream.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/Util/HelpFormatter.h"

// This Project

// Dumb callback?
struct Verbosity {
  Verbosity() : level(0) {}
  ~Verbosity() {}
  void increment(const std::string&, const std::string&) {
    ++level;
    std::cout << "level : " << level << std::endl;
  }

  unsigned int level;
};

Verbosity gVerb;

/// Try a file lookup system
class SearchPaths {
 public:
  SearchPaths() = default;

  //! Append a new search path to the mount point prefix
  bool addSearchPath(const std::string& prefix, const std::string& path) {
    bool prefixIsValid = this->validatePrefix(prefix);
    if (prefixIsValid) {
      searchPaths_[prefix].push_back(path);
    }
    return prefixIsValid;
  }

  //! Resolve input path to fully resolved path
  // Provides no guarantee that path actually exists.
  //
  std::string expand(const std::string& path) const {
    // For back-compatibility, ignore any leading "@"
    // Format expect to be "identifier:path"
    return std::string {};
  }

  // Just for testing
  void print(std::ostream& os) const {
    os << "{";
    for (auto const& elem : searchPaths_) {
      os << elem.first << " : [";
      for (auto const& p : elem.second) {
        os << p << ",";
      }
    }
    os << "]}\n";
  }

 private:
  // Return true if prefix is a valid mount point
  // basically, must be
  // 1) two or more characters long (to not clash with drive letters)
  // 2) be a valid C identifier
  bool validatePrefix(const std::string& prefix) const {
    static const std::regex CIdentifier("^[a-zA-Z][a-zA-Z0-9_]+");
    return std::regex_match(prefix,CIdentifier);
  }

 private:
  std::map<std::string, std::list<std::string> > searchPaths_;
};


/// Try a simple additional subsystem
class TestSubSystem : public Poco::Util::Subsystem {
 public:
  TestSubSystem() = default;

  virtual const char* name() const  {
    return "TestSubSystem";
  }

 protected:
  virtual void initialize(Poco::Util::Application& app) {
    logger_ = &(Poco::Logger::get(this->name()));
    logger_->information("TestSubSystem::initialize");
  }

  virtual void uninitialize() {
    logger_->information("TestSubSystem::uninitialize");
  }

 private:
  Poco::Logger* logger_;
};





MPSApplication::MPSApplication() : Poco::Util::Application()
{
  this->logger().information("default constructor running");
  Application::instance().addSubsystem(new TestSubSystem);
}

MPSApplication::MPSApplication(int argc, char* argv[])
  : Poco::Util::Application(argc, argv) {
  this->logger().information("argc, argv constructor running");
}

MPSApplication::~MPSApplication() {
  this->logger().information("destructor running");
}

const char* MPSApplication::name() const {
  return "MPSApplication";
}

void MPSApplication::initialize(Application& self) {
  // No default configuration
  this->logger().information("start initialize");

  // What is config at this point?
  this->printConfig("");

  // - root logger
  //this->config().setString("logging.loggers.MPSDEFAULT.name", "DEFAULT");
  //this->config().setString("logging.loggers.MPSDEFAULT.channel", "MPSCONSOLE");
  //this->config().setString("logging.loggers.MPSDEFAULT.level", "trace");

  // - root channel
  this->config().setString("logging.channels.MPSCONSOLE.class", "ConsoleChannel");
  this->config().setString("logging.channels.MPSCONSOLE.pattern", "[%q:%s] %t");
  this->config().setString("logging.loggers.root.channel", "MPSCONSOLE");

  // Using the config system, we can configure the properties of the logger
  // for the given sub logger. Note the separation in naming between the
  // configuration object (t1) and the ultimate logger (TestSubSystem).
  // Need to think about how that feeds through to properties files...
  // e.g.
  // logging : properties {
  //   channels : properties {
  //     ChannelName : properties {
  //       class : string = "ConsoleChannel"
  //     }
  //   loggers : properties {
  //     # Would like to write
  //     TestSubSystem : properties {
  //       level : string = "trace"
  //     }
  //     # But have to write
  //     t1 : properties {
  //       name : string = "TestSubSystem"
  //       level : string = "trace"
  //     }
  //   }
  //
  this->config().setString("logging.loggers.t1.name", "TestSubSystem");
  this->config().setString("logging.loggers.t1.level", "fatal");
  // Adding a custom channel requires both arguments!
  //this->config().setString("logging.loggers.t1.channel.class", "ConsoleChannel");
  //this->config().setString("logging.loggers.t1.channel.pattern", "fobar %t");

  // Subsystems *must* be created before full initialization
  // can do it here, or in app class constructor
  // Need to see if we have configuration available from
  // command line yet.
  // Now try in constructor (could also envisage adding optional
  // subsystems based on config...)
  // this->addSubsystem(new TestSubSystem);

  //Try SearchPaths...
  SearchPaths s;
  if(!s.addSearchPath("application", this->config().getString("application.configDir"))) {
    this->logger().error("failed to add path");
  }
  if(!s.addSearchPath("local", this->config().getString("application.path"))) {
    this->logger().error("failed to add path");
  }
  if(!s.addSearchPath("application", this->config().getString("application.path"))) {
    this->logger().error("failed to add path");
  }

  s.print(std::cout);

  Application::initialize(self);

  this->logger().information("end initialize");
  this->printConfig("");
}

void MPSApplication::reinitialize(Application& self) {
  this->logger().information("start reinitialize");
  Application::reinitialize(self);
  this->logger().information("end reinitialize");
}

void MPSApplication::uninitialize() {
  this->logger().information("start uninitialize");
}

void MPSApplication::defineOptions(Poco::Util::OptionSet& options) {
  this->logger().information("running defineOptions");

  Application::defineOptions(options);

  options.addOption(
      Poco::Util::Option("help", "h", "display help information")
      .required(false)
      .repeatable(false)
      .callback(Poco::Util::OptionCallback<MPSApplication>(this, &MPSApplication::handleHelp)));

  // Increment verbosity?
  options.addOption(
      Poco::Util::Option("verbose", "v", "increase verbosity")
      .required(false)
      .repeatable(true)
      .callback(Poco::Util::OptionCallback<Verbosity>(&gVerb, &Verbosity::increment)));
  this->logger().information("defineOptions done");
}

void MPSApplication::handleOption(const std::string& name,
                                  const std::string& value) {
  this->logger().information("running handle option "+name+" "+value);
  Application::handleOption(name, value);
}

int MPSApplication::main(const std::vector<std::string>& args) {
  Poco::LogStream mainLog(this->logger());
  mainLog << "start main @ " << Poco::DateTimeFormatter::format(this->startTime(),Poco::DateTimeFormat::ISO8601_FORMAT) << "\n";

  this->reinitialize(*this);

  mainLog << "end main\n";
  mainLog << "uptime " << Poco::DateTimeFormatter::format(this->uptime()) << "\n";
  return EXIT_OK;
}


void MPSApplication::handleHelp(const std::string& name,
                                const std::string& value) {
  this->logger().information("handling help");
  this->displayHelp();
  this->stopOptionsProcessing();
}

void MPSApplication::displayHelp() {
  Poco::Util::HelpFormatter helpFormatter(options());
  helpFormatter.setCommand(commandName());
  helpFormatter.setUsage("OPTIONS");
  helpFormatter.setHeader(
      std::string(this->name()) +
      "\n\n"
      "A sample application that demonstrates some of the features "
      "of the Poco::Util::Application class."
      );
  helpFormatter.setFooter("For more details see X");
  helpFormatter.format(std::cout);
}

void MPSApplication::printConfig(const std::string& base) {
  using Poco::Util::AbstractConfiguration;

  AbstractConfiguration::Keys keys;
    config().keys(base, keys);
    if (keys.empty()) // key has no child
    {
        if (config().hasProperty(base))
        {
            std::string msg;
            msg.append(base);
            msg.append(" = ");
            msg.append(config().getString(base));
            poco_information(logger(),msg);
        }
    }
    else // recursion
    {
        for (AbstractConfiguration::Keys::const_iterator it = keys.begin(); it != keys.end(); ++it)
        {
            std::string fullKey = base;
            if (!fullKey.empty()) fullKey += '.';
            fullKey.append(*it);
            printConfig(fullKey);
        }
    }
}
