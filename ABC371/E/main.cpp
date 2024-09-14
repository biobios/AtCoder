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
        A[i] -= 1;
    }

    vector<int64_t> prev_appeared_index(N, -1);
    uint64_t result = (N + 1) * N * N / 2;

    for (uint64_t i = 0; i < N; ++i)
    {
        int64_t diff = i - prev_appeared_index[A[i]];
        result -= diff * (diff - 1) / 2;
        prev_appeared_index[A[i]] = i;
    }

    for (auto i : prev_appeared_index)
    {
        auto diff = N - i;
        result -= diff * (diff - 1) / 2;
    }

    cout << result << endl;

    return 0;
}