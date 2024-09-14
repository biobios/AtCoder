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
    char AB, AC, BC;
    cin >> AB >> AC >> BC;

    if (AB == BC)
    {
        cout << "B" << endl;
    }
    else if (AB != AC)
    {
        cout << "A" << endl;
    }
    else if (AC != BC)
    {
        cout << "C" << endl;
    }

    return 0;
}