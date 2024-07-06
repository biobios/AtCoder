#include <iostream>

int main() {
	std::uint64_t N;
	std::cin >> N;

	for (std::size_t i = 1; i <= N; i++) {
		if (i % 3 != 0) {
			std::cout << "o";
		}
		else {
			std::cout << "x";
		}
	}

	std::cout << std::endl;
	return 0;
}