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
    uint64_t N, K;
    cin >> N >> K;

    vector<size_t> X(N);
    vector<uint64_t> A(N);

    for (size_t i = 0; i < N; ++i)
    {
        cin >> X[i];
        X[i]--;
    }

    for (size_t i = 0; i < N; ++i)
    {
        cin >> A[i];
    }

    vector<vector<size_t>> doubling(60, vector<size_t>(N));

    for (size_t i = 0; i < N; ++i)
    {
        doubling[0][i] = X[i];
    }

    for (size_t i = 1; i < 60; ++i)
    {
        for (size_t j = 0; j < N; ++j)
        {
            doubling[i][j] = doubling[i - 1][doubling[i - 1][j]];
        }
    }

    vector<uint64_t> result(N, 0);

    for (size_t i = 0; i < N; ++i)
    {
        size_t now = i;
        uint64_t k = K;
        for (size_t j = 0; j < 60; ++j)
        {
            if (k & 1)
            {
                now = doubling[j][now];
            }
            k >>= 1;
        }

        result[i] = A[now];
    }

    for (size_t i = 0; i < N; ++i)
    {
        cout << result[i] << " ";
    }

    cout << endl;

    return 0;
}