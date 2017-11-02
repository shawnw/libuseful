/*
The MIT License (MIT)

Copyright (c) 2017 shawnw

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

/* Additional sorting algorithms that work on iterator ranges. Of note
 * is that insertion and selection sort only need forward iterators,
 * and quick sort a bidirectional one, so they'll sort linked list
 * classes without having to use a sort member function.
 *
 * Useful for container agnostic code.
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

  template<class BidirectionalIterator, class Compare>
  void merge_sort(BidirectionalIterator first, BidirectionalIterator last, Compare comp) {
    auto length = std::distance(first, last);
    bool isodd = length % 2;
    auto mlast = last;
    if (isodd) {
      length -= 1;
      --mlast;
    }
    for (int s = 1; s <= length / 2; s += s) {
      auto s1s = first;
      auto s1e = s1s, s2e = s1s;
      while (std::distance(first, s1s) + s + s <= length) {
        std::advance(s1e, s);
        std::advance(s2e, s + s);
        std::inplace_merge(s1s, s1e, s2e, comp);
        s1s = s1e = s2e;
      }
      if (std::distance(first, s1s) + s <= length) 
        std::inplace_merge(first, s1s, mlast);
    }
    if (isodd)
      std::inplace_merge(first, mlast, last, comp);
  }
	
  template<class BidirectionalIterator>
  void merge_sort(BidirectionalIterator first, BidirectionalIterator last) {
    using value_type = typename std::iterator_traits<BidirectionalIterator>::value_type;
    merge_sort(first, last, std::less<value_type>());
  }
  
  template<typename BiDirectionalIterator, typename Comp>
  void quick_sort(BiDirectionalIterator start, BiDirectionalIterator end, Comp cmp) {
    if (start == end)
      return;
  
    auto pivot = std::next(start, std::distance(start, end) / 2);
    std::iter_swap(start, pivot);
    auto mid = std::partition(std::next(start), end,
                              [&](const auto &a){ return cmp(a, *start); });  
    auto mid2 = std::prev(mid);
    std::iter_swap(start, mid2);

    quick_sort(start, mid2, cmp);
    quick_sort(mid, end, cmp);
  }

  template<typename BiDirectionalIterator>
  void quick_sort(BiDirectionalIterator start, BiDirectionalIterator end) {
    using value_type = typename std::iterator_traits<BiDirectionalIterator>::value_type;
    quick_sort(start, end, std::less<value_type>());
  }

  /* Useful functions for comparing pairs of values. Unlike the
   * standard < for pairs, only look at the first or second
   * element. cmp1st and cmp2nd are functors that work with a
   * user-specific comparison operator, comp1st and comp2nd are
   * functions that use <. Use whichever works better for the need.
   */

  template<class T1, class T2, class Comp = std::less<T1>>
  struct cmp1st {
    using result_type = bool;
    using argument_type = std::pair<T1, T2>;
    Comp c;
    explicit cmp1st(Comp c_ = Comp()) : c(c_) {}
    result_type operator()(const argument_type &a, const argument_type &b) const {
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
    using argument_type = std::pair<T1, T2>;
    Comp c;
    explicit cmp2nd(Comp c_ = Comp()) : c(c_) {}
    result_type operator()(const argument_type &a, const argument_type &b) const {
      return c(a.second, b.second);
    }	
  };
  
  template<class T1, class T2>
  bool comp2nd(const std::pair<T1, T2> &a, const std::pair<T1, T2> &b) {
    return cmp2nd<T1, T2>()(a, b);
  }
};

#endif
