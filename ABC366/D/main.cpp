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
    uint64_t N;
    cin >> N;

    vector<vector<vector<uint64_t>>> grid(N, vector<vector<uint64_t>>(N, vector<uint64_t>(N)));

    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            for (size_t k = 0; k < N; k++)
            {
                cin >> grid[i][j][k];
            }
        }
    }

    vector<vector<vector<uint64_t>>> sum_grid(N + 1, vector<vector<uint64_t>>(N + 1, vector<uint64_t>(N + 1)));

    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            for (size_t k = 0; k < N; k++)
            {
                sum_grid[i + 1][j + 1][k + 1] = grid[i][j][k] + sum_grid[i + 1][j + 1][k];
            }
        }
    }

    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            for (size_t k = 0; k < N; k++)
            {
                sum_grid[i + 1][j + 1][k + 1] += sum_grid[i + 1][j][k + 1];
            }
        }
    }

    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            for (size_t k = 0; k < N; k++)
            {
                sum_grid[i + 1][j + 1][k + 1] += sum_grid[i][j + 1][k + 1];
            }
        }
    }

    // debug
    // cout << sum_grid.back().back().back() << endl;

    // cout << sum_grid[1][2][2] << endl;

    uint64_t Q;
    cin >> Q;

    for (size_t i = 0; i < Q; i++)
    {
        uint64_t x1, x2, y1, y2, z1, z2;
        cin >> x1 >> x2 >> y1 >> y2 >> z1 >> z2;

        x1--;
        y1--;
        z1--;

        cout << sum_grid[x2][y2][z2] - sum_grid[x1][y2][z2] - sum_grid[x2][y1][z2] - sum_grid[x2][y2][z1] + sum_grid[x1][y1][z2] + sum_grid[x1][y2][z1] + sum_grid[x2][y1][z1] - sum_grid[x1][y1][z1] << endl;
    }

    return 0;
}