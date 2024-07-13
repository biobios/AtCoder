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
    uint64_t N, M;
    cin >> N >> M;
    vector<vector<pair<int64_t, uint64_t>>> edge(2 * N);
    for (size_t i = 0; i < N; ++i)
    {
        uint64_t A;
        cin >> A;
        edge[2 * i].push_back({2 * i + 1, A});
    }

    for (size_t i = 0; i < M; ++i)
    {
        uint64_t U, V, B;
        cin >> U >> V >> B;
        U--;
        V--;
        edge[2 * U + 1].push_back({2 * V, B});
        edge[2 * V + 1].push_back({2 * U, B});
    }

    vector<uint64_t> cost(2 * N, -1ull);
    //                  cost, node
    priority_queue<pair<uint64_t, size_t>, vector<pair<uint64_t, size_t>>, greater<pair<uint64_t, size_t>>> pq;
    pq.push({0, 0});
    while (!pq.empty())
    {
        auto [c, n] = pq.top();
        pq.pop();
        if (cost[n] < c)
        {
            continue;
        }
        cost[n] = c;
        for (auto [next, w] : edge[n])
        {
            if (cost[next] > c + w)
            {
                pq.push({c + w, next});
            }
        }
    }

    for (size_t i = 1; i < N; i++)
    {
        cout << cost[2 * i + 1] << " ";
    }
    cout << endl;

    return 0;
}