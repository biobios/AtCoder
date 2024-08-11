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

    vector<map<uint64_t, uint64_t>> A(16);

    for (size_t i = 1; i <= 16; ++i)
    {
        // iを素因数分解する
        uint64_t n = i;
        for (uint64_t j = 2; j * j <= i; ++j)
        {
            while (n % j == 0)
            {
                A[i - 1][j]++;
                n /= j;
            }
        }
        if (n != 1)
        {
            A[i - 1][n]++;
        }
    }

    vector<uint64_t> dp(M, 0);
}