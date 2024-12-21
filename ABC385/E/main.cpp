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
    uint64_t N;
    cin >> N;

    vector<vector<size_t>> G(N);
    for (size_t i = 0; i < N - 1; ++i)
    {
        uint64_t a, b;
        cin >> a >> b;
        a--;
        b--;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    uint64_t ans = -1ull;

    for (size_t i = 0; i < N; ++i)
    {
        uint64_t count = 1;

        vector<uint64_t> chiled_count;
        for (size_t j = 0; j < G[i].size(); ++j)
        {
            chiled_count.push_back(G[G[i][j]].size() - 1);
        }

        sort(chiled_count.begin(), chiled_count.end());

        for (size_t j = 0; j < chiled_count.size(); ++j)
        {
            count = max(count, 1 + (1 + chiled_count[j]) * (chiled_count.size() - j));
        }

        ans = min(ans, N - count);
    }

    cout << ans << endl;

    return 0;
}