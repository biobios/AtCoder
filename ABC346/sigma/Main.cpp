#include <iostream>
#include <set>

int main()
{
	std::uint64_t N, K;
	std::cin >> N >> K;

	std::uint64_t result = K * (K + 1) / 2;
	std::set<std::uint64_t> appeared;

	for (std::size_t i = 0; i < N; i++) {
		std::uint64_t A;
		std::cin >> A;

		if (A > K || appeared.contains(A)) continue;

		appeared.insert(A);
		result -= A;
	}

	std::cout << result << std::endl;
}