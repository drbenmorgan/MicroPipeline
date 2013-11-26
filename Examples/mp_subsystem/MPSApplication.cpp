// MPSApplication - implementation
//
// Copyright (c) 2013 by Ben Morgan <bmorgan.warwick@gmail.com>
// Copyright (c) 2013 by The University of Warwick

// Ourselves
#include "MPSApplication.h"

// Standard Library

// Third Party
// - Poco
#include "Poco/LogStream.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/DateTimeFormatter.h"

// This Project


MPSApplication::MPSApplication() : Poco::Util::Application()
{
  this->logger().information("default constructor running");
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
  this->logger().information("running initialize");
  // - root logger
  this->config().setString("logging.loggers.MPSDEFAULT.name", "DEFAULT");
  this->config().setString("logging.loggers.MPSDEFAULT.channel", "MPSCONSOLE");
  this->config().setString("logging.loggers.MPSDEFAULT.level", "trace");

  // - root channel
  this->config().setString("logging.channels.MPSCONSOLE.class", "ConsoleChannel");
  this->config().setString("logging.channels.MPSCONSOLE.pattern", "[%q:%s] %t");

  this->config().setString("application.logger", "DEFAULT");

  Application::initialize(self);

  this->logger().information("initialize done");
}

void MPSApplication::reinitialize(Application& self) {
  Application::reinitialize(self);
  this->logger().information("running reinitialize");
}

void MPSApplication::uninitialize() {
  this->logger().information("running uninitialize");
}

void MPSApplication::defineOptions(Poco::Util::OptionSet& options) {
  this->logger().information("running defineOptions");

  Application::defineOptions(options);

  options.addOption(
      Poco::Util::Option("help", "h", "display help information")
      .required(false)
      .repeatable(false)
      .callback(Poco::Util::OptionCallback<MPSApplication>(this, &MPSApplication::handleHelp)));
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
}


