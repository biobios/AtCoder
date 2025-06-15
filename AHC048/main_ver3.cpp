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

using color = tuple<double, double, double>;

color mix(const color& c1, const color& c2, double ratio)
{
    auto [c1_c, c1_m, c1_y] = c1;
    auto [c2_c, c2_m, c2_y] = c2;
    return make_tuple(c1_c * ratio + c2_c * (1 - ratio),
                      c1_m * ratio + c2_m * (1 - ratio),
                      c1_y * ratio + c2_y * (1 - ratio));
}

size_t find_closest_color(const color& target, const vector<color>& colors)
{
    double min_error = numeric_limits<double>::max();
    size_t min_index = 0;
    for (size_t i = 0; i < colors.size(); ++i)
    {
        double error = calc_error(target, colors[i]);
        if (error < min_error)
        {
            min_error = error;
            min_index = i;
        }
    }
    return min_index;
}

struct operation
{
    uint64_t type, i, j, k, l;
    
    operation(uint64_t type, uint64_t i, uint64_t j, uint64_t k = 0, uint64_t l = 0)
        : type(type), i(i), j(j), k(k), l(l) {}
    
    void print() const
    {
        if (type == 1)
        {
            cout << "1 " << i << " " << j << " " << k << endl;
        }else if(type == 2)
        {
            cout << "2 " << i << " " << j << endl;
        }else if(type == 3)
        {
            cout << "3 " << i << " " << j << endl;
        }else if(type == 4)
        {
            cout << "4 " << i << " " << j << " " << k << " " << l << endl;
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
            cout << "1 ";
        }
        
        cout << endl;
    }
    
