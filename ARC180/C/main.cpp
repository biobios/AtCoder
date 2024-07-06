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

using namespace std;

int main()
{
    uint64_t N;
    cin >> N;

    vector<int64_t> A(N);
    for (size_t i = 0; i < N; i++)
    {
        cin >> A[i];
    }

    uint64_t result = 0;

    vector<vector<uint64_t>> dp(N + 1, vector<uint64_t>(2001, 0));

    dp[0][1000] = 1;

    for (size_t i = 0; i < N; i++)
    {
        for (size_t v = 0; v < 2001; v++)
        {
            if (dp[i][v] == 0)
                continue;
            if (v == 1000)
            {
                for (size_t j = i; j < N; j++)
                {
                    for (size_t l = 990; l <= 1010; l++)
                    {
                        if (l == 1000)
                            continue;
                        for (size_t k = i; k < j; k++)
                        {
                            if (A[k] + 1000 == l)
                            {
                                dp[j + 1][l + A[j]] += dp[i][v];
                                dp[j + 1][l + A[j]] %= 1000000007;
                                break;
                            }
                        }
                    }
                }
            }
            else
            {
                for (size_t j = i; j < N; j++)
                {
                    dp[j + 1][v + A[j]] += dp[i][v];
                    dp[j + 1][v + A[j]] %= 1000000007;
                }
            }
        }
    }

    for (size_t i = 0; i < N + 1; i++)
    {
        for (size_t j = 0; j < 2001; j++)
        {
            result += dp[i][j] % 1000000007;
            result %= 1000000007;
        }
    }

    cout << result << endl;

    return 0;
}