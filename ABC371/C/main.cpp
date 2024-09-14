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
    uint64_t N;
    cin >> N;

    vector<set<size_t>> G_node(N);

    uint64_t MG;
    cin >> MG;

    for (size_t i = 0; i < MG; ++i)
    {
        uint64_t A, B;
        cin >> A >> B;

        G_node[A - 1].insert(B - 1);
        G_node[B - 1].insert(A - 1);
    }

    vector<set<size_t>> H_node(N);

    uint64_t MH;
    cin >> MH;

    for (size_t i = 0; i < MH; ++i)
    {
        uint64_t C, D;
        cin >> C >> D;

        H_node[C - 1].insert(D - 1);
        H_node[D - 1].insert(C - 1);
    }

    vector<vector<uint64_t>> costs(N, vector<uint64_t>(N, 0));

    for (size_t i = 0; i < N - 1; ++i)
    {
        for (size_t j = i + 1; j < N; ++j)
        {
            uint64_t cost;
            cin >> cost;

            costs[i][j] = cost;
            costs[j][i] = cost;
        }
    }

    vector<size_t> perm(N);

    for (size_t i = 0; i < N; ++i)
    {
        perm[i] = i;
    }

    uint64_t min_cost = numeric_limits<uint64_t>::max();

    do
    {
        uint64_t cost = 0;

        for (size_t i = 0; i < N - 1; ++i)
        {
            for (size_t j = i + 1; j < N; ++j)
            {
                if (G_node[i].contains(j) != H_node[perm[i]].contains(perm[j]))
                {
                    cost += costs[perm[i]][perm[j]];
                }
            }
        }

        min_cost = min(min_cost, cost);
    } while (next_permutation(perm.begin(), perm.end()));

    cout << min_cost << endl;

    return 0;
}