#include <iostream>

extern "C" void message_me();

void message_me() {
  std::cout << "[foo] message me" << std::endl;
}
