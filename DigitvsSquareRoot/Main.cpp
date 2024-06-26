#include <iostream>
#include <cmath>
std::size_t debug_count = 0;

void debug() {
	std::cout << "debug: " << debug_count << std::endl;
	debug_count++;
}

void process() {
	std::uint64_t N;
	std::cin >> N;

	std::uint64_t result = 0;

	for (std::uint64_t y = 1; y * y <= N; y++) {
		std::uint64_t x_min = y * y;
		std::uint64_t x_max = std::min((y + 1) * (y + 1) - 1, N);

		std::uint64_t times = 1;
		while (y * times < x_min) times *= 10;

		std::uint64_t current = y * times;

		while (x_max >= current) {
			std::uint64_t limit = (y + 1) * times;
			if (limit > x_max) {
				result += (x_max - current) + 1;
			}
			else {
				result += (limit - current);
			}

			times *= 10;
			current = y * times;
			debug();
		}
	}

	std::cout << result << std::endl;
}

int main()
{
	std::uint64_t T;
	std::cin >> T;

	for (std::size_t i = 0; i < T; i++) {
		process();
	}
}