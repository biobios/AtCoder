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
    vector<vector<tuple<size_t, uint64_t>>> G(N);
    for (uint64_t i = 0; i < M; ++i) {
        uint64_t u, v, w;
        cin >> u >> v >> w;
        --u; --v; // Convert to 0-based index
        G[u].emplace_back(v, w);
    }
    
    vector<set<uint64_t>> distances(N);
    distances[0].insert(0);
    queue<tuple<size_t, uint64_t>> q;
    q.emplace(0, 0);
    while (!q.empty()) {
        auto [current_node, current_distance] = q.front();
        q.pop();

        for (const auto& [next_node, weight] : G[current_node]) {
            uint64_t new_distance = current_distance ^ weight;
            if (distances[next_node].contains(new_distance)) {
                continue;
            }
            
            distances[next_node].insert(new_distance);
            q.emplace(next_node, new_distance);
        }
    }
    
    if (distances[N - 1].empty()) {
        cout << "-1" << endl;
    } else {
        cout << *distances[N - 1].begin() << endl;
    }
    
    return 0;
}