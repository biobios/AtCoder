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
    vector<vector<bool>> G(8, vector<bool>(8, false));

    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            char c;
            cin >> c;
            if (c == '#')
            {
                for (int k = 0; k < 8; ++k)
                {
                    G[i][k] = true;
                }
                for (int k = 0; k < 8; ++k)
                {
                    G[k][j] = true;
                }
            }
        }
    }

    uint64_t false_count = 0;

    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if (G[i][j] == false)
                false_count++;
        }
    }

    cout << false_count << endl;

    return 0;
}