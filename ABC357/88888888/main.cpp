#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

constexpr uint64_t MOD = 998244353;

uint64_t msb(uint64_t N)
{
	uint64_t msb = 0;
	while (N >>= 1) msb++;
	return msb;
}

uint64_t pow_mod(uint64_t base, uint64_t exponent, uint64_t mod)
{
	uint64_t result = 1;
	while (exponent > 0)
	{
		if (exponent & 1)
		{
			result = (result * base) % mod;
		}
		base = (base * base) % mod;
		exponent >>= 1;
	}
	return result;
}

uint64_t process(uint64_t N, uint64_t decimal_digits, uint64_t consecutive)
{
	if (consecutive == 0)
	{
		return 0;
	}

	uint64_t N_mod = N % MOD;
	uint64_t consecutive_msb = msb(consecutive);

	// consecutive‚ÌÅãˆÊƒrƒbƒg‚ğ0‚É‚·‚é
	consecutive &= (1ull << consecutive_msb) - 1;

	uint64_t result = process(N, decimal_digits, consecutive);
	result = (result * pow_mod(10, decimal_digits * (1ull << consecutive_msb), MOD)) % MOD;

	uint64_t intermediate_result = N_mod;
	
	for (size_t i = 0; i < consecutive_msb; i++)
	{
		intermediate_result = intermediate_result * (pow_mod(10, decimal_digits * pow(2, i), MOD) + 1) % MOD;
		intermediate_result %= MOD;
	}

	result = (result + intermediate_result) % MOD;

	return result;
}

int main()
{
	uint64_t N;
	cin >> N;

	uint64_t decimal_digits = 0;
	uint64_t power_of_10 = 1;
	
	while (power_of_10 <= N)
	{
		decimal_digits++;
		power_of_10 *= 10;
	}

	uint64_t result = process(N, decimal_digits, N);

	cout << result << endl;

	return 0;
}