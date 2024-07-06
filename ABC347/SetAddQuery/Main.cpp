#include <iostream>
#include <vector>
#include <set>

int main()
{
	std::uint64_t N, Q;
	std::cin >> N >> Q;

	std::vector<std::uint64_t> A(N);
	std::vector<std::size_t> S_added_timings(N);
	std::set<std::uint64_t> S;

	std::vector<std::uint64_t> cumul(Q + 1, 0);

	for (std::size_t i = 0; i < Q; i++)
	{
		std::uint64_t x;
		std::cin >> x;

		if (S.contains(x)) {
			S.erase(x);
			A[x - 1] += cumul[i] - cumul[S_added_timings[x - 1]];
		}
		else {
			S.insert(x);
			S_added_timings[x - 1] = i;
		}

		cumul[i + 1] = cumul[i] + S.size();
	}

	for (auto&& s : S)
	{
		A[s - 1] += cumul[Q] - cumul[S_added_timings[s - 1]];
	}

	for (auto&& a : A)
	{
		std::cout << a << " ";
	}

	return 0;
}