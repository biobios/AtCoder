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
#include <cstdint>

using namespace std;

double calc_error(const tuple<double, double, double>& made_color, const tuple<double, double, double>& target_color)
{
    auto [c1, m1, y1] = made_color;
    auto [c2, m2, y2] = target_color;
    return sqrt(pow(c1 - c2, 2) + pow(m1 - m2, 2) + pow(y1 - y2, 2));
}

struct operation
{
    uint64_t type, i, j, k;
    
    operation(uint64_t type, uint64_t i, uint64_t j, uint64_t k = 0)
        : type(type), i(i), j(j), k(k) {}
    
    void print() const
    {
        if (type == 1)
        {
            cout << "1 " << i << " " << j << " " << k << endl;
        }else if(type == 2)
        {
            cout << "2 " << i << " " << j << endl;
        }
    }
};

int main()
{
    uint64_t N, K, H, T, D;
    cin >> N >> K >> H >> T >> D;
    using color = tuple<double, double, double>;
    vector<color> own_colors(K);
    for (size_t i = 0; i < K; ++i)
    {
        double c, m, y;
        cin >> c >> m >> y;
        own_colors[i] = make_tuple(c, m, y);
    }
    
    vector<color> target_colors(H);
    for (size_t i = 0; i < H; ++i)
    {
        double c, m, y;
        cin >> c >> m >> y;
        target_colors[i] = make_tuple(c, m, y);
    }
    
    // target_colorsをk-means法でクラスタリング
    constexpr size_t ITERATION = 100;
    constexpr size_t CLUSTER_SIZE = 16;
    vector<vector<color>> clusters(CLUSTER_SIZE);

    // target_colorsをランダムにクラスタに分割
    for (size_t i = 0; i < H; ++i)
    {
        size_t cluster_index = i % CLUSTER_SIZE;
        clusters[cluster_index].push_back(target_colors[i]);
    }
    
    for (size_t iter = 0; iter < ITERATION; ++iter)
    {
        // 新しいクラスタ中心を計算
        vector<color> cluster_centers(CLUSTER_SIZE, make_tuple(0.0, 0.0, 0.0));
        for (size_t i = 0; i < CLUSTER_SIZE; ++i)
        {
            if (clusters[i].empty())
                continue;

            double sum_c = 0, sum_m = 0, sum_y = 0;
            for (const auto& [c, m, y] : clusters[i])
            {
                sum_c += c;
                sum_m += m;
                sum_y += y;
            }
            size_t size = clusters[i].size();
            cluster_centers[i] = make_tuple(sum_c / size, sum_m / size, sum_y / size);
        }

        
        for (size_t i = 0; i < CLUSTER_SIZE; ++i)
            clusters[i].clear(); // クラスタをクリア

        // 各target_colorを最も近いクラスタ中心に割り当てる
        for (const auto& [c, m, y] : target_colors)
        {
            double min_dist = numeric_limits<double>::max();
            size_t min_index = 0;
            for (size_t i = 0; i < CLUSTER_SIZE; ++i)
            {
                auto [cc, cm, cy] = cluster_centers[i];
                double dist = sqrt(pow(c - cc, 2) + pow(m - cm, 2) + pow(y - cy, 2));
                if (dist < min_dist)
                {
                    min_dist = dist;
                    min_index = i;
                }
            }
            clusters[min_index].push_back(make_tuple(c, m, y));
        }

    }

    // パレットの形状を出力
    for (size_t j = 0; j < N; ++j) {
        for (size_t i = 0; i < N - 1; ++i)
        {
            if ((i + 1) % 5 == 0)
            {
                cout << "1 ";
            }else
            {
                cout << "0 ";
            }
        }
        
        cout << endl;
    }
    
    for (size_t i = 0; i < N - 1; ++i)
    {
        for (size_t j = 0; j < N; ++j)
        {
            if ((i + 1) % 5 == 0)
            {
                cout << "1 ";
            }else
            {
                cout << "0 ";
            }
        }
        
        cout << endl;
    }
    
    vector<color> clusters_centers;
    for (const auto& cluster : clusters)
    {
        if (!cluster.empty())
        {
            double sum_c = 0, sum_m = 0, sum_y = 0;
            for (const auto& [c, m, y] : cluster)
            {
                sum_c += c;
                sum_m += m;
                sum_y += y;
            }
            size_t size = cluster.size();
            clusters_centers.push_back(make_tuple(sum_c / size, sum_m / size, sum_y / size));
        }
    }
    
    vector<vector<size_t>> color_indices_of_clusters(CLUSTER_SIZE);
    vector<size_t> cluster_indices_of_colors(H, 0);
    
    for (size_t i = 0; i < H; ++i)
    {
        double min_error = numeric_limits<double>::max();
        size_t min_index = 0;
        for (size_t j = 0; j < clusters_centers.size(); ++j)
        {
            double error = calc_error(target_colors[i], clusters_centers[j]);
            if (error < min_error)
            {
                min_error = error;
                min_index = j;
            }
        }
        color_indices_of_clusters[min_index].push_back(i);
        cluster_indices_of_colors[i] = min_index;
    }
    
    vector<vector<operation>> operations(CLUSTER_SIZE);
    for (size_t cluster_i = 0; cluster_i < CLUSTER_SIZE; ++cluster_i)
    {
        auto& color_indices = color_indices_of_clusters[cluster_i];
        if (color_indices.empty())
            continue;      

        size_t sell_pos_x = (cluster_i / 4) * 5;
        size_t sell_pos_y = (cluster_i % 4) * 5;
        
        uint64_t color_amount = 0;
        color current_color;
        size_t current_index = 0;
        size_t color_needs = color_indices.size();
        while (current_index < color_needs)
        {
            if (color_amount >= 25)
            {
                operations[cluster_i].emplace_back(2, sell_pos_x, sell_pos_y);
                color_amount--;
                current_index++;
                continue;
            }

            auto& target_color = target_colors[color_indices[current_index]];

            // 次の色を探す
            double min_error = numeric_limits<double>::max();
            size_t min_index = 0;
            for (size_t i = 0; i < K; ++i)
            {
                color maybe_next_color = current_color;
                auto& [c, m, y] = maybe_next_color;
                c *= color_amount;
                m *= color_amount;
                y *= color_amount;
                c += get<0>(own_colors[i]);
                m += get<1>(own_colors[i]);
                y += get<2>(own_colors[i]);
                c /= (color_amount + 1);
                m /= (color_amount + 1);
                y /= (color_amount + 1);
                double error = calc_error(maybe_next_color, target_color);
                if (error < min_error)
                {
                    min_error = error;
                    min_index = i;
                }
            }
            
            color next_color = current_color;
            auto& [c, m, y] = next_color;
            c *= color_amount;
            m *= color_amount;
            y *= color_amount;
            c += get<0>(own_colors[min_index]);
            m += get<1>(own_colors[min_index]);
            y += get<2>(own_colors[min_index]);
            c /= (color_amount + 1);
            m /= (color_amount + 1);
            y /= (color_amount + 1);
            
            if (color_amount == 0)
            {
                operations[cluster_i].emplace_back(1, sell_pos_x, sell_pos_y, min_index);
                current_color = next_color;
                color_amount++;
                continue;
            }
            
            double cost1 = 0;
            double cost2 = 0;
            for (size_t i = 0; i < color_amount; ++i)
            {
                if (current_index + i >= color_needs) {
                    cost1 += D;
                    continue;
                }
                
                cost1 += calc_error(current_color, target_colors[color_indices[current_index + i]]);
                cost2 += calc_error(next_color, target_colors[color_indices[current_index + i]]);
            }
            
            if (current_index + color_amount >= color_needs) {
                cost1 += D;
            }else {
                const auto& color_used_new_color = target_colors[color_indices[current_index + color_amount]];
                // 最も近い色を探す
                double min_error = numeric_limits<double>::max();
                for (size_t i = 0; i < K; ++i)
                {
                    double error = calc_error(own_colors[i], color_used_new_color);
                    if (error < min_error)
                    {
                        min_error = error;
                    }
                }
                
                cost1 += min_error;
            }
            
            if (current_index + color_amount + 1 >= color_needs) {
                cost2 += D;
            }else {
                cost2 += calc_error(next_color, target_colors[color_indices[current_index + color_amount + 1]]);
            }
            
            // 現在の色と次の色のコストを比較
            if (cost1 < cost2)
            {
                operations[cluster_i].emplace_back(2, sell_pos_x, sell_pos_y);
                color_amount--;
                current_index++;
            }else
            {
                operations[cluster_i].emplace_back(1, sell_pos_x, sell_pos_y, min_index);
                current_color = next_color;
                color_amount++;
            }
        }
    }
    
    vector<size_t> operation_counts(CLUSTER_SIZE, 0);
    for (size_t i = 0; i < H; ++i)
    {
        size_t cluster_index = cluster_indices_of_colors[i];
        auto& opes = operations[cluster_index];
        auto& ope_i = operation_counts[cluster_index];
        while (ope_i < opes.size())
        {
            opes[ope_i].print();
            ope_i++;
            if (opes[ope_i - 1].type == 2)
                break;
        }
    }
    
}