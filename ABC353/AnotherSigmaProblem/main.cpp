#include <iostream>
#include <vector>
#include <string>
#include <cmath>

constexpr std::uint64_t MOD = 998244353;

int main() {
	std::uint64_t N;
	std::cin >> N;

	std::vector<std::string> A(N);
	std::uint64_t result = 0;
	for (std::size_t i = 0; i < N; i++) {
		std::cin >> A[i];
		result += (std::stoull(A[i]) * i) % MOD;
	}

	std::uint64_t keta = 0;
	for (std::size_t i = N - 1; i > 0; i--) {
		keta += std::pow(10, A[i].size());
		keta %= MOD;
		result += (std::stoull(A[i - 1]) * keta) % MOD;
		result %= MOD;
	}

	std::cout << result << std::endl;

	return 0;
}