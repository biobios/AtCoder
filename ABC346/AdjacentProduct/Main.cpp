#include <iostream>
#include <vector>

int main()
{
	std::uint16_t N;
	std::cin >> N;

	std::vector<std::uint16_t> result;

	std::uint16_t prev;
	std::cin >> prev;

	for (std::size_t i = 1; i < N; i++)
	{
		std::uint16_t current;
		std::cin >> current;

		result.push_back(prev * current);
		prev = current;
	}

	for (const auto& i : result)
	{
		std::cout << i << " ";
	}

	std::cout << std::endl;
	return 0;
}