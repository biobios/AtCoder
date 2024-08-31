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
    int64_t A, B;
    cin >> A >> B;

    if (A == B)
    {
        cout << "1" << endl;
    }
    else if ((A + B) % 2 == 0)
    {
        cout << "3" << endl;
    }
    else
    {
        cout << "2" << endl;
    }

    return 0;
}