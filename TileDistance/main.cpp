#include <iostream>
#include <array>


int main()
{
	std::uint64_t K;
	std::cin >> K;
	std::array<std::uint64_t, 2> S;
	std::array<std::uint64_t, 2> T;

	std::cin >> S[0] >> S[1];
	std::cin >> T[0] >> T[1];

	std::array<std::uint64_t, 2> S_area;
	std::array<std::uint64_t, 2> T_area;

	S_area[0] = S[0] / K;
	S_area[1] = S[1] / K;

	T_area[0] = T[0] / K;
	T_area[1] = T[1] / K;
}