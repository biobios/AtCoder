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

    for (auto s : S)
    {
        if (s == '.')
            continue;

        cout << s;
    }

    cout << endl;

    return 0;
}