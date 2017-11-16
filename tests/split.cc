#include <iostream>
#include <vector>
#include <iterator>

#include "useful/string.hpp"

int main(void) {
  std::string test1 = "this is\t   a test\tstring to\tsplit up.";
  //std::vector<std::string> results;
  
  int words = useful::split(test1, std::ostream_iterator<std::string>(std::cout, "\n"));
  
  std::cout << "The string had " << words << " words.\n";
  
  std::string test2 = "this is the string the test is done on.";
  auto wordv = useful::splitv(test2, "the");

  for (auto &w : wordv)
  	std::cout << w << '\n';

  wordv = useful::tokenize(test1, "\t");

  for (auto &w : wordv)
    std::cout << w << '\n';

  return 0;
} 
