#include <iostream>
#include <cmath>

int main()
{
	std::uint64_t N, A, B;
	std::cin >> N >> A >> B;

	std::string S;
	std::cin >> S;

	std::uint64_t correct_parenthesis = 0;
	std::uint64_t count_left = 0;
	std::uint64_t count_right = 0;
	std::int64_t depth = 0;

	for (std::size_t i = 0; i < 2*N; i++) {
		if (S[i] == '(') {
			depth++;
			count_left++;
		}
		else {
			depth--;
			count_right++;

			if (depth < 0) {
				depth = 0;
			}
			else {
				correct_parenthesis++;
			}
		}
	}

	std::uint64_t non_pair_left = count_left - correct_parenthesis;
	std::uint64_t non_pair_right = count_right - correct_parenthesis;
	std::uint64_t swap_count = (std::min(non_pair_left, non_pair_right) + 1) / 2;
	std::uint64_t transform_count = (std::max(non_pair_left, non_pair_right) - std::min(non_pair_left, non_pair_right)) / 2;

	//debugo—Í
	//std::cout << "correct_parenthesis" << correct_parenthesis << std::endl;
	//std::cout << "non_pair_left" << non_pair_left << std::endl;
	//std::cout << "non_pair_right" << non_pair_right << std::endl;
	//std::cout << "swap_count" << swap_count << std::endl;
	//std::cout << "transform_count" << transform_count << std::endl;


	if (A >= B * 2) {
		std::cout << swap_count * B * 2 + transform_count * B << std::endl;
	}
	else {
		std::cout << swap_count * A + transform_count * B << std::endl;
	}

	return 0;
}