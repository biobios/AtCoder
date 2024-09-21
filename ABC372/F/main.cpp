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
    uint64_t N, M, K;
    cin >> N >> M >> K;

    vector<pair<size_t, size_t>> edge(M);

    for (size_t i = 0; i < M; ++i)
    {
        cin >> edge[i].first >> edge[i].second;
        edge[i].first--;
        edge[i].second--;
    }

    vector<uint64_t> count(N, 0);
    count[0] = 1;

    vector<pair<size_t, uint64_t>> ope;

    for (size_t i = 0; i < K; ++i)
    {
        //        size_t offset = (N - i) % N;
        int64_t offset = N - i;
        while (offset < 0)
        {
            offset += N;
        }

        for (size_t j = 0; j < M; ++j)
        {
            ope.push_back(make_pair(((edge[j].second + offset - 1 + N) % N), count[(edge[j].first + offset) % N]));
        }

        for (auto [index, c] : ope)
        {
            // debug
            cout << "index: " << index << ", c: " << c << endl;
            count[index] += c;
            count[index] %= 998244353;
        }
    }

    uint64_t result = 0;

    for (size_t i = 0; i < N; ++i)
    {
        result += count[i];
        result %= 998244353;
    }

    cout << result << endl;

    return 0;
}