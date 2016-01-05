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

#include <iterator>
#include <type_traits>

namespace useful {

	/* Adaptors for range-based for loops to iterate over a container in reverse
	 * order. Requires a container to provide rbegin() and rend().
	 * const_reverse_adaptor is for immutable containers, and reverse_adaptor for
	 * mutable ones. The rev() function automatically picks the right one to use
	 * based on the const-ness of its argument.
	 *
	 *
	 * | const std::vector<int> v;
	 * | for (auto &i : rev(v)) {}
	 * | for (auto &i : const_reverse_adaptor<std::vector<int>>(v)) {}
	 * 
	 * are equivalent.
	 */
	template<typename Container>
	class const_reverse_adaptor {
	public:
		using container_type = typename std::add_const<Container>::type;
		using const_iterator = typename container_type::const_reverse_iterator;
		using value_type = typename container_type::value_type;
		
	private:
		container_type &c;
	
	public:
		explicit const_reverse_adaptor(container_type &c_)
			: c(c_) {}
	
		const_iterator begin(void) const noexcept { return c.rbegin(); }
		const_iterator cbegin(void) const noexcept { return c.rbegin(); }
		
		const_iterator end(void) const noexcept { return c.rend(); }
		const_iterator cend(void) const noexcept { return c.rend(); }
	};
	
	template<typename Container,
		class NotConst = typename std::enable_if<!std::is_const<Container>::value>::type> 
	class reverse_adaptor {
	public:
		using container_type = Container;
		using iterator = typename container_type::reverse_iterator;
		using const_iterator = typename container_type::const_reverse_iterator;
		using value_type = typename container_type::value_type;
		
	private:
		container_type &c;
	
	public:
		explicit reverse_adaptor(container_type &c_)
			: c(c_) {}
	
		iterator begin(void) noexcept { return c.rbegin(); }
		const_iterator begin(void) const noexcept { return c.rbegin(); }
		const_iterator cbegin(void) const noexcept { return c.rbegin(); }
		
		iterator end(void) noexcept { return c.rend(); }
		const_iterator end(void) const noexcept { return c.rend(); }
		const_iterator cend(void) const noexcept { return c.rend(); }
	};
	
	template<typename Container,
		class Const = typename std::enable_if<std::is_const<Container>::value>::type>
	const_reverse_adaptor<Container> rev(Container &c) {
		return const_reverse_adaptor<Container>(c);
	}
	
	template<typename Container,
		class NotConst = typename std::enable_if<!std::is_const<Container>::value>::type>
	reverse_adaptor<Container> rev(Container &c) {
		return reverse_adaptor<Container>(c);
	} 

	/* Adaptors to iterate over all but the first N elements of a container.
	 *  for (auto i : drop(foo, 5)) skips the first five elements.
	 * If N is negative, drops all but the last abs(N) elements
	 *  for (auto i : drop(foo, -2)) iterates over only the last 2 elements.
	*/
	template<typename Container>
	class const_drop_adaptor {
	public:
		using container_type = typename std::add_const<Container>::type;
		using const_iterator = typename container_type::const_iterator;
		using difference_type = typename container_type::difference_type;
		using value_type = typename container_type::value_type;
		
	private:
		container_type &c;
		difference_type n;
		
	public:
		explicit const_drop_adaptor(container_type &c_, difference_type n_)
			: c(c_), n(n_) {
				if (n < 0)
					n = c.size() + n;
			}
	
		const_iterator begin(void) const noexcept { return cbegin(); }
		const_iterator cbegin(void) const noexcept {
			auto i = c.cbegin();
			std::advance(i, n);
			return i;
		}

		const_iterator end(void) const noexcept { return c.cend(); }
		const_iterator cend(void) const noexcept { return c.cend(); }
	};
	
	template<typename Container,
		class NotConst = typename std::enable_if<!std::is_const<Container>::value>::type>
	class drop_adaptor {
	public:
		using container_type = Container;
		using iterator = typename container_type::iterator;
		using const_iterator = typename container_type::const_iterator;
		using difference_type = typename container_type::difference_type;
		using value_type = typename container_type::value_type;
		
