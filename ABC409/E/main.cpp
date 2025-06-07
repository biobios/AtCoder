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

void destroy(size_t prev_node, size_t current_node, vector<int64_t> &X, vector<vector<tuple<size_t, uint64_t>>> &graph, uint64_t &result)
{
    for (const auto& [next_node, weight] : graph[current_node])
    {
        if (next_node == prev_node)
            continue;
        
        destroy(current_node, next_node, X, graph, result);
        
        result += abs(X[next_node]) * weight;
        X[current_node] += X[next_node];
    }
}

int main()
{
    uint64_t N;
    cin >> N;
    vector<int64_t> X(N);
    for (uint64_t i = 0; i < N; ++i)
    {
        cin >> X[i];
    }

    vector<vector<tuple<size_t, uint64_t>>> graph(N);
    for (uint64_t i = 0; i < N - 1; ++i)
    {
        uint64_t a, b, w;
        cin >> a >> b >> w;
        a--;
        b--;
        graph[a].emplace_back(b, w);
        graph[b].emplace_back(a, w);
    }
    
    uint64_t result = 0;
    destroy(0, 0, X, graph, result);
    cout << result << endl;
    return 0;
}