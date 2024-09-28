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

    uint64_t count = 0;

    for (size_t i = 1; i <= 12; ++i)
    {
        string S;
        cin >> S;

        if (S.size() == i)
            count++;
    }

    cout << count << endl;

    return 0;
}