#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

int main()
{
	std::string X_str;
	std::cin >> X_str;
	std::int64_t X;
	std::stringstream(X_str) >> X;

	if (X_str.size() == 1) {
		std::cout << std::ceil(X / 10.0) << std::endl;
	}else if (X_str[0] == '-' && X_str.size() == 2) {
		std::cout << 0 << std::endl;
	}
	else {

		char last_digit = X_str[X_str.size() - 1];
		X_str.erase(X_str.size() - 1);

		std::int64_t X_devided_by_10;
		std::stringstream(X_str) >> X_devided_by_10;
	
		if (X_str[0] != '-' && last_digit != '0') {
			X_devided_by_10++;
		}

		std::cout << X_devided_by_10 << std::endl;
	}

	return 0;
}