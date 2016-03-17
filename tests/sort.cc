#include <iostream>
#include <vector>
#include <list>
#include <forward_list>

#include "useful/sort.hpp"
#include "useful/range.hpp"

using namespace useful;

int main(void) {
	std::vector<int> v{7,3,2,9,1,5,4};
	std::list<int> ll{7, 3, 2, 9, 1, 5, 4, 6};
	std::forward_list<int> sll{7, 3, 2, 9, 1, 5, 4, 6};
	
	std::cout << "Original vector and list: {";
	for (auto i : take(v, -1)) 
		std::cout << i << ", ";
	std::cout << v.back() << "}\n";
	
	auto vc = v;
	heap_sort(vc.begin(), vc.end());
	std::cout << "\nAfter heap sort (v): {";
	for (auto i : take(vc, -1))
		std::cout << i << ", ";
	std::cout << vc.back() << "}\n";
		
	vc = v;
	insertion_sort(vc.begin(), vc.end());
	std::cout << "After insertion sort (v): {";
	for (auto i : take(vc, -1))
		std::cout << i << ", ";
	std::cout << vc.back() << "}\n";
		
	vc = v;
	selection_sort(vc.begin(), vc.end());
	std::cout << "After selection sort (v): {";
	for (auto i : take(vc, -1))
		std::cout << i << ", ";
	std::cout << vc.back() << "}\n";

	vc = v;
	merge_sort(vc.begin(), vc.end());
	std::cout << "After merge sort (v): {";
	for (auto i : take(vc, -1))
		std::cout << i << ", ";
	std::cout << vc.back() << "}\n";

	
	auto llc = ll;
	insertion_sort(llc.begin(), llc.end());
	std::cout << "\nAfter insertion sort (l): {";
	for (auto i : take(llc, -1))
		std::cout << i << ", ";
	std::cout << llc.back() << "}\n";

	llc = ll;
	selection_sort(llc.begin(), llc.end());
	std::cout << "After selection sort (l): {";
	for (auto i : take(llc, -1))
		std::cout << i << ", ";
	std::cout << llc.back() << "}\n";

	llc = ll;
	merge_sort(llc.begin(), llc.end());
	std::cout << "After merge sort (l): {";
	for (auto i : take(llc, -1))
		std::cout << i << ", ";
	std::cout << llc.back() << "}\n";
		
	auto sllc = sll;
	insertion_sort(sllc.begin(), sllc.end());
	std::cout << "\nAfter insertion sort (sl): {";
	for (auto i : sllc)
		std::cout << i << ", ";
	std::cout << "}\n";
	
	sllc = sll;
	selection_sort(sllc.begin(), sllc.end());
	std::cout << "After selection sort (sl): {";
	for (auto i : sllc)
		std::cout << i << ", ";
	std::cout << "}\n";
	
	return 0;
}
