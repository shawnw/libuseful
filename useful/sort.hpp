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

#ifndef USEFUL_SORT_HPP
#define USEFUL_SORT_HPP

#include <algorithm>
#include <iterator>
#include <utility>
#include <functional>

/* Additional sorting algorithms that work on iterator ranges. Of note is that
 * insertion and selection sort only need forward iterators, so they'll sort
 * linked list classes without having to use a sort member function. Useful for
 * container agnostic code.
 */

namespace useful {
	template<class RandomAccessIterator>
	void heap_sort(RandomAccessIterator first, RandomAccessIterator last) {
		std::make_heap(first, last);
		std::sort_heap(first, last);
	}
	
	template<class RandomAccessIterator, class Compare>
	void heap_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
		std::make_heap(first, last, comp);
		std::sort_heap(first, last, comp);
	}
	
	template<class ForwardIterator>
	void insertion_sort(ForwardIterator first, ForwardIterator last) {
		for (auto i = first; i != last; ++i)
			std::rotate(std::upper_bound(first, i, *i), i, std::next(i));
	}
		
	template<class ForwardIterator, class Compare>
	void insertion_sort(ForwardIterator first, ForwardIterator last, Compare comp) {
		for (auto i = first; i != last; ++i) 
			std::rotate(std::upper_bound(first, i, *i, comp), i, std::next(i));
	}
	
	template<class ForwardIterator>
	void selection_sort(ForwardIterator first, ForwardIterator last) {
		for (; first != last; ++first)
			std::iter_swap(first, std::min_element(first, last));
	}
		
	template<class ForwardIterator, class Compare>
	void selection_sort(ForwardIterator first, ForwardIterator last, Compare comp) {
		for (; first != last; ++first)
			std::iter_swap(first, std::min_element(first, last, comp));
	}

	/* Useful functions for comparing pairs of values. Unlike the standard < for
	 * pairs, only look at the first or second element. cmp1st and cmp2nd are
	 * functors that work with std::not2 and a user-specific comparison operator,
	 * comp1st and comp2nd are functions that use <. Use whichever works better
	 * for the need.
	 */

	template<class T1, class T2, class Comp = std::less<T1>>
	struct cmp1st {
		using result_type = bool;
		using first_argument_type = std::pair<T1, T2>;
		using second_argument_type = std::pair<T1, T2>;
		Comp c;
		explicit cmp1st(Comp c_ = Comp()) : c(c_) {}
		result_type operator()(const first_argument_type &a, const second_argument_type &b) const {
			return c(a.first, b.first);
		}
	};
	
	template<class T1, class T2>
	bool comp1st(const std::pair<T1, T2> &a, const std::pair<T1, T2> &b) {
		return cmp1st<T1, T2>()(a, b);
	}
	
	template<class T1, class T2, class Comp = std::less<T2>>
	struct cmp2nd {
		using result_type = bool;
		using first_argument_type = std::pair<T1, T2>;
		using second_argument_type = std::pair<T1, T2>;
		Comp c;
		explicit cmp2nd(Comp c_ = Comp()) : c(c_) {}
		result_type operator()(const first_argument_type &a, const second_argument_type &b) const {
			return c(a.second, b.second);
		}	
	};

	template<class T1, class T2>
	bool comp2nd(const std::pair<T1, T2> &a, const std::pair<T1, T2> &b) {
		return cmp2nd<T1, T2>()(a, b);
	}
};

#endif
