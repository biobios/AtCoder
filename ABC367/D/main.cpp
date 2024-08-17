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

    vector<uint64_t> A(N);
    map<uint64_t, uint64_t> count;

    cin >> A[0];
    A[0] %= M;

    for (uint64_t i = 1; i < N; ++i)
    {
        cin >> A[i];
        A[i] = A[i] + A[i - 1];
        A[i] %= M;
    }

    uint64_t length = A.back();
    uint64_t result = 0;

    for (auto a : A)
    {
        result += count[a];
        count[a]++;
    }

    // 2周目
    for (auto a : A)
    {
        count[a]--;
        result += count[(a + length) % M];
    }

    cout << result << endl;

    return 0;
}