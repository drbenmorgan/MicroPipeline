// mp_asynchannel - experiment with the Poco AsyncChannel for logging
//
// Based on the Poco Examples
//
#include "Poco/Logger.h" 
#include "Poco/AsyncChannel.h" 
#include "Poco/ConsoleChannel.h" 
#include "Poco/AutoPtr.h"
#include "Poco/FormattingChannel.h"
#include "Poco/PatternFormatter.h"

using Poco::Logger; 
using Poco::AsyncChannel; 
using Poco::ConsoleChannel; 
using Poco::FormattingChannel;
using Poco::PatternFormatter;
using Poco::AutoPtr;

int main(int argc, char** argv)
{
  AutoPtr<ConsoleChannel> pCons(new ConsoleChannel); 
  AutoPtr<PatternFormatter> pPF(new PatternFormatter);
  pPF->setProperty("pattern", "[%s:%P:%p] %t");
  AutoPtr<FormattingChannel> pFC(new FormattingChannel(pPF, pCons));
  AutoPtr<AsyncChannel> pAsync(new AsyncChannel(pFC));

  Logger::root().setChannel(pAsync);
  Logger::root().getChannel()->open();

  Logger& logger = Logger::get("TestLogger");
  for (int i = 0; i < 10; ++i) { 
    logger.information("This is a test");
  }

  Logger::root().getChannel()->close();
  return 0;
}

