// mp_pocoplugins - try out Poco's plugin mechanism
//
// Copyright (c) 2013 by Ben Morgan <bmorgan.warwick@gmail.com> 
// Copyright (c) 2013 by The University of Warwick

// Standard Library

// Third Party
// - Poco
#include "Poco/SharedLibrary.h"

// This Project

// Function ptr
typedef void (*MessageMe)();

int main(int argc, char *argv[]) {
  // Designed to be run from root of build directory...
  std::string firstLibPath("./Examples/libFoo"+Poco::SharedLibrary::suffix());
  std::string secondLibPath("./Examples/libBar"+Poco::SharedLibrary::suffix());

  Poco::SharedLibrary firstLib(firstLibPath);
  MessageMe firstFPtr = (MessageMe)firstLib.getSymbol("message_me");
  firstFPtr();

  Poco::SharedLibrary secondLib(secondLibPath);
  MessageMe secondFPtr = (MessageMe)secondLib.getSymbol("message_me");
  secondFPtr();

  // and the first again...
  firstFPtr();

  firstLib.unload();
  secondLib.unload();

  return 0;
}

