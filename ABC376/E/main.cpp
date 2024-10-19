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

void process()
{
    uint64_t N, K;
    cin >> N >> K;

    vector<pair<uint64_t, uint64_t>> AB(N);

    for (size_t i = 0; i < N; i++)
    {
        cin >> AB[i].first;
    }

    for (size_t i = 0; i < N; i++)
    {
        cin >> AB[i].second;
    }

    sort(AB.begin(), AB.end());

    if (K == 1)
    {
        uint64_t result = 1e18;
        for (auto [A, B] : AB)
        {
            result = min(result, A * B);
        }

        cout << result << endl;
        return;
    }

    uint64_t sum_B = 0;
    priority_queue<uint64_t, vector<uint64_t>> pq;
    for (size_t i = 0; i < K - 1; ++i)
    {
        sum_B += AB[i].second;
        pq.push(AB[i].second);
    }

    uint64_t result = 1e18;
    for (size_t i = K - 1; i < N; ++i)
    {
        auto [A, B] = AB[i];

        result = min(result, (sum_B + B) * A);

        auto max_B = pq.top();
        if (max_B <= B)
            continue;

        pq.pop();
        pq.push(B);
        sum_B -= max_B - B;
    }

    cout << result << endl;
}

int main()
{
    uint64_t T;
    cin >> T;

    for (size_t i = 0; i < T; i++)
    {
        process();
    }
}