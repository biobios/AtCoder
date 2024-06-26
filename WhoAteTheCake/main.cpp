#include <iostream>

int main() {
	std::uint64_t A, B;
	std::cin >> A >> B;

	if (A == B) {
		std::cout << "-1" << std::endl;
	}
	else if (A == 1) {
		if (B == 2) {
			std::cout << "3" << std::endl;
		}
		else {
			std::cout << "2" << std::endl;
		}
	}
	else if (A == 2) {
		if (B == 1) {
			std::cout << "3" << std::endl;
		}
		else {
			std::cout << "1" << std::endl;
		}
	}
	else {
		if (B == 1) {
			std::cout << "2" << std::endl;
		}
		else {
			std::cout << "1" << std::endl;
		}
	}

	return 0;
}