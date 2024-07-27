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
    uint64_t H, W;
    cin >> H >> W;
    uint64_t I, J;
    cin >> I >> J;
    I--;
    J--;
    vector<vector<char>> C(H, vector<char>(W));
    for (size_t i = 0; i < H; i++)
    {
        for (size_t j = 0; j < W; j++)
        {
            cin >> C[i][j];
        }
    }
    string X;
    cin >> X;
    for (size_t i = 0; i < X.size(); i++)
    {
        if (X[i] == 'U')
        {
            if (I > 0 && C[I - 1][J] != '#')
            {
                I--;
            }
        }
        else if (X[i] == 'D')
        {
            if (I < H - 1 && C[I + 1][J] != '#')
            {
                I++;
            }
        }
        else if (X[i] == 'L')
        {
            if (J > 0 && C[I][J - 1] != '#')
            {
                J--;
            }
        }
        else if (X[i] == 'R')
        {
            if (J < W - 1 && C[I][J + 1] != '#')
            {
                J++;
            }
        }
    }

    cout << I + 1 << " " << J + 1 << endl;

    return 0;
}