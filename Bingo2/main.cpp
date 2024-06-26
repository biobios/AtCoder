#include <iostream>
#include <vector>

int main() {
	std::uint64_t N, T;
	std::cin >> N >> T;

	std::vector<std::uint64_t> horizontal(N);
	std::vector<std::uint64_t> vertical(N);
	std::uint64_t diagonal_1 = 0;
	std::uint64_t diagonal_2 = 0;


	for (std::size_t i = 0; i < T; i++) {
		std::uint64_t A;
		std::cin >> A;
		std::uint64_t x = A % N;
		std::uint64_t y = A / N;

		if (x == 0) {
			x = N - 1;
			y--;
		}
		else {
			x--;
		}

		horizontal[x]++;
		vertical[y]++;
		if (x == y) {
			diagonal_1++;
		}
		if (x + y == N - 1) {
			diagonal_2++;
		}

		if (horizontal[x] == N || vertical[y] == N || diagonal_1 == N || diagonal_2 == N) {
			std::cout << i + 1 << std::endl;
			return 0;
		}
	}

	std::cout << "-1" << std::endl;

	return 0;
}