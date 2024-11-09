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

    vector<uint64_t> X(M);
    vector<uint64_t> A(M);
    uint64_t sum = 0;

    for (uint64_t i = 0; i < M; i++)
    {
        cin >> X[i];
    }

    for (uint64_t i = 0; i < M; i++)
    {
        cin >> A[i];
        sum += A[i];
    }

    vector<pair<uint64_t, uint64_t>> XA(M);
    for (uint64_t i = 0; i < M; i++)
    {
        XA[i] = make_pair(X[i], A[i]);
    }

    sort(XA.rbegin(), XA.rend());

    if (sum != N)
    {
        cout << "-1" << endl;
        return 0;
    }

    int64_t not_filled = 0;
    uint64_t prev = N + 1;
    uint64_t result = 0;

    for (auto [x, a] : XA)
    {
        result += (prev - x) * not_filled;
        result += (prev - x - 1) * (prev - x) / 2;
        not_filled += prev - x - 1;
        not_filled -= a - 1;
        if (not_filled < 0)
        {
            cout << "-1" << endl;
            return 0;
        }
        prev = x;
    }

    cout << result << endl;

    return 0;
}