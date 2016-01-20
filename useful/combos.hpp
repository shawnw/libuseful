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

#include <vector>

#include "useful/math.hpp"

namespace useful {
	/* Return the number of combinations of r items of a set of n items */
	constexpr int ncr(int n, int r) {
		return factorial(n) / (factorial(r) * factorial(n - r));
	}

	/* Return the number of permutations of r items of a set of n items */
	constexpr int npr(int n, int r) {
		return factorial(n) / factorial(n - r);
	}

	/* Generate all combinations of R elements from a vector */
	template<typename N>
	class combinations {
	public:
		using result_type = std::vector<std::vector<N>>;
	private:
		std::vector<N> items;
		void gencombos(std::vector<N>, int r, result_type &results);
	public:
		explicit combinations(std::vector<N> i) : items(std::move(i)) {}
		explicit combinations(std::vector<N> &&i) : items(i) {}
		int count(int r) { return ncr(items.size(), r); }
		result_type combos(int r);
	};

	template<typename N>
	void combinations<N>::gencombos(std::vector<N> items, int r, result_type &results) {
		if (r <= 0)
			return;
		else if (r == 1) {
			for (auto i : items) {
				std::vector<N> v { i };
				results.push_back(std::move(v));
			}
		} else {
			int n = 0;
			while (items.size()) {
				result_type nminus1;
				auto i = items.back();
				items.pop_back();
				nminus1.reserve(ncr(items.size(), r - 1));
				gencombos(items, r - 1, nminus1);
				for (auto &c : nminus1) {
					c.push_back(i);
					results.push_back(std::move(c));
				}
				n += 1;
			}
		}
	}

	template<typename N>
	auto combinations<N>::combos(int r) -> result_type {
		if (r < 0 || r > items.size())
			throw std::out_of_range{"combo"};
		result_type combo;
		combo.reserve(count(r));
		gencombos(items, r, combo);
		return combo;
	}
};