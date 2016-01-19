#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <vector>
#include <functional>

#include <useful/sort.hpp>
#include <useful/range.hpp>

using namespace useful;

using wcount = std::map<std::string, int>;

int main(void) {
	wcount words;
	std::string word;

	while (std::cin >> word)
		words[word] += 1;
	
	std::vector<std::pair<std::string, int>> wordv(words.begin(), words.end());
	std::partial_sort(wordv.begin(), wordv.begin() + 10, wordv.end(),
			cmp2nd<std::string, int, std::greater<int>>()
			//std::not2(cmp2nd<std::string, int>()) 
			//[](auto &a, auto &b) { return a.second > b.second; }			
			);
	
	for (const auto p : take(wordv, 10))
		std::cout << p.second << ": " << p.first << '\n';
	
	return 0;
}