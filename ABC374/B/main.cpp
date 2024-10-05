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
    string S;
    cin >> S;

    string T;
    cin >> T;

    size_t i = 0;
    while (i < S.size() && i < T.size())
    {
        if (S[i] != T[i])
        {
            cout << i + 1 << endl;
            return 0;
        }

        i++;
    }

    if (S.size() != T.size())
    {
        cout << min(S.size(), T.size()) + 1 << endl;
    }
    else
    {
        cout << 0 << endl;
    }

    return 0;
}