    for (size_t i = 0; i < N - 1; ++i)
    {
        for (size_t j = 0; j < N; ++j)
        {
            cout << "0 ";
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
        
        size_t sell_pos_x = 0;
        size_t sell_pos_y = cluster_i;
        
        uint64_t color_amount = 0;
        color current_color;
        size_t color_needs = color_indices.size();
        
        size_t rest_available_ope_count = (T * color_indices.size()) / H;
        
        for (size_t i = 0; i < color_needs; ++i)
        {
            size_t rest_color_needs = color_needs - i;
            size_t rest_available_ope_count_per_color = rest_available_ope_count / rest_color_needs;
            rest_available_ope_count -= rest_available_ope_count_per_color;
            const color& target_color = target_colors[color_indices[i]];
            
            // 色が空なら新しい色を追加
            if (color_amount == 0)
            {
                size_t min_index = find_closest_color(target_color, own_colors);
                current_color = own_colors[min_index];
                color_amount = 1;
                rest_available_ope_count_per_color--;
                operations[cluster_i].emplace_back(1, sell_pos_x, sell_pos_y, min_index);
            }
            
            vector<tuple<color, double, uint64_t>> splitted_colors;
            splitted_colors.emplace_back(current_color, color_amount, 20);

            vector<operation> cleanup_operations;
            
            while (true)
            {
                auto& [local_current_color, local_color_amount, current_space_size] = splitted_colors.back();
                // 選択肢をすべて列挙してコストが最少の物を選ぶ
                // 1. 現在の色を使う use 0 ope
                // 2. 壁を追加せずに次の色を作る use 1 ope
                // 3. 壁を追加して次の色を作る use 3 ope
                double cost1 = 0;
                for (size_t j = 0; j < local_color_amount; ++j)
                {
                    if (i + j >= color_needs) {
                        cost1 += D;
                        continue;
                    }
                    cost1 += calc_error(local_current_color, target_colors[color_indices[i + j]]) * 10000.0;
                }
                if (i + local_color_amount < color_needs) {
                    size_t closest_color = find_closest_color(target_colors[color_indices[i + local_color_amount]], own_colors);
                    cost1 += calc_error(own_colors[closest_color], target_colors[color_indices[i + local_color_amount]]) * 10000.0;
                }

                double cost2 = numeric_limits<double>::max();
                size_t add_color_index_without_wall = 0;
                // 空き容量が1以上なら次の色を作る
                if (current_space_size - local_color_amount >= 1.0 && rest_available_ope_count_per_color > 1)
                {
                    vector<color> next_colors;
                    for (size_t j = 0; j < K; ++j)
                    {
                        next_colors.push_back(mix(local_current_color, own_colors[j], local_color_amount / (local_color_amount + 1.0)));
                    }
                    
                    add_color_index_without_wall = find_closest_color(target_color, next_colors);
                    cost2 = D;
                    for (size_t j = 0; j < local_color_amount + 1; ++j)
                    {
                        if (i + j >= color_needs) {
                            cost2 += D;
                            continue;
                        }
                        cost2 += calc_error(next_colors[add_color_index_without_wall], target_colors[color_indices[i + j]]) * 10000.0;
                    }
                }
                
                double cost3 = numeric_limits<double>::max();
                size_t add_color_index_with_wall = 0;
                size_t splited_space_size = 0;

                double addable_color_amount = current_space_size - local_color_amount;
                size_t splitable_min_wall = ceil(current_space_size / addable_color_amount);
                if (addable_color_amount >= 1.0 && rest_available_ope_count_per_color > 3)
                    for (size_t j = splitable_min_wall; j < current_space_size; ++j)
                    {
                        vector<color> next_colors;
                        double use_amount = local_color_amount * j / current_space_size;
                        double ratio = use_amount / (use_amount + 1.0);
                        for (size_t k = 0; k < K; ++k)
                        {
                            next_colors.push_back(mix(local_current_color, own_colors[k], ratio));
                        }

                        size_t min_next_color_index = find_closest_color(target_color, next_colors);
                        double next_color_cost = D;
                        for (size_t k = 0; k < local_color_amount + 1; ++k)
                        {
                            if (i + k >= color_needs) {
                                next_color_cost += D;
                                continue;
                            }
                            
                            if (k < use_amount + 1.0)
                            {
                                next_color_cost += calc_error(next_colors[min_next_color_index], target_colors[color_indices[i + k]]) * 10000.0;
                            }
                        }

                        if (next_color_cost <= cost3)
                        {
                            cost3 = next_color_cost;
                            add_color_index_with_wall = min_next_color_index;
                            splited_space_size = j;
                        }
                    }
                
                if (cost1 <= cost2 && cost1 <= cost3) {
                    operations[cluster_i].emplace_back(2, sell_pos_x, sell_pos_y);
                    local_color_amount -= 1.0;
                    color_amount -= 1;
                    rest_available_ope_count_per_color--;
                    break;
                }
                
                if (cost2 <= cost3)
                {
                    operations[cluster_i].emplace_back(1, sell_pos_x, sell_pos_y, add_color_index_without_wall);
                    local_current_color = mix(local_current_color, own_colors[add_color_index_without_wall], local_color_amount / (local_color_amount + 1.0));
                    rest_available_ope_count_per_color--;
                    local_color_amount += 1.0;
                    color_amount += 1;
                }else{
                    double use_amount = local_color_amount * splited_space_size / current_space_size;
                    double ratio = use_amount / (use_amount + 1.0);
                    operations[cluster_i].emplace_back(4, sell_pos_x + splited_space_size - 1, sell_pos_y, sell_pos_x + splited_space_size, sell_pos_y);
                    operations[cluster_i].emplace_back(1, sell_pos_x, sell_pos_y, add_color_index_with_wall);
                    cleanup_operations.emplace_back(4, sell_pos_x + splited_space_size - 1, sell_pos_y, sell_pos_x + splited_space_size, sell_pos_y);
                    tuple<color, double, uint64_t> new_color = make_tuple(mix(local_current_color, own_colors[add_color_index_with_wall], ratio), use_amount + 1.0, splited_space_size);
                    local_color_amount = local_color_amount * (current_space_size - splited_space_size) / current_space_size;
                    current_space_size -= splited_space_size;
                    splitted_colors.push_back(new_color);
                    rest_available_ope_count_per_color -= 3;
                    color_amount += 1;
                }
            }

            // 最後の色をまとめる       
            rest_available_ope_count += rest_available_ope_count_per_color;
            double current_color_amount = get<1>(splitted_colors.front());
            current_color = get<0>(splitted_colors.front());
            for (size_t j = 1; j < splitted_colors.size(); ++j)
            {
                auto& [next_color, next_color_amount, next_space_size] = splitted_colors[j];
                current_color_amount += next_color_amount;
                current_color = mix(next_color, current_color, next_color_amount / current_color_amount);
            }

            // クリーンアップ操作を追加
            for (const auto& ope : cleanup_operations)
            {
                operations[cluster_i].push_back(ope);
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