	private:
		container_type &c;
		difference_type n;
	
	public:
		explicit drop_adaptor(container_type &c_, difference_type n_)
			: c(c_), n(n_) {
				if (n < 0)
					n = c.size() + n;
			}
	
		iterator begin(void) noexcept {
			auto i = c.begin();
			std::advance(i, n);
			return i;
		}
		const_iterator begin(void) const noexcept { return cbegin(); }
		const_iterator cbegin(void) const noexcept {
			auto i = c.cbegin();
			std::advance(i, n);
			return i;
		}
		
		iterator end(void) noexcept { return c.end(); }
		const_iterator end(void) const noexcept { return c.cend(); }
		const_iterator cend(void) const noexcept { return c.cend(); }
	};
	
	template<typename Container,
		class Const = typename std::enable_if<std::is_const<Container>::value>::type>
	const_drop_adaptor<Container> drop(Container &c, typename Container::difference_type n) {
		return const_drop_adaptor<Container>(c, n);
	}
	
	template<typename Container,
		class NotConst = typename std::enable_if<!std::is_const<Container>::value>::type>
	drop_adaptor<Container> drop(Container &c, typename Container::difference_type n) {
		return drop_adaptor<Container>(c, n);
	} 
	
	/* Adaptors to iterate over just the first N elements of a container.
	 *  for (auto i : take(foo, 5)) stops after five elements.
	 * If N is negative, stops abs(N) elements from the end. So
	 *  for (auto i : take(foo, -1)) iterates over all but the last element.
	*/
	template<typename Container>
	class const_take_adaptor {
	public:
		using container_type = typename std::add_const<Container>::type;
		using const_iterator = typename container_type::const_iterator;
		using difference_type = typename container_type::difference_type;
		using value_type = typename container_type::value_type;
		
	private:
		container_type &c;
		difference_type n;
		
	public:
		explicit const_take_adaptor(container_type &c_, difference_type n_)
			: c(c_), n(n_) { 
				if (n < 0)
					n = c.size() + n;
		}
	
		const_iterator begin(void) const noexcept { return c.cbegin(); }
		const_iterator cbegin(void) const noexcept { return c.cbegin(); }
		
		const_iterator end(void) const noexcept { return cend(); }
		const_iterator cend(void) const noexcept {
			auto i = c.cbegin();
			std::advance(i, n);
			return i;
		}
	};
	
	template<typename Container,
		class NotConst = typename std::enable_if<!std::is_const<Container>::value>::type>
	class take_adaptor {
	public:
		using container_type = Container;
		using iterator = typename container_type::iterator;
		using const_iterator = typename container_type::const_iterator;
		using difference_type = typename container_type::difference_type;
		using value_type = typename container_type::value_type;
		
	private:
		container_type &c;
		difference_type n;
	
	public:
		explicit take_adaptor(container_type &c_, difference_type n_)
			: c(c_), n(n_) {
				if (n < 0)
					n = c.size() + n;
		}
	
		iterator begin(void) noexcept { return c.begin(); }
		const_iterator begin(void) const noexcept { return c.cbegin(); }
		const_iterator cbegin(void) const noexcept { return c.cbegin(); }
		
		iterator end(void) noexcept { 
			auto i = c.begin();
			std::advance(i, n);
			return i;
		}
		const_iterator end(void) const noexcept { return cend(); }
		const_iterator cend(void) const noexcept { 
			auto i = c.cbegin();
			std::advance(i, n);
			return i;
		}
	};
	
	template<typename Container,
		class Const = typename std::enable_if<std::is_const<Container>::value>::type>
	const_take_adaptor<Container> take(Container &c, typename Container::difference_type n) {
		return const_take_adaptor<Container>(c, n);
	}
	
	template<typename Container,
		class NotConst = typename std::enable_if<!std::is_const<Container>::value>::type>
	take_adaptor<Container> take(Container &c, typename Container::difference_type n) {
		return take_adaptor<Container>(c, n);
	} 
};