#include <iostream>
#include <vector>
#include <iterator>

#include "useful/string.hpp"

int main(void) {
  std::string test1 = "this is   a test\tstring to split up.";
  //std::vector<std::string> results;
  
  int words = useful::split(test1, std::ostream_iterator<std::string>(std::cout, "\n"));
  
  std::cout << "The string had " << words << " words.\n";
  
  std::string test2 = "this is the string the test is done on.";
  words = useful::split(test2, "the", std::ostream_iterator<std::string>(std::cout, "\n"));
  
  return 0;
} 