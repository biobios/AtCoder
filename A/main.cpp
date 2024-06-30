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
    string S;
    cin >> S;
    for (char c : S)
    {
        if (c == 'R')
        {
            cout << "Yes" << endl;
            return 0;
        }
        if (c == 'M')
        {
            cout << "No" << endl;
            return 0;
        }
    }

    return 0;
}