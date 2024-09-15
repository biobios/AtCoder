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
#include <fstream>

using namespace std;

// GRID_SIZE    SCORE
// 60           13864292
// 45           15303632
// 37           15994790
// 34           16194948
// 30           15963275
// 22           14853791
// 15           12273199

int main()
{
    uint64_t N;
    cin >> N;

    vector<pair<uint64_t, uint64_t>> points(N);

    for (uint64_t i = 0; i < N; i++)
    {
        cin >> points[i].first >> points[i].second;
    }

    sort(points.begin(), points.end());

    constexpr uint64_t GRID_SIZE = 34;

    vector<vector<vector<pair<uint64_t, uint64_t>>>> grid(GRID_SIZE, vector<vector<pair<uint64_t, uint64_t>>>(GRID_SIZE));

    // 0~10^9の座標を0~59に変換
    for (auto [x, y] : points)
    {
        grid[x * GRID_SIZE / 1000000000][y * GRID_SIZE / 1000000000].push_back({x, y});
    }

    vector<tuple<uint64_t, uint64_t, uint64_t, uint64_t>> opes;

    for (size_t i = 1; i < GRID_SIZE; ++i)
    {
        opes.push_back({(i - 1) * 1000000000 / GRID_SIZE, 0, i * 1000000000 / GRID_SIZE, 0});
    }

    for (size_t i = 0; i < GRID_SIZE; ++i)
    {
        size_t j_end = GRID_SIZE - 1;
        while (j_end > 0 && grid[i][j_end].empty())
            --j_end;

        for (size_t j = 1; j <= j_end; ++j)
        {
            opes.push_back({i * 1000000000 / GRID_SIZE, (j - 1) * 1000000000 / GRID_SIZE, i * 1000000000 / GRID_SIZE, j * 1000000000 / GRID_SIZE});
        }
    }

    for (auto column : grid)
    {
        for (auto points : column)
        {
            for (auto [x, y] : points)
            {
                opes.push_back({x * GRID_SIZE / 1000000000 * 1000000000 / GRID_SIZE, y * GRID_SIZE / 1000000000 * 1000000000 / GRID_SIZE, x, y});
            }
        }
    }

    cout << opes.size() << endl;

    for (auto [x1, y1, x2, y2] : opes)
    {
        cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
    }

    // ファイル出力(デバッグ用)

    // ofstream outputfile("output.txt");

    // outputfile << opes.size() << endl;

    // for (auto [x1, y1, x2, y2] : opes)
    // {
    //     outputfile << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
    // }

    // outputfile.close();

    return 0;
}