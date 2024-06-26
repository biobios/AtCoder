#include <iostream>
#include <map>

int main()
{
	std::uint64_t N;
	std::cin >> N;

	std::map<std::uint64_t, std::uint64_t> taste_score_min;

	for (std::size_t i = 0; i < N; i++) {
		std::uint64_t A, C;
		std::cin >> A >> C;
		auto it = taste_score_min.find(C);
		if (it == taste_score_min.end()) {
			taste_score_min[C] = A;
		}
		else {
			if (A < it->second) {
				it->second = A;
			}
		}
	}

	std::uint64_t min_score_max = 0;

	for (auto it = taste_score_min.begin(); it != taste_score_min.end(); it++) {
		if (it->second > min_score_max) {
			min_score_max = it->second;
		}
	}

	std::cout << min_score_max << std::endl;
	return 0;
}