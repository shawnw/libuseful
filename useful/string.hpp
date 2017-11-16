/*
The MIT License (MIT)

Copyright (c) 2016 shawnw

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef USEFUL_STRING_HPP
#define USEFUL_STRING_HPP

#include <string>
#include <regex>

namespace useful {

  // perl style split on regular expression functions.
  template<class OutputIterator>
  int split(const std::string &s, const std::regex &re, OutputIterator o) {
    std::regex_token_iterator<std::string::const_iterator> rend{},
      ri{s.begin(), s.end(), re, -1};
      int n = 0;
      while (ri != rend) {
        *o++ = *ri++;
        n += 1;
      }
      return n;
  }

  template<class OutputIterator, class T>
  int split(const std::string &s, const T &re, OutputIterator o) {
    return split(s, std::regex(re), o);
  }

  template<class OutputIterator>
  int split(const std::string &s, OutputIterator o) {
    const static std::regex whitespace{"\\s+"};
    return split(s, whitespace, o);
  }

  inline std::vector<std::string> splitv(const std::string &s, const std::regex &re) {
    std::regex_token_iterator<std::string::const_iterator> rend{},
      ri{s.begin(), s.end(), re, -1};
      return std::vector<std::string>(ri, rend);
  }

  template<class T>
  std::vector<std::string> splitv(const std::string &s, const T &re) {
    return splitv(s, std::regex(re));
  }

  inline std::vector<std::string> splitv(const std::string &s) {
    const static std::regex whitespace{"\\s+"};
    return splitv(s, whitespace);
  }

  /* And a strtok style tokenizing function */
  inline std::vector<std::string> tokenize(const std::string &s, const std::string &tokens) {
    std::string::size_type start{0}, end;
    std::vector<std::string> res;
    while ((end = s.find_first_of(tokens, start)) != std::string::npos) {
      res.push_back(std::move(s.substr(start, end - start)));
      start = end + 1;
    }
    res.push_back(std::move(s.substr(start)));
    return res;
  }
};

#endif
