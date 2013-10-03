// Ourselves
#include "MyModuleBar.hpp"

// Standard Library
#include <iostream>

// Third Party
// - A

// This Project

MyModuleBar::MyModuleBar() {
  std::cout << "[MyModuleBar] Constructor" << std::endl;
}

MyModuleBar::~MyModuleBar() {
  std::cout << "[MyModuleBar] Destructor" << std::endl;
}

std::string MyModuleBar::name() const {
  return "MyModuleBar";
}

int MyModuleBar::process(int data) const {
  std::cout << "[MyModuleBar] process(" << data << ")" << std::endl;
  return data - 1;
}

