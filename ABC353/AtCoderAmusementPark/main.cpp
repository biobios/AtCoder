#include <iostream>

int main()
{
	std::uint64_t N, K;
	std::cin >> N >> K;

	std::uint64_t available_seats = K;
	std::size_t i = 0;
	std::size_t attraction_start_count = 1;
	std::uint64_t first_group_size;
	std::cin >> first_group_size;

	while (i < N) {
		if (first_group_size <= available_seats) {
			available_seats -= first_group_size;

			i++;
			if (i >= N) {
				break;
			}
			std::cin >> first_group_size;
		}
		else {
			available_seats = K;
			attraction_start_count++;
		}
	}

	std::cout << attraction_start_count << std::endl;

	return 0;
}