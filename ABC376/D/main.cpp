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
    uint64_t N, M;
    cin >> N >> M;

    vector<vector<size_t>> G(N);

    for (size_t i = 0; i < M; i++)
    {
        size_t a, b;
        cin >> a >> b;
        a--;
        b--;

        G[a].push_back(b);
    }

    priority_queue<pair<uint64_t, size_t>, vector<pair<uint64_t, size_t>>, greater<pair<uint64_t, size_t>>> pq;
    pq.push({0, 0});

    vector<uint64_t> cost(N, 1e18);

    while (!pq.empty())
    {
        auto [c, v] = pq.top();
        pq.pop();

        for (auto u : G[v])
        {
            if (cost[u] == 1e18)
            {
                cost[u] = c + 1;
                pq.push({c + 1, u});
            }
        }
    }

    if (cost[0] == 1e18)
    {
        cout << "-1" << endl;
    }
    else
    {
        cout << cost[0] << endl;
    }

    return 0;
}