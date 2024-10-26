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
    uint64_t N, M;
    cin >> N >> M;

    vector<pair<uint64_t, uint64_t>> Ranges(N);

    for (size_t i = 0; i < N; ++i)
    {
        uint64_t l, r;
        cin >> l >> r;
        Ranges[i] = {r, l};
    }

    sort(Ranges.begin(), Ranges.end());

    vector<uint64_t> d(M, 0);
    d[0] = 1;
    for (size_t i = 0; i < N; ++i)
    {
        auto [r, l] = Ranges[i];
        d[r - 1] = max(d[r - 1], l + 1);
    }

    uint64_t result = 2 - d[0];

    for (size_t i = 1; i < M; ++i)
    {
        d[i] = max(d[i], d[i - 1]);
        result += i - d[i] + 2;
    }

    cout << result << endl;

    return 0;
}