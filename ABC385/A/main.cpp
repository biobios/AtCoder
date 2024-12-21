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
    uint64_t a, b, c;

    cin >> a >> b >> c;

    if (a == b && b == c)
    {
        cout << "Yes" << endl;
    }
    else if (a + b == c || b + c == a || c + a == b)
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }

    return 0;
}