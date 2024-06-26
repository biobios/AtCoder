#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

int main() {
	std::uint64_t N, H;
	std::cin >> N >> H;

	std::vector<std::uint64_t> A(N);
	std::vector<std::pair<std::uint64_t, std::size_t>> X(N);

	for (std::size_t i = 0; i < N; ++i) {
		std::uint64_t X_i;
		std::cin >> X_i;
		X[i] = {X_i, i};
	}

	std::sort(X.begin(), X.end());
	
}