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
    string S, T;
    cin >> S >> T;

    vector<pair<size_t, char>> ope;

    for (size_t i = 0; i < S.size(); ++i)
    {
        if (S[i] > T[i])
        {
            ope.push_back({i, T[i]});
        }
    }

    for (size_t i = S.size(); i > 0; --i)
    {
        if (S[i - 1] < T[i - 1])
        {
            ope.push_back({i - 1, T[i - 1]});
        }
    }

    cout << ope.size() << endl;

    for (auto [i, c] : ope)
    {
        S[i] = c;
        cout << S << endl;
    }

    return 0;
}