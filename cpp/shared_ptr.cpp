// make_shared example
#include <iostream>
#include <memory>
#include <string.h>
//  g++ shared_ptr.cpp --std=c++11
int main () {
  std::shared_ptr<int> foo = std::make_shared<int> (10);
  // same as:
  std::shared_ptr<int> foo2 (new int(10));
  auto bar = std::make_shared<int> (20);
  auto baz = std::make_shared<std::pair<int,int>> (30,40);
  std::cout << "*foo: " << *foo << '\n';
  std::cout << "*bar: " << *bar << '\n';
  std::cout << "*baz: " << baz->first << ' ' << baz->second << '\n';

  const char *helloworld = "hello world"; 
  char *hello = new char[256];
  strcpy(hello, helloworld);
  std::cout<<strlen(hello)<<std::endl;
  std::shared_ptr<char> shared_ptr_hello(hello);
  std::cout<<*shared_ptr_hello<<std::endl;
  std::cout<<*hello<<std::endl;
  std::cout<<*helloworld<<std::endl;
  
  std::cout<< (shared_ptr_hello.get() == hello) <<std::endl;
  return 0;
}

