#include <iostream>

std::uint64_t popcount(std::uint64_t x)
{
	std::uint64_t count = 0;
	for (std::size_t i = 0; i < 60; i++) {
		count += x & 1;
		x >>= 1;
	}
	return count;
}

int main()
{
	std::uint64_t a, b, C;
	std::cin >> a >> b >> C;

	std::uint64_t C_popcount = popcount(C);

	if (a + b < C_popcount) {
		std::cout << "-1" << std::endl;
		return 0;
	}

	std::uint64_t rest = a + b - C_popcount;
	if (rest % 2 != 0) {
		std::cout << "-1" << std::endl;
		return 0;
	}

	if (rest / 2 > a || rest / 2 > b) {
		std::cout << "-1" << std::endl;
		return 0;
	}

	std::uint64_t for_cancel = rest / 2;
	std::uint64_t a_for_set = a - for_cancel;
	std::uint64_t b_for_set = b - for_cancel;

	std::uint64_t X = 0;
	std::uint64_t Y = 0;
	std::uint64_t window = 1;
	for (std::size_t i = 0; i < 60; i++) {
		if ((window & C) != 0) {
			if (a_for_set > 0) {
				X |= window;
				a_for_set--;
			}
			else {
				Y |= window;
				b_for_set--;
			}
		}
		else {
			if (for_cancel > 0) {
				X |= window;
				Y |= window;
				for_cancel--;
			}
		}
		window <<= 1;
	}

	if (for_cancel != 0 || a_for_set != 0 || b_for_set != 0) {
		std::cout << "-1" << std::endl;
	}else{
		std::cout << X << " " << Y << std::endl;
	}
	return 0;
}