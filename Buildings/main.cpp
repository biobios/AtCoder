#include <iostream>

int main() {
	std::uint64_t N;
	std::cin >> N;

	std::size_t i = 0;
	std::uint64_t first_height;
	std::cin >> first_height;

	for (i = 2; i <= N; i++) {
		std::uint64_t height;
		std::cin >> height;

		if (height > first_height) {
			break;
		}
	}

	if (i > N) {
		std::cout << "-1" << std::endl;
	}
	else {
		std::cout << i << std::endl;
	}

	return 0;
}