#include <iostream>
#include <queue>
#include <future>
#include <random>
#include <algorithm>

// As before a global mutex to help syncronize (neatify) stdout
std::mutex gOutputMutex;

// The thing that'll actually do the work, this time with input and output
int myWorker(int input) {
  // generate random sleep time in ms
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, 10);
  int value = dis(gen);
  std::chrono::seconds mySleep(value);

  // Work and manipulate finishing time by sleeping!
  std::this_thread::sleep_for(mySleep);
  gOutputMutex.lock();
  std::cout << "finished processing iput " << input << " after " << mySleep.count() << std::endl;
  gOutputMutex.unlock();

  // Calculate
  return input + 1;
}

int main() {
  // create a holder for the futures - use a FIFO queue to maintain
  // output order.
  std::queue<std::future<int> > results;
  std::vector<int> inputs {9,7,5,3,1,2,4,6,8};
  std::vector<int> outputs;

  std::cout << "queing up..." << std::endl;
  for(int val : inputs) {
    // Create the future via call to async, then queue it up.
    results.emplace(std::async(myWorker,val));
  }

  std::cout << "processing..." << std::endl;

  while(!results.empty()) {
    // Await the result by getting the future. This will block
    // indefinetely... Look to future::wait_{for,until} for allowing
    // timeouts
    std::cout << "waiting for next expected result... " << std::endl;
    int res = results.front().get();
    std::cout << "  got result : " << res << std::endl;
    outputs.push_back(res);
    results.pop();
  }

  // Validate output order comparing differences between inputs and outputs
  int res = std::inner_product(inputs.begin(), inputs.end(),
                               outputs.begin(),
                               0,
                               std::plus<int>(),
                               [](int x, int y) {return x - y + 1;});

  std::cout << "Checking order : "
            << ((res == 0) ? "ok" : "fail")
            << std::endl;

  return 0;
}
