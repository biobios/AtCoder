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

    vector<vector<uint64_t>> items(3001);

    for (size_t i = 0; i < N; ++i)
    {
        uint64_t w, v;
        cin >> w >> v;

        items[w].push_back(v);
    }

    vector<int64_t> dp(W + 1, -1ull);

    dp[0] = 0;

    for (size_t i = 0; i < items.size(); ++i)
    {
        if (items[i].empty())
            continue;

        auto dp_next = dp;

        priority_queue<int64_t> pq;
        for (auto v : items[i])
        {
            pq.push(v - 1);
        }

        int64_t value = 0;

        for (size_t j = 1; j * i <= W; ++j)
        {
            auto pq_top = pq.top();
            value += pq_top;
            pq.pop();
            pq.push(pq_top - 2);

            for (size_t k = 0; k + j * i <= W; ++k)
            {
                dp_next[k + j * i] = max(dp_next[k + j * i], dp[k] + value);
            }
        }

        dp = dp_next;
    }

    cout << *max_element(dp.begin(), dp.end()) << endl;

    return 0;
}