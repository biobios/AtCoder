#include <iostream>
#include <vector>
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
    uint64_t N, K;
    cin >> N >> K;

    vector<uint64_t> P(N);
    for (size_t i = 0; i < N; i++)
    {
        cin >> P[i];
    }

    vector<vector<uint64_t>> dp(N, vector<uint64_t>(N, 0));
    vector<pair<uint64_t, uint64_t>> operation;

    // for (size_t i = N; i > 0; i--)
    // {
    //     auto &&it = find(P.begin(), P.end(), i);

    //     uint64_t d = distance(P.begin(), it);
    //     if (d + K >= N)
    //         continue;

    //     auto &&range = it + K;
    //     while (range != P.end())
    //     {

    //         auto it2 = range;
    //         while (range != P.end())
    //         {
    //             if (*it2 < *range && *range < *it)
    //                 it2 = range;
    //             range++;
    //         }

    //         if (*it < *it2)
    //             break;

    //         operation.push_back({distance(P.begin(), it) + 1, distance(P.begin(), it2) + 1});
    //         swap(*it, *it2);
    //         it = it2;

    //         d = distance(P.begin(), it);
    //         if (d + K >= N)
    //             break;

    //         range = it + K;
    //     }
    // }

    // cout << operation.size() << endl;
    // for (auto &&op : operation)
    // {
    //     cout << op.first << " " << op.second << endl;
    // }

    return 0;
}