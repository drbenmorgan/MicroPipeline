// IService - Pure abstract class for a global service
//
// Copyright (c) 2013 by Ben Morgan <bmorgan.warwick@gmail.com> 
// Copyright (c) 2013 by The University of Warwick
#ifndef ISERVICE_HH
#define ISERVICE_HH
// Standard Library
#include <string>

// Third Party
// - A

// This Project
namespace MicroPipeline {
class IService {
 public:
  IService() {}
  virtual ~IService() {}

  virtual std::string name() const =0;
  virtual void onCreate() =0;
  virtual void onDestroy() =0;
};
} // namespace MicroPipeline
#endif // IService_HH

