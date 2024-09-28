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

int main()
{
    uint64_t N, W;

    cin >> N >> W;

    vector<pair<uint64_t, uint64_t>> items(N);

    for (size_t i = 0; i < N; ++i)
    {
        uint64_t w, v;
        cin >> w >> v;

        items[i] = {v, w};
    }

    vector<int64_t> dp(W + 1, -1ull);

    dp[0] = 0;

    for (size_t i = 0; i < N; ++i)
    {
        auto [value, weight] = items[i];
        auto next_dp = dp;

        for (size_t j = 1; j * weight <= W; j *= 2)
        {
            auto multi_val = value * j - j * j;
            auto multi_weight = weight * j;

            for (size_t k = 0; k + multi_weight <= W; ++k)
            {
                next_dp[k + multi_weight] = max(next_dp[k + multi_weight], (int64_t)(dp[k] + multi_val));
            }
        }

        dp = move(next_dp);
    }

    cout << *max_element(dp.begin(), dp.end()) << endl;

    return 0;
}