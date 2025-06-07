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
    map<size_t, set<size_t>> group_map;

    Union_Find(size_t size)
        : parent(size), rank(size, 0)
    {
        for (size_t i = 0; i < size; ++i)
        {
            parent[i] = i;
            group_map[i].insert(i);
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

    void unite(int64_t x, int64_t y)
    {
        int64_t root_x = find(x);
        int64_t root_y = find(y);
        
        if (root_x != root_y)
        {
            if (rank[root_x] < rank[root_y])
            {
                parent[root_x] = root_y;
                group_map[root_y].merge(group_map[root_x]);
                group_map.erase(root_x);
            }
            else if (rank[root_x] > rank[root_y])
            {
                parent[root_y] = root_x;
                group_map[root_x].merge(group_map[root_y]);
                group_map.erase(root_y);
            }
            else
            {
                parent[root_y] = root_x;
                rank[root_x]++;
                group_map[root_x].merge(group_map[root_y]);
                group_map.erase(root_y);
            }
        }
    }

    void add_elem()
    {
        parent.push_back(parent.size());
        rank.push_back(0);
        group_map[parent.size() - 1].insert(parent.size() - 1);
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

    
    for (size_t i = 0; i < Q; ++i)
    {
        uint64_t q_type;
        cin >> q_type;
        if (q_type == 1)
        {
            uint64_t a, b;
            cin >> a >> b;
            uf.add_elem();
            nodes.push_back({a, b});
        }else if(q_type == 2)
        {
            if (uf.group_map.size() < 2)
            {
                cout << "-1" << endl;
                continue;
            }
            vector<pair<uint64_t, uint64_t>> min_distance_nodes;
            uint64_t min_distance = UINT64_MAX;
            for (auto it_i = uf.group_map.begin(); it_i != uf.group_map.end(); ++it_i)
            {
                for (auto it_j = next(it_i); it_j != uf.group_map.end(); ++it_j)
                {
                    uint64_t min_distance_i_j = UINT64_MAX;
                    size_t i = it_i->first;
                    size_t j = it_j->first;
                    for (const auto& elem_i : it_i->second)
                    {
                        for (const auto& elem_j : it_j->second)
                        {
                            uint64_t distance = abs((int64_t)(nodes[elem_i].first - nodes[elem_j].first)) + abs((int64_t)(nodes[elem_i].second - nodes[elem_j].second));
                            if (distance < min_distance_i_j)
                            {
                                min_distance_i_j = distance;
                            }
                        }
                    }
                    
                    if (min_distance_i_j < min_distance)
                    {
                        min_distance = min_distance_i_j;
                        min_distance_nodes.clear();
                        min_distance_nodes.push_back({i, j});
                    }
                    else if (min_distance_i_j == min_distance)
                    {
                        min_distance_nodes.push_back({i, j});
                    }
                }
            }
            
            for (const auto& [i, j] : min_distance_nodes)
            {
                uf.unite(i, j);
            }
            
            cout << min_distance << endl;
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