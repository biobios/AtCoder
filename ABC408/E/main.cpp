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
#include <cstdint>

using namespace std;

int main()
{
    uint64_t N, M;
    cin >> N >> M;
    vector<vector<pair<size_t, uint64_t>>> graph(N);
    
    for (size_t i = 0; i < M; ++i)
    {
        uint64_t u, v, w;
        cin >> u >> v >> w;
        u--; // Convert to 0-based index
        v--; // Convert to 0-based index
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }
    
    set<pair<uint64_t, size_t>> pq; // (cost, node)
    vector<uint64_t> min_cost(N, UINT64_MAX);
    min_cost[N - 1] = 0;
    pq.insert({0, N - 1}); // Start from node N - 1 with cost 0

    while (!pq.empty())
    {
        auto [cost, node] = *pq.begin();
        pq.erase(pq.begin());
        
        if (cost > min_cost[node])
            continue; // Skip if we already found a better cost
        
        for (const auto& [neighbor, weight] : graph[node])
        {
            uint64_t new_cost = cost | weight;
            if (new_cost < min_cost[neighbor])
            {
                pq.erase({min_cost[neighbor], neighbor});
                min_cost[neighbor] = new_cost;
                pq.insert({new_cost, neighbor});
            }
        }
    }
    
    cout << min_cost[0] << endl; // Output the minimum cost to reach node N-1
    return 0;
}