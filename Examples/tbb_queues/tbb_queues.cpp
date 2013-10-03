// tbb_queues - very basic test of TBB's queue collections
//
// Copyright (c) 2013 by Ben Morgan <bmorgan.warwick@gmail.com> 
// Copyright (c) 2013 by The University of Warwick
//
// Standard Library
#include <iostream>

// Third Party
// - TBB
#include <tbb/tbb.h>
#include <tbb/concurrent_queue.h>

typedef tbb::concurrent_bounded_queue<int> MPQueue;

// This Project
class MyProducer {
 public:
  MyProducer(MPQueue& q) : outBox_(q) {;}

  void operator()(size_t howMany) {
    for(size_t i(0); i < howMany; ++i) {
      std::cout << "Enqueuing workitem : " << i << std::endl;
      outBox_.push(i);
      std::cout << "Queued it!" << std::endl;
    }
  }

 private:
  MPQueue& outBox_;
};

class MyConsumer {
 public:
  MyConsumer(MPQueue& q, size_t sleep) : inBox_(q), sleepFor_(sleep) {;}

  void operator()() {
    int workItem;
    while (!inBox_.empty()) {
      inBox_.pop(workItem);
      std::cout << "["<<this<<":"<<sleepFor_<<"] Got workitem : " << workItem << std::endl;
      sleep(sleepFor_);
    }
  }
 private:
  MPQueue& inBox_;
  size_t sleepFor_;
};


int main(int argc, char *argv[]) {
  MPQueue inQueue;
  inQueue.set_capacity(10);
  MyProducer p(inQueue);
  MyConsumer c_a(inQueue,5);
  MyConsumer c_b(inQueue,1);

  tbb::tbb_thread producer(p,100);
  tbb::tbb_thread consumer_a(c_a);
  tbb::tbb_thread consumer_b(c_b);

  producer.join();
  consumer_a.join();
  consumer_b.join();
  return 0;
}

