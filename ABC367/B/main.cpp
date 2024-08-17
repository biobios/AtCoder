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
    string X;
    cin >> X;

    string result = "";

    auto it = X.rbegin();

    for (; it != X.rend(); ++it)
    {
        if (*it == '.' && result.size() != 0)
        {
            result = '.' + result;
        }
        else if (*it != '0' && *it != '.')
        {
            result = *it + result;
        }
        else if (*it == '0' && result.size() != 0)
        {
            result = '0' + result;
        }

        if (*it == '.')
        {
            break;
        }
    }

    ++it;

    for (; it != X.rend(); ++it)
    {
        result = *it + result;
    }

    cout << result << endl;

    return 0;
}