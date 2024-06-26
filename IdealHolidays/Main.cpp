#include <iostream>
#include <vector>
#include <set>

int main()
{
	std::uint64_t N, A, B;
	std::cin >> N >> A >> B;
	std::uint64_t daysInWeek = A + B;
	std::set<std::uint64_t> plans;

	for (std::size_t i = 0; i < N; i++)
	{
		std::uint64_t plan;
		std::cin >> plan;
		plans.insert(plan % daysInWeek);
	}
	
	auto begin = plans.cbegin();
	auto end = plans.cend();
	end--;

	std::uint64_t max_diff = daysInWeek + *begin - *end;

	auto it = begin;
	end = plans.cend();
	std::uint64_t prev = *it;
	it++;
	while (it != end)
	{
		std::uint64_t curr = *it;
		max_diff = std::max(max_diff, curr - prev);
		prev = curr;
		it++;
	}

	if (B < max_diff) {
		std::cout << "Yes" << std::endl;
	}
	else {
		std::cout << "No" << std::endl;
	}

	return 0;

}