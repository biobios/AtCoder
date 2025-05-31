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
    
    uint64_t mask = (0b1 << 30) - 1;
    
    for (size_t i = 0; i < 30; ++i){
        vector<bool> visited(N, false);
        bool found = false;
        
        mask ^= (0b1 << (29 - i));
        
        queue<size_t> q;
        q.push(0);
        visited[0] = true;
        while(!q.empty() && !found)
        {
            size_t current = q.front();
            q.pop();

            for (const auto& [neighbor, weight] : graph[current])
            {
                if ((weight & mask) != weight)
                    continue;
                
                if (neighbor == N - 1)
                {
                    found = true;
                    break;
                }
                
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        
        if (!found)
            mask ^= (0b1 << (29 - i));
    }
    
    cout << mask << endl;
    
    return 0;
}