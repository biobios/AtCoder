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

    string S;
    cin >> S;

    uint64_t result = 1;
    char prev = S[0];
    uint64_t current_streak = 1;
    for (size_t i = 1; i < N; i++)
    {
        char c = S[i];

        if (c == prev)
        {
            if (current_streak >= 3)
            {
                result *= (current_streak + 1) / 2;
                result %= 1000000007;
            }
            current_streak = 1;
            continue;
        }

        prev = c;
        current_streak++;
    }

    if (current_streak >= 3)
    {
        result *= (current_streak + 1) / 2;
        result %= 1000000007;
    }

    cout << result << endl;

    return 0;
}