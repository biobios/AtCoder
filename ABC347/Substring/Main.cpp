#include <iostream>
#include <set>

int main()
{
	std::string S;
	std::cin >> S;

	std::set<std::string> result;

	for (std::size_t i = 0; i < S.size(); i++) {
		for (std::size_t j = 1; i + j <= S.size(); j++) {
			result.insert(S.substr(i, j));
		}
	}

	std::cout << result.size() << std::endl;
	return 0;
}