#include <iostream>
#include <vector>

using namespace std;

size_t msb(uint64_t x)
{
	size_t n = 0;
	while (x > 0)
	{
		x >>= 1;
		n++;
	}
	return n;
}

int main()
{
	uint64_t N, M;
	cin >> N >> M;

	vector<uint64_t> Popcounts(64);

	Popcounts[0] = M & 1;
	
	size_t i;

	for (i = 1; i < 64; i++)
	{
		Popcounts[i] = 2 * Popcounts[i - 1] + (M >> i & 1) * ((uint64_t)1 << i) ;
	}

	uint64_t sum_popcount = 0;
	size_t msb_N = msb(N);

	while (msb_N > 0)
	{
		if(msb_N > 1) sum_popcount += Popcounts[msb_N - 2];
		N &= ~((uint64_t)1 << (msb_N - 1));
		sum_popcount += (M >> (msb_N - 1) & 1) * (N + 1);

		sum_popcount %= 998244353;

		msb_N = msb(N);
	}


	cout << sum_popcount% 998244353 << endl;
}