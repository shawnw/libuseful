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
	for (auto i : drop(cfoo, -2))
		std::cout << i << ',';
	std::cout << '\n';
	for (auto i : drop(bar, -2))
		std::cout << i << ',';
	std::cout << '\n';
	
	std::cout << "\nTake 2:\n";
	for (auto i : take(cfoo, 2))
		std::cout << i << ',';
	std::cout << '\n';
	for (auto i : take(bar, 2))
		std::cout << i << ',';
	std::cout << '\n';
	for (const auto &i : take(bar, 2))
		std::cout << i << ',';
	std::cout << '\n';
	
	std::cout << "\nTake -2:\n";
	for (auto i : take(cfoo, -2))
		std::cout << i << ',';
	std::cout << '\n';
	for (auto i : take(bar, -2))
		std::cout << i << ',';
	std::cout << '\n';

	return 0;
}
	
	
	
	
	