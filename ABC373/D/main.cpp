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

    vector<vector<pair<size_t, int64_t>>> graph(N);

    for (size_t i = 0; i < M; ++i)
    {
        size_t u, v;
        int64_t w;
        cin >> u >> v >> w;

        u--;
        v--;

        graph[u].push_back({v, w});
        graph[v].push_back({u, -w});
    }

    vector<int64_t> values(N);
    set<size_t> not_visited;

    for (size_t i = 0; i < N; ++i)
    {
        not_visited.insert(i);
    }

    while (!not_visited.empty())
    {
        size_t start = *not_visited.begin();
        not_visited.erase(start);

        queue<pair<int64_t, size_t>> q;
        q.push({0, start});

        while (!q.empty())
        {
            auto [value, current] = q.front();
            q.pop();

            values[current] = value;

            for (auto [next, weight] : graph[current])
            {
                if (!not_visited.contains(next))
                    continue;

                not_visited.erase(next);
                q.push({value + weight, next});
            }
        }
    }

    for (auto value : values)
    {
        cout << value << " ";
    }

    cout << endl;

    return 0;
}