#include <vector>
#include <iostream>
#include "useful/range.hpp"

using namespace useful;

int main(void) {
	const std::vector<int> cfoo{1,2,3,4,5};
	std::vector<int> bar{6,7,8,9,10};	
	
	std::cout << "Original:\n";
	for (auto i : cfoo)
		std::cout << i << ',';
	std::cout << '\n';
	for (auto i : bar)
		std::cout << i << ',';
	std::cout << '\n';
		
	
	std::cout << "\nReversed:\n";
	for (auto i : rev(cfoo))
		std::cout << i << ',';
	std::cout << '\n';
	for (auto i : rev(bar))
		std::cout << i << ',';
	std::cout << '\n';
	
	std::cout << "\nDrop 2:\n";
	for (auto i : drop(cfoo, 2))
		std::cout << i << ',';
	std::cout << '\n';
	for (auto i : drop(bar, 2)) 
		std::cout << i << ',';
	std::cout << '\n';
		
	std::cout << "\nDrop -2:\n";
	for (auto i : cdrop(cfoo, -2))
		std::cout << i << ',';
	std::cout << '\n';
	for (auto i : cdrop(bar, -2))
		std::cout << i << ',';
	std::cout << '\n';
	
	std::cout << "\nTake 2:\n";
	for (auto i : take(cfoo, 2))
		std::cout << i << ',';
	std::cout << '\n';
	for (auto i : take(bar, 2))
		std::cout << i << ',';
	std::cout << '\n';
	
	std::cout << "\nTake -2:\n";
	for (auto &i : ctake(cfoo, -2))
		std::cout << i << ',';
	std::cout << '\n';
	for (auto i : ctake(bar, -2))
		std::cout << i << ',';
	std::cout << '\n';

	// These should fail to compile:
	//  auto baz = take_adaptor<const std::vector<int>>(cfoo, 1);
	//  auto baz = take_adaptor<std::vector<int>>(cfoo, 1);
	// but
	//  auto baz = const_take_adaptor<std::vector<int>>(bar, 1);
	// will work, and elements of bar will unable to be modified through
	// baz's iterators:
	//  *baz.begin() = 5;

	return 0;
}
	
	
	
	
	