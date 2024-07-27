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
    uint64_t N;
    cin >> N;

    bool prev_is_sweet = false;

    for (size_t i = 0; i < N - 1; i++)
    {
        string S;
        cin >> S;

        if (S == "sweet")
        {
            if (prev_is_sweet)
            {
                cout << "No" << endl;
                return 0;
            }
            prev_is_sweet = true;
        }
        else if (S == "salty")
        {
            prev_is_sweet = false;
        }
    }

    cout << "Yes" << endl;

    return 0;
}