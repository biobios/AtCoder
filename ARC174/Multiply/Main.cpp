#include <iostream>
#include <cmath>
#include <vector>


int main()
{
	std::uint64_t N;
	std::int64_t C;
	std::cin >> N >> C;

	std::vector<std::int64_t> table(N);
	for (std::size_t i = 0; i < table.size(); i++) {
		table[i] = 0;
	}

	std::int64_t sum = 0;
	std::int64_t current_sum = 0;
	std::int64_t max_or_min = 0;
	
	if (C >= 1) {
		for (std::size_t i = 0; i < N; i++) {
			std::int64_t A;
			std::cin >> A;
			sum += A;
			current_sum += A;
			max_or_min = std::max(max_or_min, current_sum);

			if (current_sum < 0) {
				current_sum = 0;
			}
		}
	}
	else {
		for (std::size_t i = 0; i < N; i++) {
			std::int64_t A;
			std::cin >> A;
			sum += A;
			current_sum += A;
			max_or_min = std::min(max_or_min, current_sum);

			if (current_sum > 0) {
				current_sum = 0;
			}
		}
	}

	sum -= max_or_min;
	sum += max_or_min * C;
	
	std::cout << sum << std::endl;
	return 0;
	
}