#include <iostream>
#include <array>
#include <vector>

void process()
{
	std::uint64_t N;
	std::cin >> N;

	std::vector<std::uint64_t> scores(N);
	for (std::size_t i = 0; i < N; i++)
	{
		char A1, A2, A3, A4, A5;
		std::cin >> A1 >> A2 >> A3 >> A4 >> A5;
		if (A5 == '0') {
			scores[i] = 0;
		}
		else if (A4 == '0') {
			scores[i] = 0;
		}
		else if (A3 == '0') {
			scores[i] = 3;
		}
		else if (A2 == '0') {
			scores[i] = 2;
			if (A1 == '0') scores[i] = 3;
		}
		else if (A1 == '0') {
			scores[i] = 1;
		}
		else {
			scores[i] = 0;
		}
	}
}

int main() {
	std::uint64_t T;
	std::cin >> T;
}
