#include <iostream>

constexpr std::uint64_t A_VALUE = 1;
constexpr std::uint64_t B_VALUE = 5;
constexpr std::uint64_t C_VALUE = 10;
constexpr std::uint64_t D_VALUE = 50;
constexpr std::uint64_t E_VALUE = 100;
constexpr std::uint64_t F_VALUE = 500;

int main() {
	std::uint64_t A, B, C, D, E, F;
	std::cin >> A >> B >> C >> D >> E >> F;

	std::uint64_t N;
	std::cin >> N;

	for (std::size_t i = 0; i < N; i++) {
		std::uint64_t X;
		std::cin >> X;

		while (X != 0) {
			if (X >= F_VALUE && F > 0) {
				F--;
				X -= F_VALUE;
			}
			else if (X >= E_VALUE && E > 0) {
				E--;
				X -= E_VALUE;
			}
			else if (X >= D_VALUE && D > 0) {
				D--;
				X -= D_VALUE;
			}
			else if (X >= C_VALUE && C > 0) {
				C--;
				X -= C_VALUE;
			}
			else if (X >= B_VALUE && B > 0) {
				B--;
				X -= B_VALUE;
			}
			else if (X >= A_VALUE && A > 0) {
				A--;
				X -= A_VALUE;
			}
			else {
				std::cout << "No" << std::endl;
				return 0;
			}
		}
	}

	std::cout << "Yes" << std::endl;
	
	return 0;
}