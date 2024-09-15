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

// K          SCORE
// 100        22814848
// 200        22821477

// K            V4SCORE
// 500          26458154
// 400          26676788
// 250          26519131
// 100          24130106
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

    // k-means法でクラスタリング
    constexpr size_t K = 400;
    constexpr size_t ITERATION = 100;

    vector<pair<uint64_t, uint64_t>> centers(K);
    // 初期の中心点は0~1000000000で一様に分布させる
    for (size_t i = 0; i < K; ++i)
    {
        centers[i] = points[i];
    }

    for (size_t iter = 0; iter < ITERATION; ++iter)
    {
        vector<vector<pair<uint64_t, uint64_t>>> clusters(K);
        for (auto [x, y] : points)
        {
            uint64_t min_dist = -1ull;
            size_t min_i = -1ull;
            for (size_t i = 0; i < K; ++i)
            {
                auto [cx, cy] = centers[i];
                uint64_t dist = abs((int64_t)(x - cx)) + abs((int64_t)(y - cy));
                if (dist < min_dist)
                {
                    min_dist = dist;
                    min_i = i;
                }
            }
            clusters[min_i].push_back({x, y});
        }

        for (size_t i = 0; i < K; ++i)
        {
            uint64_t sum_x = 0;
            uint64_t sum_y = 0;
            for (auto [x, y] : clusters[i])
            {
                sum_x += x;
                sum_y += y;
            }
            centers[i] = {sum_x / clusters[i].size(), sum_y / clusters[i].size()};
        }
    }

    // クラスタごとにx座標・y座標の最小値を求めて
    // pointsに追加

    vector<vector<pair<uint64_t, uint64_t>>> cluster_points(K);
    for (auto [x, y] : points)
    {
        uint64_t min_dist = -1ull;
        size_t min_i = -1ull;
        for (size_t i = 0; i < K; ++i)
        {
            auto [cx, cy] = centers[i];
            uint64_t dist = abs((int64_t)(x - cx)) + abs((int64_t)(y - cy));
            if (dist < min_dist)
            {
                min_dist = dist;
                min_i = i;
            }
        }
        cluster_points[min_i].push_back({x, y});
    }

    for (size_t i = 0; i < K; ++i)
    {

        if (cluster_points[i].empty())
            continue;

        auto min_x = cluster_points[i][0].first;
        size_t min_x_index = 0;
        auto min_y = cluster_points[i][0].second;
        size_t min_y_index = 0;

        for (size_t j = 1; j < cluster_points[i].size(); ++j)
        {
            auto [x, y] = cluster_points[i][j];
            if (min_x > x)
            {
                min_x = x;
                min_x_index = j;
            }
            if (min_y > y)
            {
                min_y = y;
                min_y_index = j;
            }
        }

        if (min_x_index != min_y_index)
            points.push_back({min_x, min_y});
    }

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