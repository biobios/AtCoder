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

constexpr uint64_t MOD = 998244353;

int main()
{
    uint64_t N, Q;
    cin >> N >> Q;

    vector<size_t> P(Q);
    vector<uint64_t> V(Q);
    for (size_t i = 0; i < Q; ++i)
    {
        cin >> P[i] >> V[i];
        P[i]--;
    }

    vector<uint64_t> selectables(Q, 0); // 0で両方選択可能、1で左のみ、2で右のみ
    vector<vector<pair<uint64_t, size_t>>> lefts(N);
    vector<vector<pair<uint64_t, size_t>>> rights(N);

    for (size_t i = 0; i < Q; ++i)
    {
        auto p = P[i];
        auto v = V[i];

        // lefts[p]でvより大きいものを抽出する。

        vector<pair<uint64_t, size_t>> lefts_v;
        for (size_t j = 0; j < lefts[p].size(); ++j)
        {
            if (lefts[p][j].first > v)
            {
                lefts_v.push_back(lefts[p][j]);
            }
        }

        // rights[p]でvより大きいものを抽出する。

        vector<pair<uint64_t, size_t>> rights_v;
        for (size_t j = 0; j < rights[p].size(); ++j)
        {
            if (rights[p][j].first > v)
            {
                rights_v.push_back(rights[p][j]);
            }
        }

        // 両方空なら、selectables[p] = 0

        // どちらかが空なら, 空でない方の集合を選択する。
        // 空でない方の集合がleftsなら、集合のインデックスのselectableを1にする。
        // その過程で2になるものがあれば、出力は0とする。
        // 空でない方の集合がrightsなら、集合のインデックスのselectableを2にする。
        // その過程で1になるものがあれば、出力は0とする。
        // lefts[p]にもrights[p]にもvより大きいものがなければ、両方選択可能とする。

        if (lefts_v.empty() && rights_v.empty())
        {
            selectables[i] = 0;
        }
        else if (lefts_v.empty())
        {
            selectables[i] = 2;
            for (auto [value, index] : rights_v)
            {
                if (selectables[index] == 2)
                {
                    cout << "0" << endl;
                    return 0;
                }
                selectables[index] = 1;
            }
        }
        else if (rights_v.empty())
        {
            selectables[i] = 1;
            for (auto [value, index] : lefts_v)
            {
                if (selectables[index] == 1)
                {
                    cout << "0" << endl;
                    return 0;
                }
                selectables[index] = 2;
            }
        }
        else
        {
            cout << "0" << endl;
            return 0;
        }

        // pを含む左右の集合にvを追加する。
        for (size_t j = 0; j <= p; ++j)
        {
            rights[j].push_back({v, i});
        }
        for (size_t j = p; j < N; ++j)
        {
            lefts[j].push_back({v, i});
        }
    }

    // 両方選択可能なものを数える。
    uint64_t count = 0;
    for (auto selectable : selectables)
    {
        if (selectable == 0)
        {
            count++;
        }
    }

    // pow(2, count)のmodを取る。
    uint64_t result = 1;
    while (count > 0)
    {
        result = (result * 2) % MOD;
        count--;
    }

    cout << result << endl;
}