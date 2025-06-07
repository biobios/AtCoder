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

struct Union_Find
{
    vector<int64_t> parent;
    vector<int64_t> rank;

    Union_Find(size_t size)
        : parent(size), rank(size, 0)
    {
        for (size_t i = 0; i < size; ++i)
        {
            parent[i] = i;
        }
    }

    int64_t find(int64_t x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool unite(int64_t x, int64_t y)
    {
        int64_t root_x = find(x);
        int64_t root_y = find(y);
        
        if (root_x != root_y)
        {
            if (rank[root_x] < rank[root_y])
            {
                parent[root_x] = root_y;
            }
            else if (rank[root_x] > rank[root_y])
            {
                parent[root_y] = root_x;
            }
            else
            {
                parent[root_y] = root_x;
                rank[root_x]++;
            }
            return true;
        }
        
        return false;
    }
};

int main()
{
    uint64_t N, Q;
    cin >> N >> Q;
    vector<pair<uint64_t, uint64_t>> nodes(N + Q);
    for (uint64_t i = 0; i < N; ++i)
    {
        cin >> nodes[i].first >> nodes[i].second;
    }
    
    Union_Find uf(N + Q);
    
    priority_queue<tuple<uint64_t, size_t, size_t>, vector<tuple<uint64_t, size_t, size_t>>, greater<>> pq;
    for (size_t i = 0; i < N; ++i)
    {
        for (size_t j = i + 1; j < N; ++j)
        {
            uint64_t distance = abs((int64_t)(nodes[i].first - nodes[j].first)) + abs((int64_t)(nodes[i].second - nodes[j].second));
            pq.emplace(distance, i, j);
        }
    }
    
    size_t current_index = N;
    
    for (size_t i = 0; i < Q; ++i)
    {
        uint64_t q_type;
        cin >> q_type;
        if (q_type == 1)
        {
            uint64_t a, b;
            cin >> a >> b;
            for (size_t j = 0; j < current_index; ++j)
            {
                const auto& [x, y] = nodes[j];
                uint64_t distance = abs((int64_t)(x - a)) + abs((int64_t)(y - b));
                pq.emplace(distance, j, current_index);
            }
            nodes[current_index] = {a, b};
            current_index++;
        }else if(q_type == 2)
        {
            while(true){
                if (pq.empty())
                {
                    cout << -1 << endl;
                    break;
                }

                auto [distance, u, v] = pq.top();
                pq.pop();

                if (uf.find(u) == uf.find(v))
                {
                    continue;
                }
                
                uf.unite(u, v);
                while (!pq.empty() && get<0>(pq.top()) == distance)
                {
                    tie(distance, u, v) = pq.top();
                    pq.pop();
                    uf.unite(u, v);
                }
                
                cout << distance << endl;
                break;
            }
        }else
        {
            uint64_t u, v;
            cin >> u >> v;
            u--; v--;
            if (uf.find(u) == uf.find(v))
            {
                cout << "Yes" << endl;
            }
            else
            {
                cout << "No" << endl;
            }
        }
    }
}