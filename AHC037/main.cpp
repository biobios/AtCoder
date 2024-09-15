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

// GRID_SIZE    SCORE       V2SCORE
// 60           13864292
// 45           15303632
// 37           15994790
// 34           16194948    17065573
// 30           15963275    17323937
// 22           14853791    17647487
// 15           12273199    17924557
// 10                       18317305
// 5                        19439461
// 4                        19287414
// 3                        19791916
// 2                        21179792
// 1                        22803065

int main()
{
    uint64_t N;
    cin >> N;

    vector<pair<uint64_t, uint64_t>> points(N);

    for (uint64_t i = 0; i < N; i++)
    {
        cin >> points[i].first >> points[i].second;
    }

    constexpr uint64_t GRID_SIZE = 1;

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

    for (auto &&column : grid)
    {
        for (auto &&points : column)
        {

            if (points.empty())
                continue;

            set<pair<uint64_t, uint64_t>> point_set(points.begin(), points.end());

            auto [x, y] = *point_set.begin();
            point_set.erase(point_set.begin());

            vector<tuple<uint64_t, uint64_t, uint64_t, uint64_t>> sub_opes;

            while (true)
            {
                uint64_t min_cost = -1ull;
                size_t min_i = -1ull;

                for (size_t i = 0; i < points.size(); ++i)
                {
                    auto [c, r] = points[i];
                    if (c == x && r == y)
                        continue;
                    if (c > x || r > y)
                        continue;

                    uint64_t cost = x - c + y - r;
                    if (cost < min_cost)
                    {
                        min_cost = cost;
                        min_i = i;
                    }
                }

                if (min_i == -1ull)
                {
                    sub_opes.push_back({x * GRID_SIZE / 1000000000 * 1000000000 / GRID_SIZE, y * GRID_SIZE / 1000000000 * 1000000000 / GRID_SIZE, x, y});
                    // opesにsub_opesを逆順に追加
                    for (auto it = sub_opes.rbegin(); it != sub_opes.rend(); ++it)
                    {
                        opes.push_back(*it);
                    }
                    sub_opes.clear();

                    if (point_set.empty())
                        break;

                    x = point_set.begin()->first;
                    y = point_set.begin()->second;
                    point_set.erase(point_set.begin());
                }
                else
                {
                    auto [c, r] = points[min_i];
                    sub_opes.push_back({c, r, x, y});

                    x = c;
                    y = r;
                    auto it = point_set.find({c, r});
                    if (it != point_set.end())
                        point_set.erase(it);
                    else
                    {
                        // opesにsub_opesを逆順に追加
                        for (auto it = sub_opes.rbegin(); it != sub_opes.rend(); ++it)
                        {
                            opes.push_back(*it);
                        }
                        sub_opes.clear();

                        if (point_set.empty())
                            break;
                        x = point_set.begin()->first;
                        y = point_set.begin()->second;

                        point_set.erase(point_set.begin());
                    }
                }
            }

            // for (auto [x, y] : points)
            // {
            //     opes.push_back({x * GRID_SIZE / 1000000000 * 1000000000 / GRID_SIZE, y * GRID_SIZE / 1000000000 * 1000000000 / GRID_SIZE, x, y});
            // }
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