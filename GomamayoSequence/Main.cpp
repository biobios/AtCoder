#include <iostream>
#include <vector>
#include <string>
#include <cmath>

int main()
{
	std::uint64_t N;
	std::string S;
	std::cin >> N >> S;

	std::uint64_t C_1;
	std::cin >> C_1;

	std::uint64_t prev[2][2] = { {0, 0}, {((std::uint64_t)1) << 32, ((std::uint64_t)1) << 32} };
	if (S[0] == '0') {
		prev[0][1] = C_1;
	}
	else {
		prev[0][0] = C_1;
	}

	for (std::size_t i = 1; i < S.size(); i++) {
		std::uint64_t next[3][2] = { {0, 0}, {0, 0}, {0, 0} };
		std::uint64_t C;

		std::cin >> C;
		if (S[i] == '0') {
			next[0][0] = prev[0][1];
			next[0][1] = prev[0][0] + C;
			next[1][0] = prev[1][1];
			next[1][1] = prev[1][0] + C;
			next[2][0] = prev[0][0];
			next[2][1] = prev[0][1] + C;
		}
		else {
			next[0][0] = prev[0][1] + C;
			next[0][1] = prev[0][0];
			next[1][0] = prev[1][1] + C;
			next[1][1] = prev[1][0];
			next[2][0] = prev[0][0] + C;
			next[2][1] = prev[0][1];
		}

		prev[0][0] = next[0][0];
		prev[0][1] = next[0][1];

		if (next[1][0] < next[2][0]) {
			prev[1][0] = next[1][0];
		}
		else {
			prev[1][0] = next[2][0];
		}

		if (next[1][1] < next[2][1]) {
			prev[1][1] = next[1][1];
		}
		else {
			prev[1][1] = next[2][1];
		}
	}

	std::cout << std::min(prev[1][0], prev[1][1]) << std::endl;
}