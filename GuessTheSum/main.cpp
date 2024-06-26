#include <iostream>

int main()
{
	std::uint64_t N, L, R;
	std::cin >> N >> L >> R;

	std::uint64_t deff = R - L + 1;
	
	std::uint64_t i = 0;
	std::uint64_t power_2_i = 1;
	
	while (power_2_i < deff)
	{
		power_2_i *= 2;
		i++;
	}

	std::uint64_t j = 0;
	std::int64_t deff_L_l = L;
	while (deff_L_l > power_2_i / 2) {
		j++;
		deff_L_l = L - power_2_i * j;
		if(deff_L_l < 0) deff_L_l *= -1;
	}
}