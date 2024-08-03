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
    string S;
    cin >> S;
    map<char, uint64_t> dp;
    for (size_t i = 0; i < N; i++)
    {
        char c = S[i];

        uint64_t R = dp['R'];
        uint64_t P = dp['P'];
        uint64_t S = dp['S'];

        if (c == 'R')
        {
            dp['R'] = max(P, S);
            dp['S'] = 0;
            dp['P'] = max(R, S) + 1;
        }
        else if (c == 'P')
        {
            dp['P'] = max(R, S);
            dp['S'] = max(R, P) + 1;
            dp['R'] = 0;
        }
        else if (c == 'S')
        {
            dp['S'] = max(R, P);
            dp['R'] = max(S, P) + 1;
            dp['P'] = 0;
        }
    }

    cout << max({dp['R'], dp['P'], dp['S']}) << endl;

    return 0;
}