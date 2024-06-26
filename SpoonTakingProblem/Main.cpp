#include <iostream>
#include <vector>

constexpr std::uint64_t MOD_MAGIC_NUMBER = 998244353;

int main()
{
	std::uint64_t N;
	std::cin >> N;

	std::vector<std::uint64_t> P(N + 2);

	for (std::uint64_t i = 0; i < N; ++i)
	{
		std::uint64_t P_i;
		std::cin >> P_i;
		P[P_i] = i;
	}

	P[0] = P[N];
	P[N + 1] = P[1];

	std::string S;
	std::cin >> S;

	std::uint64_t result[2] = { 1, 1 };

	for (std::size_t i = 1; i < N + 1; i++) {
		bool less_than_left = P[i] < P[i - 1];
		bool less_than_right = P[i] < P[i + 1];

		if (!less_than_left && !less_than_right) {
			if (S[i - 1] == '?') {
				result[0] = (result[0] * 2) % MOD_MAGIC_NUMBER;
				result[1] = (result[1] * 2) % MOD_MAGIC_NUMBER;
			}
		}
		else if (less_than_left && !less_than_right) {
			if (S[i - 1] == '?') {
				result[0] = (result[0] * 2) % MOD_MAGIC_NUMBER;
			}
			else if (S[i - 1] == 'L') {
				result[1] = 0;
			}
		}
		else if (!less_than_left && less_than_right) {
			if (S[i - 1] == '?') {
				result[1] = (result[1] * 2) % MOD_MAGIC_NUMBER;
			}
			else if (S[i - 1] == 'R') {
				result[0] = 0;
			}
		}
		else {
			if (S[i - 1] == 'L') {
				result[1] = 0;
			}
			else if (S[i - 1] == 'R') {
				result[0] = 0;
			}
		}
	}

	std::cout << (result[0] + result[1]) % MOD_MAGIC_NUMBER << std::endl;
	return 0;
}