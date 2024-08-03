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
    vector<uint64_t> A(N);
    for (size_t i = 0; i < N; ++i)
    {
        cin >> A[i];
    }

    uint64_t ans = 0;

    vector<uint64_t> cum_xor(N + 1);
    for (size_t i = 0; i < N; ++i)
    {
        cum_xor[i + 1] = cum_xor[i] ^ A[i];
    }

    array<array<uint64_t, 2>, 64> cnt = {};

    for (size_t i = 0; i < N - 1; ++i)
    {
        uint64_t x = cum_xor[i];
        for (size_t j = 0; j < 64; ++j)
        {
            cnt[j][x & 1]++;
            x >>= 1;
        }

        x = cum_xor[i + 2];
        for (size_t j = 0; j < 64; ++j)
        {
            ans += (x & 1) * (1ULL << j) * cnt[j][0];
            ans += ((x & 1) ^ 1) * (1ULL << j) * cnt[j][1];
            x >>= 1;
        }
    }

    cout << ans << endl;

    return 0;
}