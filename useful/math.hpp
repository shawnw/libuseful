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

#include <numeric>
#include <functional>

namespace useful {

	constexpr int factorial(int n) {
		return n == 1 ? 1 : n * factorial(n - 1);
	}

	template<class InputIterator>
	auto sum(InputIterator b, InputIterator e)
		-> typename InputIterator::value_type {
			using t = typename InputIterator::value_type;
			return std::accumulate(b, e, static_cast<t>(0));
	}
	
	template<class InputIterator>
	auto product(InputIterator b, InputIterator e)
		-> typename InputIterator::value_type {
			using t = typename InputIterator::value_type;
			return std::accumulate(b, e, static_cast<t>(1), std::multiplies<t>());
	}
};