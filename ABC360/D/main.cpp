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
#include <array>

using namespace std;

int main()
{
    uint64_t N, T;
    cin >> N >> T;

    string S;
    cin >> S;

    vector<array<int64_t, 3>> X(N);

    for (size_t i = 0; i < N; i++)
    {
        int64_t x;
        cin >> x;
        X[i] = {x, (int64_t)i, 0};
    }

    sort(X.begin(), X.end());
    for (size_t i = 0; i < N; i++)
    {
        X[i][2] = i;
        if (S[X[i][1]] == '0')
        {
            X[i][0] -= T;
            X[i][1] = 0;
        }
        else
        {
            X[i][0] += T;
            X[i][1] = 1;
        }
    }

    sort(X.begin(), X.end());
    uint64_t result = 0;
    for (size_t i = 0; i < N; i++)
    {
        if (X[i][2] > i)
        {
            result += X[i][2] - i;
        }
        else
        {
            result += i - X[i][2];
        }
    }

    result /= 2;

    cout << result << endl;

    return 0;
}