#include <iostream>

extern "C" void message_me();

void message_me() {
  std::cout << "[bar] message me" << std::endl;
}
