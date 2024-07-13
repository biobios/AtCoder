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
    uint64_t R, G, B;
    string C;
    cin >> R >> G >> B;
    cin >> C;

    uint64_t result = 0;
    if (C == "Red")
    {
        if (G > B)
        {
            result = B;
        }
        else
        {
            result = G;
        }
    }
    else if (C == "Green")
    {
        if (R > B)
        {
            result = B;
        }
        else
        {
            result = R;
        }
    }
    else
    {
        if (R > G)
        {
            result = G;
        }
        else
        {
            result = R;
        }
    }

    cout << result << endl;

    return 0;
}