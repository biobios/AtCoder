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
    string S, T;
    cin >> S >> T;

    for (size_t i = 1; i < S.size(); i++)
    {
        for (size_t j = 1; j <= i; j++)
        {
            string U;
            for (size_t k = j - 1; k < S.size(); k += i)
            {
                U += S[k];
            }

            if (U == T)
            {
                cout << "Yes" << endl;
                return 0;
            }
        }
    }

    cout << "No" << endl;

    return 0;
}