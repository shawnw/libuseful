#include <iostream>
#include <vector>

#include "useful/math.hpp"
#include "useful/range.hpp"

using namespace useful;

int main(void) {
	int f = 5;
	std::vector<int> foo = {1,2,3,4,5};
	
	std::cout << "5! should be 120, calculated as " << factorial(f) << '\n';
	
	std::cout << "\nVector: {";
	for (auto i : take(foo, -1))
		std::cout << i << ", ";
	std::cout << foo.back() << "}\n";
	
	std::cout << "Sum of vector: " << sum(foo.begin(), foo.end()) << '\n';
	std::cout << "Product of vector: " << product(foo.begin(), foo.end()) << '\n';
	
	return 0;
}