#include <iostream>
#include <cmath>

void process() {
	std::uint64_t star_count = 0;
	std::uint64_t review_count = 0;

	for (std::size_t i = 1; i <= 5; i++) {
		std::uint64_t A;
		std::cin >> A;
		star_count += A * i;
		review_count += A;
	}

	std::uint64_t need_star = review_count * 3 - star_count;

	std::uint64_t buf;
	for (std::size_t i = 0; i < 3; i++) std::cin >> buf;

	std::uint64_t four_star_cost;
	std::uint64_t double_four_star_cost;
	std::uint64_t five_star_cost;

	std::cin >> four_star_cost;
	double_four_star_cost = four_star_cost * 2;
	std::cin >> five_star_cost;

	//‚·‚Å‚É•½‹Ï‚RˆÈã‚Ìê‡
	if (star_count >= review_count * 3) {
		std::cout << "0" << std::endl;
		return;
	}

	if (five_star_cost >= double_four_star_cost) {
		std::cout << (need_star * four_star_cost) << std::endl;
	}
	else if (five_star_cost <= four_star_cost) {
		std::cout << (((need_star + 1) / 2) * five_star_cost) << std::endl;
	}
	else {
		std::uint64_t result_cost = 0;
		result_cost += (need_star / 2) * five_star_cost;
		result_cost += (need_star % 2) * four_star_cost;

		std::cout << result_cost << std::endl;
	}
}

int main() {
	std::uint32_t T;
	std::cin >> T;

	for (std::size_t i = 0; i < T; i++) {
		process();
	}
}