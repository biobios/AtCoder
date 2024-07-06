#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <tuple>
#include <string>
#include <bitset>
#include <algorithm>
#include <utility>
#include <cmath>
#include <atcoder/all>

using namespace std;
using namespace atcoder;

constexpr int64_t MOD = 998244353;

int main()
{
    uint64_t N, K;
    cin >> N >> K;

    if (N == 1)
    {
        cout << 1 << endl;
        return 0;
    }

    int64_t inv_N = inv_mod(N, MOD);
    int64_t result = (N - 1) * inv_N % MOD;

    for (size_t i = 0; i < K; i++)
    {
        result = result * (N - 2) % MOD * inv_N % MOD;
    }

    result += inv_N;
    result %= MOD;

    int64_t inv_N_1 = inv_mod(N - 1, MOD);

    int64_t result_a = ((N * (N + 1) / 2) - 1) % MOD * inv_N_1 % MOD;

    int64_t inv_2 = inv_mod(2, MOD);

    result_a -= result * N % MOD * inv_2 % MOD;

    if (result_a < 0)
    {
        result_a += MOD;
    }

    result_a %= MOD;

    cout << result_a << endl;

    return 0;
}