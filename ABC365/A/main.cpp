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
    uint64_t Y;
    cin >> Y;

    if (Y % 4 == 0 && (Y % 100 != 0 || Y % 400 == 0))
    {
        cout << "366" << endl;
    }
    else
    {
        cout << "365" << endl;
    }

    return 0;
}