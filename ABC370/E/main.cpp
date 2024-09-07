#include <iostream>
#include <vector>
#include <array>
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

using namespace std;

constexpr uint64_t MOD = 998244353;

int main()
{
    uint64_t N;
    int64_t K;
    cin >> N >> K;

    map<int64_t, uint64_t> sum_map;
    sum_map[0] = 1;
    vector<int64_t> dp(N + 1, 0);

    dp[0] = 1;

    int64_t dp_sum = 1;

    int64_t sum = 0;

    for (size_t i = 0; i < N; ++i)
    {
        int64_t a;
        cin >> a;
        sum += a;

        dp[i + 1] = dp_sum;

        if (sum_map.contains(sum - K))
        {
            dp[i + 1] -= sum_map[sum - K];
            dp[i + 1] += MOD;
            dp[i + 1] %= MOD;
        }

        dp_sum += dp[i + 1];
        dp_sum %= MOD;

        sum_map[sum] += dp[i + 1];
        sum_map[sum] %= MOD;
    }

    cout << dp[N] << endl;

    return 0;
}