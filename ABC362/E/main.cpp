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

constexpr uint64_t MOD = 998244353;

int main()
{
    uint64_t N;
    cin >> N;

    vector<int64_t> A(N);
    for (size_t i = 0; i < N; ++i)
    {
        cin >> A[i];
    }

    vector<uint64_t> result(N, 0);
    result[0] = N;
    result[1] = N * (N - 1) / 2;
    if (N > 2)
        for (size_t i = 0; i < N - 2; i++)
        {
            for (size_t j = i + 1; j < N - 1; j++)
            {
                int64_t diff = A[j] - A[i];
                int64_t first_term = A[j];
                vector<uint64_t> dp(N, 0);
                dp[0] = 1;
                if (diff == 0)
                {
                    uint64_t count = 0;
                    for (size_t k = j + 1; k < N; k++)
                    {
                        if (A[k] == first_term)
                        {
                            count++;
                            for (int64_t l = count - 1; l >= 0; l--)
                            {
                                result[l + 1] += dp[l];
                                result[l + 1] %= MOD;
                                dp[l + 1] += dp[l];
                            }
                        }
                    }
                    continue;
                }
                for (size_t k = j + 1; k < N; k++)
                {
                    if (diff < 0 && (A[k] - first_term) > 0)
                        continue;
                    if (diff > 0 && (A[k] - first_term) < 0)
                        continue;
                    if ((A[k] - first_term) % diff != 0)
                        continue;

                    uint64_t index = (A[k] - first_term) / diff;
                    if (index <= 0 || index >= N)
                        continue;
                    result[index + 1] += dp[index - 1];
                    result[index + 1] %= MOD;
                    dp[index] += dp[index - 1];
                }
            }
        }

    for (size_t i = 0; i < N; i++)
    {
        cout << result[i] << " ";
    }

    cout << endl;
    return 0;
}