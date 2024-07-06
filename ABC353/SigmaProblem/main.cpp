#include <iostream>

constexpr std::uint64_t pow_ten_eight = 100000000;

int main()
{
	std::uint64_t N;
	std::cin >> N;

	std::uint64_t sum = 0;
	for (std::size_t i = 0; i < N; i++) {
		std::uint64_t A;
		std::cin >> A;
		sum += A;
	}


}