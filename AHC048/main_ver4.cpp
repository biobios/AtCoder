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
        
        size_t color_needs = color_indices.size();
        
        size_t rest_available_ope_count = (T * color_indices.size()) / H;
        vector<tuple<color, double, uint64_t>> splitted_colors;
        splitted_colors.emplace_back(color{}, 0.0, 20);
        
        for (size_t i = 0; i < color_needs; ++i)
        {
            size_t rest_color_needs = color_needs - i;
            int64_t rest_available_ope_count_per_color = rest_available_ope_count / rest_color_needs;
            rest_available_ope_count -= rest_available_ope_count_per_color;
            const color& target_color = target_colors[color_indices[i]];

            while (true)
            {
                auto& [local_current_color, local_color_amount, current_space_size] = splitted_colors.back();
                bool usable_current_color = local_color_amount >= 1.0 - 1e-6;
                // 選択肢をすべて列挙してコストが最少の物を選ぶ
                // 1. 現在の色を使う use 0 ope
                // 2. 壁を追加せずに次の色を作る use 1 ope
                // 3. 壁を追加して次の色を作る use 2 ope
                // 4. 絵の具を消去して新しい色を作る use 2 ope
                // 5. 壁を無くして新しい色を作る use 1 ope
                double cost1 = numeric_limits<double>::max();
                if (usable_current_color){
                    cost1 = 0.0;
                    for (size_t j = 0; j < (size_t)local_color_amount; ++j)
                    {
                        if (i + j >= color_needs) {
                            continue;
                        }
                        cost1 += calc_error(local_current_color, target_colors[color_indices[i + j]]) * 10000.0;
                    }
                    if (i + (size_t)local_color_amount < color_needs) {
                        double rest_amount = local_color_amount - (uint64_t)local_color_amount;
                        double ratio = rest_amount / (rest_amount + 1.0);
                        vector<color> new_colors;
                        for (size_t j = 0; j < K; ++j)
                        {
                            new_colors.push_back(mix(local_current_color, own_colors[j], ratio));
                        }
                        // auto& second_last_splitted_color = *(splitted_colors.end() - 2);
                        // new_colors.push_back(mix(get<0>(second_last_splitted_color), local_current_color, get<1>(second_last_splitted_color) / (rest_amount + get<1>(second_last_splitted_color))));
                        size_t closest_color = find_closest_color(target_colors[color_indices[i + local_color_amount]], new_colors);
                        cost1 += calc_error(new_colors[closest_color], target_colors[color_indices[i + local_color_amount]]) * 10000.0;
                    }
                }

                double cost2 = numeric_limits<double>::max();
                size_t add_color_index_without_wall = 0;
                if (rest_available_ope_count_per_color > 1 || !usable_current_color)
                {
                    vector<color> next_colors;
                    double addable_amount = current_space_size - local_color_amount;
                    double add_amount = min(addable_amount, 1.0);
                    double ratio = local_color_amount / (local_color_amount + add_amount);
                    for (size_t j = 0; j < K; ++j)
                    {
                        next_colors.push_back(mix(local_current_color, own_colors[j], ratio));
                    }
                    
                    add_color_index_without_wall = find_closest_color(target_color, next_colors);
                    cost2 = D;
                    for (size_t j = 0; j < (size_t)(local_color_amount + add_amount); ++j)
                    {
                        if (i + j >= color_needs) {
                            continue;
                        }
                        cost2 += calc_error(next_colors[add_color_index_without_wall], target_colors[color_indices[i + j]]) * 10000.0;
                    }
                    if (((uint64_t)local_color_amount == (uint64_t)(local_color_amount + add_amount)) && i + (size_t)(local_color_amount) < color_needs) {
                        vector<color> new_colors;
                        double rest_amount = (local_color_amount + add_amount) - (uint64_t)(local_color_amount + add_amount);
                        double ratio = rest_amount / (rest_amount + 1.0);
                        for (size_t j = 0; j < K; ++j)
                        {
                            new_colors.push_back(mix(local_current_color, own_colors[j], ratio));
                        }
                        size_t closest_color = find_closest_color(target_colors[color_indices[i + local_color_amount]], new_colors);
                        cost2 += calc_error(own_colors[closest_color], target_colors[color_indices[i + local_color_amount]]) * 10000.0;
                    }
                }
                
                double cost3 = numeric_limits<double>::max();
                size_t add_color_index_with_wall = 0;
                size_t splited_space_size = 0;

                if (rest_available_ope_count_per_color > 2 || !usable_current_color)
                    for (size_t j = 1; j < current_space_size; ++j)
                    {
                        vector<color> next_colors;
                        double use_amount = local_color_amount * j / current_space_size;
                        double ratio = use_amount / min(use_amount + 1.0, (double)j);
                        for (size_t k = 0; k < K; ++k)
                        {
                            next_colors.push_back(mix(local_current_color, own_colors[k], ratio));
                        }

                        size_t min_next_color_index = find_closest_color(target_color, next_colors);
                        double next_color_cost = D;
                        double rest_amount = local_color_amount - use_amount;
                        for (size_t k = 0; k < (size_t)local_color_amount + 1; ++k)
                        {
                            if (i + k >= color_needs) {
                                continue;
                            }
                            
                            if (k < min((size_t)use_amount + 1, j))
                            {
                                next_color_cost += calc_error(next_colors[min_next_color_index], target_colors[color_indices[i + k]]) * 10000.0;
                            }else if(rest_amount >= 1.0){
                                next_color_cost += calc_error(local_current_color, target_colors[color_indices[i + k]]) * 10000.0;
                                rest_amount -= 1.0;
                            }else{
                                double ratio = rest_amount / (rest_amount + 1.0);
                                vector<color> new_colors;
                                for (size_t j = 0; j < K; ++j)
                                {
                                    new_colors.push_back(mix(local_current_color, own_colors[j], ratio));
                                }
                                // auto& second_last_splitted_color = *(splitted_colors.end() - 2);
                                // new_colors.push_back(mix(get<0>(second_last_splitted_color), local_current_color, get<1>(second_last_splitted_color) / (rest_amount + get<1>(second_last_splitted_color))));
                                size_t closest_color = find_closest_color(target_colors[color_indices[i + k]], new_colors);
                                next_color_cost += calc_error(new_colors[closest_color], target_colors[color_indices[i + k]]) * 10000.0;
                            }
                        }

                        if (next_color_cost <= cost3)
                        {
                            cost3 = next_color_cost;
                            add_color_index_with_wall = min_next_color_index;
                            splited_space_size = j;
                        }
                    }
                
                double cost4 = numeric_limits<double>::max();
                size_t add_color_index_with_delete = 0;
                if (rest_available_ope_count_per_color > 2 || !usable_current_color)
                {
                    double use_amount = max(0.0, local_color_amount - 1.0);
                    double ratio = use_amount / (use_amount + 1.0);
                    vector<color> new_colors;
                    for (size_t j = 0; j < K; ++j)
                    {
                        new_colors.push_back(mix(local_current_color, own_colors[j], ratio));
                    }
                    add_color_index_with_delete = find_closest_color(target_color, new_colors);
                    color& new_color = new_colors[add_color_index_with_delete];
                    cost4 = D;
                    for (size_t j = 0; j < (size_t)local_color_amount; ++j)
                    {
                        if (i + j >= color_needs) {
                            continue;
                        }
                        cost4 += calc_error(new_color, target_colors[color_indices[i + j]]) * 10000.0;
                    }
                    if (i + (size_t)local_color_amount < color_needs) {
                        vector<color> new_colors;
                        double rest_amount = local_color_amount - (uint64_t)local_color_amount;
                        double ratio = rest_amount / (rest_amount + 1.0);
                        for (size_t j = 0; j < K; ++j)
                        {
                            new_colors.push_back(mix(local_current_color, own_colors[j], ratio));
                        }
                        size_t closest_color = find_closest_color(target_colors[color_indices[i + local_color_amount]], new_colors);
                        cost4 += calc_error(own_colors[closest_color], target_colors[color_indices[i + local_color_amount]]) * 10000.0;
                    }
                }
                
                double cost5 = numeric_limits<double>::max();
                if (splitted_colors.size() >= 2 && (rest_available_ope_count_per_color > 1 || !usable_current_color))
                {
                    double ratio = local_color_amount / (local_color_amount + get<1>(*(splitted_colors.end() - 2)));
                    color new_color = mix(local_current_color, own_colors[add_color_index_without_wall], ratio);
                    cost5 = 0;
                    for (size_t j = 0; j < (size_t)local_color_amount; ++j)
                    {
                        if (i + j >= color_needs) {
                            continue;
                        }
                        cost5 += calc_error(new_color, target_colors[color_indices[i + j]]) * 10000.0;
                    }
                    if (i + (size_t)local_color_amount < color_needs) {
                        if (local_color_amount + get<1>(*(splitted_colors.end() - 2)) - (uint64_t)local_color_amount >= 1.0 - 1e-6)
                        {
                            cost5 += calc_error(new_color, target_colors[color_indices[i + local_color_amount]]) * 10000.0;
                        }else{
                            vector<color> new_colors;
                            double rest_amount = (local_color_amount + get<1>(*(splitted_colors.end() - 2))) - (uint64_t)local_color_amount;
                            double ratio = rest_amount / (rest_amount + 1.0);
                            for (size_t j = 0; j < K; ++j)
                            {
                                new_colors.push_back(mix(new_color, own_colors[j], ratio));
                            }
                            size_t closest_color = find_closest_color(target_colors[color_indices[i + local_color_amount]], new_colors);
                            cost5 += calc_error(own_colors[closest_color], target_colors[color_indices[i + local_color_amount]]) * 10000.0;
                        }
                    }
                }
                
                if (cost1 <= cost2 && cost1 <= cost3 && cost1 <= cost4 && cost1 <= cost5) {
                    operations[cluster_i].emplace_back(2, sell_pos_x, sell_pos_y);
                    local_color_amount -= 1.0;
                    rest_available_ope_count_per_color--;
                    break;
                }
                
                if (cost2 <= cost3 && cost2 <= cost4 && cost2 <= cost5)
                {
                    double ratio = local_color_amount / min(local_color_amount + 1.0, (double)current_space_size);
                    operations[cluster_i].emplace_back(1, sell_pos_x, sell_pos_y, add_color_index_without_wall);
                    local_current_color = mix(local_current_color, own_colors[add_color_index_without_wall], ratio);
                    rest_available_ope_count_per_color--;
                    local_color_amount = min(local_color_amount + 1.0, (double)current_space_size);
                }else if (cost3 <= cost4 && cost3 <= cost5)
                {
                    double use_amount = local_color_amount * splited_space_size / current_space_size;
                    double ratio = use_amount / min(use_amount + 1.0, (double)splited_space_size);
                    operations[cluster_i].emplace_back(4, sell_pos_x + splited_space_size - 1, sell_pos_y, sell_pos_x + splited_space_size, sell_pos_y);
                    operations[cluster_i].emplace_back(1, sell_pos_x, sell_pos_y, add_color_index_with_wall);
                    tuple<color, double, uint64_t> new_color = make_tuple(mix(local_current_color, own_colors[add_color_index_with_wall], ratio), min(use_amount + 1.0, (double)splited_space_size), splited_space_size);
                    local_color_amount = local_color_amount * (current_space_size - splited_space_size) / current_space_size;
                    current_space_size -= splited_space_size;
                    splitted_colors.push_back(new_color);
                    rest_available_ope_count_per_color -= 2;
                }else if (cost4 <= cost5)
                {
                    operations[cluster_i].emplace_back(3, sell_pos_x, sell_pos_y);
                    operations[cluster_i].emplace_back(1, sell_pos_x, sell_pos_y, add_color_index_with_delete);
                    double use_amount = max(0.0, local_color_amount - 1.0);
                    double ratio = use_amount / (use_amount + 1.0);
                    local_current_color = mix(local_current_color, own_colors[add_color_index_with_delete], ratio);
                    rest_available_ope_count_per_color -= 2;
                    local_color_amount = use_amount + 1.0;
                }else{
                    operations[cluster_i].emplace_back(4, sell_pos_x + current_space_size - 1, sell_pos_y, sell_pos_x + current_space_size, sell_pos_y);
                    auto& [merged_color, merged_color_amount, merged_space_size] = *(splitted_colors.end() - 2);
                    double ratio = local_color_amount / (local_color_amount + merged_color_amount);
                    tuple<color, double, uint64_t> new_color = make_tuple(mix(local_current_color, merged_color, ratio), local_color_amount + merged_color_amount, merged_space_size + current_space_size);
                    splitted_colors.pop_back();
                    splitted_colors.back() = new_color;
                    rest_available_ope_count_per_color -= 1;
                }
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