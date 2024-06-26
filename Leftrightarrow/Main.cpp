#include <iostream>
#include <string>

int main()
{
	std::string str;

	std::cin >> str;

	if (str[0] != '<') {
		std::cout << "No" << std::endl;
		return 0;
	}
	if (str[str.size() - 1] != '>') {
		std::cout << "No" << std::endl;
		return 0;
	}
	for (int i = 1; i < str.size() - 1; i++) {
		if (str[i] != '=') {
			std::cout << "No" << std::endl;
			return 0;
		}
	}

	std::cout << "Yes" << std::endl;
	return 0;
}