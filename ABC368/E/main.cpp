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
    uint64_t N, M, X_1;
    cin >> N >> M >> X_1;

    vector<tuple<size_t, size_t, uint64_t, uint64_t>> trains(M);

    for (size_t i = 0; i < M; ++i)
    {
        uint64_t A, B, S, T;
        cin >> A >> B >> S >> T;

        trains[i] = make_tuple(A - 1, B - 1, S, T);
    }

    vector<vector<pair<uint64_t, size_t>>> start_with(N);
    vector<vector<pair<uint64_t, size_t>>> end_with(N);

    for (size_t i = 0; i < M; ++i)
    {
        auto [A, B, S, T] = trains[i];

        start_with[A].push_back({S, i});
    }

    for (size_t i = 0; i < N; ++i)
    {
        sort(start_with[i].begin(), start_with[i].end());
    }

    vector<vector<size_t>> late_trains(M);

    // それぞれの列車の到着時刻より出発時刻が遅い列車を探して、late_trainsに格納する

    for (size_t i = 0; i < M; ++i)
    {
        auto [A, B, S, T] = trains[i];

        auto it = lower_bound(start_with[B].begin(), start_with[B].end(), make_pair(T, 0UL));

        while (it != start_with[B].end())
        {
            late_trains[i].push_back(it->second);
            it++;
        }
    }

    // 次数
    vector<uint64_t> in_degree(M);

    for (size_t i = 0; i < M; ++i)
    {
        in_degree[i] = late_trains[i].size();
    }

    // トポロジカルソートを行う
    vector<size_t> toporogical_order;

    queue<size_t> q;

    for (size_t i = 0; i < M; ++i)
    {
        if (in_degree[i] == 0)
        {
            q.push(i);
        }
    }

    while (!q.empty())
    {
        auto current = q.front();
        q.pop();

        toporogical_order.push_back(current);

        for (auto next : late_trains[current])
        {
            in_degree[next]--;

            if (in_degree[next] == 0)
            {
                q.push(next);
            }
        }
    }

    auto it = toporogical_order.begin();

    while (it != toporogical_order.end() && *it != 0)
    {
        it++;
    }

    vector<uint64_t> reach_times(M);
    auto [A, B, S, T] = trains[0];
    reach_times[0] = S + X_1;
    while (it != toporogical_order.end())
    {
        auto current = *it;
        it++;

        auto reach_time = reach_times[current];
        auto [A, B, S, T] = trains[current];

        if (reach_time > S)
        {
            for (auto next : late_trains[current])
            {
                reach_times[next] = max(reach_times[next], reach_time);
            }
        }
    }

    // 遅延を計算
    vector<uint64_t> late_times(M);

    for (size_t i = 0; i < M; ++i)
    {
        auto [A, B, S, T] = trains[i];

        if (reach_times[i] > S)
        {
            late_times[i] = reach_times[i] - S;
        }
    }

    // 答えを出力
    for (size_t i = 1; i < M; ++i)
    {
        cout << late_times[i] << endl;
    }

    return 0;
}