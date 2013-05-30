// Ourselves
#include "MyModuleFoo.hpp"

// Standard Library
#include <iostream>

// Third Party
// - A

// This Project

MyModuleFoo::MyModuleFoo() {
  std::cout << "[MyModuleFoo] Constructor" << std::endl;
}

MyModuleFoo::~MyModuleFoo() {
  std::cout << "[MyModuleFoo] Destructor" << std::endl;
}

std::string MyModuleFoo::name() const {
  return "MyModuleFoo";
}

int MyModuleFoo::process(int data) const {
  std::cout << "[MyModuleFoo] process(" << data << ")" << std::endl;
  return data*2;
}

