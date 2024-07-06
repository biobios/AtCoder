#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
	std::uint64_t N, K;
	std::cin >> N >> K;

	std::vector<std::uint64_t> result;

	for (std::size_t i = 0; i < N; i++) {
		std::uint64_t A;
		std::cin >> A;
		if (A % K == 0) {
			result.push_back(A / K);
		}
	}

	std::sort(result.begin(), result.end());

	for (auto& i : result) {
		std::cout << i << " ";
	}

	std::cout << std::endl;

	return 0;
}