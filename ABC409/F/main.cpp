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

    void add_elem()
    {
        parent.push_back(parent.size());
        rank.push_back(0);
    }
};

int main()
{
    uint64_t N, Q;
    cin >> N >> Q;
    vector<pair<uint64_t, uint64_t>> nodes(N);
    for (uint64_t i = 0; i < N; ++i)
    {
        cin >> nodes[i].first >> nodes[i].second;
    }
    
    Union_Find uf(N);
    
    map<uint64_t, vector<pair<size_t, size_t>>> distance_map;
    for (size_t i = 0; i < N; ++i)
    {
        for (size_t j = i + 1; j < N; ++j)
        {
            uint64_t distance = abs((int64_t)(nodes[i].first - nodes[j].first)) + abs((int64_t)(nodes[i].second - nodes[j].second));
            distance_map[distance].emplace_back(i, j);
        }
    }
    
    for (size_t i = 0; i < Q; ++i)
    {
        uint64_t q_type;
        cin >> q_type;
        if (q_type == 1)
        {
            uint64_t a, b;
            cin >> a >> b;
            uf.add_elem();
            for (size_t j = 0; j < nodes.size(); ++j)
            {
                const auto& [x, y] = nodes[j];
                uint64_t distance = abs((int64_t)(x - a)) + abs((int64_t)(y - b));
                distance_map[distance].emplace_back(j, nodes.size());
            }
            nodes.push_back({a, b});
        }else if(q_type == 2)
        {
            while(true){
                if (distance_map.empty())
                {
                    cout << -1 << endl;
                    break;
                }

                auto& [distance, pairs] = *distance_map.begin();
                bool merged = false;
                for (const auto& [u, v] : pairs)
                {
                    if (uf.unite(u, v))
                    {
                        merged = true;
                    }
                }
                
                if (merged)
                {
                    cout << distance << endl;
                    distance_map.erase(distance);
                    break;
                }else
                {
                    distance_map.erase(distance);
                    continue;
                }
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