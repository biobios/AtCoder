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
    uint64_t L, R;
    cin >> L >> R;

    if (L + R == 2 || L + R == 0)
    {
        cout << "Invalid" << endl;
    }
    else if (L == 1)
    {
        cout << "Yes" << endl;
    }
    else if (R == 1)
    {
        cout << "No" << endl;
    }
    else
    {
        cout << "No" << endl;
    }

    return 0;
}