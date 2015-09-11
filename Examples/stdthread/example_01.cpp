#include <iostream>
#include <thread>
#include <mutex>
#include <random>

// A global (o.k., o.k....) mutex for syncronizing stdout - this is just
// to help with keeping output neat
std::mutex gOutputMutex;

// The actual worker function - we just pass it an input to id it to show
// that this can be done, even though we use this_thread.
void myWork(size_t id) {
  std::thread::id thisThread = std::this_thread::get_id();

  // generate random sleep time in ms
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, 10);
  std::chrono::milliseconds mySleep(dis(gen));

  // Work by sleeping!
  std::this_thread::sleep_for(mySleep);

  // Use a global mutex to syncronize stdout
  gOutputMutex.lock();
  std::cout << "thread " << id << ":" << thisThread << " finished in " << mySleep.count() << std::endl;
  gOutputMutex.unlock();
}

int main() {
  // Create the threads
  std::thread workers[10];
  for(int i(0); i < 10; ++i) {
    workers[i] = std::thread(myWork,i);
  }

  // Join up
  for(int i(0); i < 10; ++i) {
    workers[i].join();
  }

  return 0;
}

