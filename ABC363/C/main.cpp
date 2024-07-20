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
    uint64_t N, K;
    cin >> N >> K;
    string S;
    cin >> S;

    sort(S.begin(), S.end());
    uint64_t result = 0;

    do
    {
        bool contains = false;
        for (uint64_t i = 0; i + K <= N; i++)
        {
            bool _contains = true;
            for (uint64_t j = 0; j < K; j++)
            {
                if (S[i + j] != S[i + K - 1 - j])
                {
                    _contains = false;
                    break;
                }
            }

            if (_contains)
            {
                contains = true;
                break;
            }
        }
        if (!contains)
            result++;
    } while (next_permutation(S.begin(), S.end()));

    cout << result << endl;

    return 0;
}