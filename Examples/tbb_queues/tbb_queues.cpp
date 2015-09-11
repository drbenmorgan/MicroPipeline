// tbb_queues - very basic test of TBB's queue collections
//
// Copyright (c) 2013 by Ben Morgan <bmorgan.warwick@gmail.com>
// Copyright (c) 2013 by The University of Warwick
//
// Standard Library
#include <iostream>
#include <unistd.h>

// Third Party
// - TBB
#include <tbb/tbb.h>
#include <tbb/concurrent_queue.h>

typedef tbb::concurrent_bounded_queue<int> MPQueue;

struct WorkItem {
  bool kill;
  int value;
};

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
  MyConsumer(MPQueue& q, size_t sleep) : inBox_(q), sleepFor_(sleep), processed_(0) {;}

  ~MyConsumer() {
    std::cout << "["<<this<<":"<<"processed]:" <<processed_<<std::endl;
  }

  void operator()() {
    int workItem;
    // do-while ensures that :
    // i) with concurrent bounded queue, pop waits until it has something
    // ii) terminate when queue becomes empty
    // NB: now have opposite issue, in that can wait for ever if nothing
    // is pushed onto queue!
    // Basically, if number of items to be processed is less than
    // the number of consumers, Cn - Ni consumers will block.
    do {
      inBox_.pop(workItem);
      std::cout << "["<<this<<":"<<sleepFor_<<"] Got workitem : " << workItem << std::endl;
      sleep(sleepFor_);
      ++processed_;
    } while (!inBox_.empty());
  }
 private:
  MPQueue& inBox_;
  size_t sleepFor_;
  size_t processed_;
};


int main(int argc, char *argv[]) {
  MPQueue inQueue;
  inQueue.set_capacity(10);

  MyProducer p(inQueue);
  tbb::tbb_thread producer(p,1);

  MyConsumer c_a(inQueue,1);
  MyConsumer c_b(inQueue,2);

  tbb::tbb_thread consumer_b(c_b);
  tbb::tbb_thread consumer_a(c_a);

  producer.join();
  consumer_a.join();
  consumer_b.join();
  return 0;
}

