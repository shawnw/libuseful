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
};

#endif
