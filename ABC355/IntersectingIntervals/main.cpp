#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
	std::uint64_t N;
	std::cin >> N;
	std::vector<std::uint64_t> L(N), R(N);

	for (std::uint64_t i = 0; i < N; ++i)
	{
		std::cin >> L[i] >> R[i];
	}

	std::sort(L.begin(), L.end());
	std::sort(R.begin(), R.end());

	std::uint64_t count = 0;

	for (std::size_t l_i = 0, r_i = 0; l_i < N; l_i++) {
		std::uint64_t l = L[l_i];
		while (l > R[r_i]) {
			r_i++;
		}

		count += N - r_i;
	}

	count -= N;
	count -= N * (N - 1) / 2;

	std::cout << count << std::endl;

	return 0;

}
//‚È‚º‚©‚í‚©‚ç‚È‚¢‚¯‚Ç‚Å‚«‚½B