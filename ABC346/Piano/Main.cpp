#include <iostream>
#include <cmath>

int main()
{
	std::uint16_t W, B;
	std::cin >> W >> B;
	const std::string piano = "wbwbwwbwbwbw";

	std::uint16_t repeatCount = std::min(W / 7, B / 5);
	W -= repeatCount * 7;
	B -= repeatCount * 5;

	for (std::size_t i = 0; i < piano.size(); i++) {
		
		std::uint16_t w_count = 0;
		std::uint16_t b_count = 0;
		
		std::size_t current = i;

		while (w_count <= W && b_count <= B) {
			if (piano[current] == 'w') {
				w_count++;
			}
			else {
				b_count++;
			}

			if (w_count == W && b_count == B) {
				std::cout << "Yes" << std::endl;
				return 0;
			}

			current = (current + 1) % piano.size();
		}
	}

	std::cout << "No" << std::endl;
	return 0;
}