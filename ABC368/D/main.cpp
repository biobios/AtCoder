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

uint64_t dfs(vector<vector<size_t>> &V, vector<size_t> &need, size_t current, size_t parent)
{
    uint64_t res = 0;

    for (auto next : V[current])
    {
        if (next == parent)
        {
            continue;
        }

        res += dfs(V, need, next, current);
    }

    // needはソート済み

    if (res != 0 || binary_search(need.begin(), need.end(), current))
    {
        res++;
    }

    return res;
}

int main()
{
    uint64_t N, K;
    cin >> N >> K;

    vector<vector<size_t>> V(N);

    for (uint64_t i = 0; i < N - 1; ++i)
    {
        uint64_t A, B;
        cin >> A >> B;

        V[A - 1].push_back(B - 1);
        V[B - 1].push_back(A - 1);
    }

    vector<size_t> need(K);

    for (uint64_t i = 0; i < K; ++i)
    {
        cin >> need[i];
        need[i]--;
    }

    sort(need.begin(), need.end());

    cout << dfs(V, need, need[0], -1) << endl;

    return 0;
}