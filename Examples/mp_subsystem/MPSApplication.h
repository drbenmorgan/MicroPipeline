// MPSApplication - basic poco app for studying subsystem behaviour
//
// Copyright (c) 2013 by Ben Morgan <bmorgan.warwick@gmail.com>
// Copyright (c) 2013 by The University of Warwick
#ifndef MPSAPPLICATION_HH
#define MPSAPPLICATION_HH
// Standard Library

// Third Party
// - Poco
#include "Poco/Util/Application.h"

// This Project

class MPSApplication : public Poco::Util::Application {
 public:
  MPSApplication();
  MPSApplication(int argc, char* argv[]);

  virtual const char* name() const;

 protected:
  virtual ~MPSApplication();

  virtual void initialize(Application& self);

  virtual void reinitialize(Application& self);

  virtual void uninitialize();

  virtual void defineOptions(Poco::Util::OptionSet& options);

  virtual void handleOption(const std::string& name, const std::string& value);

  virtual int main(const std::vector<std::string>& args);

 private:
  void handleHelp(const std::string& name, const std::string& value);
  void displayHelp();
};

#endif // MPSAPPLICATION_HH

