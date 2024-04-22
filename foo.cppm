module;
#include <iostream>
export module foo;

export void hello() {
  std::cout << "Hello from C++20 Modules foo" << std::endl;
}