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

// Union-Find
class UnionFind
{
public:
    UnionFind(size_t size) : parent(size), rank(size, 0), sorted_indexes_limit_10(size)
    {
        for (size_t i = 0; i < size; ++i)
        {
            parent[i] = i;
            sorted_indexes_limit_10[i].push_back(i);
        }
    }

    size_t find(size_t x)
    {
        if (parent[x] == x)
        {
            return x;
        }

        return parent[x] = find(parent[x]);
    }

    void unite(size_t x, size_t y)
    {
        size_t root_x = find(x);
        size_t root_y = find(y);

        if (root_x == root_y)
        {
            return;
        }

        if (rank[root_x] < rank[root_y])
        {
            parent[root_x] = root_y;
            unite_sorted_indexes_limit_10(root_y, root_x);
        }
        else
        {
            parent[root_y] = root_x;
            unite_sorted_indexes_limit_10(root_x, root_y);

            if (rank[root_x] == rank[root_y])
            {
                rank[root_x]++;
            }
        }
    }

    void unite_sorted_indexes_limit_10(size_t root_x, size_t root_y)
    {
        auto &&sorted_indexes_root_x = sorted_indexes_limit_10[root_x];
        auto &&sorted_indexes_root_y = sorted_indexes_limit_10[root_y];

        vector<size_t> sorted_indexes_merged;

        size_t i_x = 0;
        size_t i_y = 0;

        for (size_t i = 0; i < 10; ++i)
        {
            if (i_x < sorted_indexes_root_x.size() && i_y < sorted_indexes_root_y.size())
            {
                if (sorted_indexes_root_x[i_x] > sorted_indexes_root_y[i_y])
                {
                    sorted_indexes_merged.push_back(sorted_indexes_root_x[i_x]);
                    i_x++;
                }
                else
                {
                    sorted_indexes_merged.push_back(sorted_indexes_root_y[i_y]);
                    i_y++;
                }
            }
            else if (i_x < sorted_indexes_root_x.size())
            {
                sorted_indexes_merged.push_back(sorted_indexes_root_x[i_x]);
                i_x++;
            }
            else if (i_y < sorted_indexes_root_y.size())
            {
                sorted_indexes_merged.push_back(sorted_indexes_root_y[i_y]);
                i_y++;
            }
        }

        sorted_indexes_limit_10[root_x] = sorted_indexes_merged;
    }

    bool same(size_t x, size_t y)
    {
        return find(x) == find(y);
    }

    int64_t get_sorted_index_limit_10(size_t x, size_t i)
    {
        if (i >= sorted_indexes_limit_10[find(x)].size())
        {
            return -1;
        }
        return sorted_indexes_limit_10[find(x)][i];
    }

private:
    vector<size_t> parent;
    vector<size_t> rank;
    vector<vector<size_t>> sorted_indexes_limit_10;
};

int main()
{
    uint64_t N, Q;
    cin >> N >> Q;

    UnionFind uf(N);

    for (size_t i = 0; i < Q; ++i)
    {
        uint64_t t;
        cin >> t;

        if (t == 1)
        {
            uint64_t a, b;
            cin >> a >> b;
            a--;
            b--;

            uf.unite(a, b);
        }
        else
        {
            uint64_t v, k;
            cin >> v >> k;

            v--;
            k--;
            auto result = uf.get_sorted_index_limit_10(v, k);

            if (result == -1)
            {
                cout << "-1" << endl;
            }
            else
            {
                cout << result + 1 << endl;
            }
        }
    }

    return 0;
}