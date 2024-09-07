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

    vector<vector<uint64_t>> A(N, vector<uint64_t>(N));

    for (size_t i = 0; i < N; ++i)
    {
        for (size_t j = 0; j <= i; ++j)
        {
            cin >> A[i][j];
            A[j][i] = A[i][j];
        }
    }

    uint64_t current = 1;

    for (size_t i = 0; i < N; ++i)
    {
        current = A[current - 1][i];
    }

    cout << current << endl;

    return 0;
}