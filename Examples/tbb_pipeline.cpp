// tbb_pipeline - very basic test of TBB's pipeline
//
// Copyright (c) 2013 by Ben Morgan <bmorgan.warwick@gmail.com> 
// Copyright (c) 2013 by The University of Warwick

#include <iostream>

#include "tbb/tbb_stddef.h"
#include "tbb/pipeline.h"


void reportTBBVersion() {
  std::cout << "Intel TBB " 
            << TBB_VERSION_MAJOR << "." << TBB_VERSION_MINOR
            << "(" << TBB_INTERFACE_VERSION << ")"
            << std::endl;
}


// - Dumb generator of ints, note use of mutable because operator has
// to be const - probably better ways to do this
struct IntGenerator {
  mutable int gen_;
  int number_;

  IntGenerator(int n) : gen_(0), number_(n) {}

  int operator()(tbb::flow_control& fc) const {
    if (gen_ <= number_) {
      gen_++;
      std::cout << gen_ << std::endl;
      return gen_;
    } else {
      fc.stop();
      return NULL;
    }
  }
};


// - Simple pipeline operation
struct IntMultiplier {
  int factor_;

  IntMultiplier(int n) : factor_(n) {}

  int operator()(int v) const {
    return v*factor_;
  }
};

// - Should print out ints in order
struct ResultReporter {
  void operator()(int& n) const {
    std::cout << "received " << n << " " << &n << std::endl;
  }
};


int main(int argc, char **argv) {
  reportTBBVersion(); 
 
  IntGenerator iput(10);

  tbb::parallel_pipeline(4,
                         tbb::make_filter<void,int>(
                             tbb::filter::serial,
                             iput
                             ) &
                         tbb::make_filter<int,int>(
                             tbb::filter::parallel,
                             IntMultiplier(2)
                             ) &
                         tbb::make_filter<int,void>(
                             tbb::filter::serial,
                             ResultReporter()
                             )
                         );
  
  return 0;
}
