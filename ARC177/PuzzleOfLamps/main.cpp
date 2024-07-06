#include <iostream>
#include <vector>
#include <array>
#include <string>

int main()
{

	std::uint64_t N;
	std::cin >> N;
	std::vector<std::uint16_t> lamps(N);

	for (std::size_t i = 0; i < N; i++) {
		char X;
		std::cin >> X;
		lamps[i] = X - '0';
	}

	std::vector<std::array<std::uint16_t, 2>> operations;
	std::uint16_t prev = 0;
	std::uint64_t operations_count = 0;

	for (std::size_t i = 0; i < N; i++) {
		std::uint16_t S = lamps[N - 1 - i];

		if (S == prev) continue;
		
		std::array<std::uint16_t, 2> operation;
		operation[0] = S;
		operation[1] = N - i;
		operations_count += N - i;

		operations.push_back(operation);
		prev = S;
	}

	std::cout << operations_count << std::endl;
	for (auto& operation : operations) {
		if (operation[0] == 0) {
			for(std::size_t i = 0; i < operation[1]; i++)
				std::cout << "B";

		}
		else {
			for(std::size_t i = 0; i < operation[1]; i++)
				std::cout << "A";
		}
	}

	return 0;
}