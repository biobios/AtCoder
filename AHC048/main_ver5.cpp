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

double calc_error(const tuple<double, double, double> &made_color, const tuple<double, double, double> &target_color)
{
    auto [c1, m1, y1] = made_color;
    auto [c2, m2, y2] = target_color;
    return sqrt(pow(c1 - c2, 2) + pow(m1 - m2, 2) + pow(y1 - y2, 2));
}

using color = tuple<double, double, double>;

color mix(const color &c1, const color &c2, double ratio)
{
    auto [c1_c, c1_m, c1_y] = c1;
    auto [c2_c, c2_m, c2_y] = c2;
    return make_tuple(c1_c * ratio + c2_c * (1 - ratio),
                      c1_m * ratio + c2_m * (1 - ratio),
                      c1_y * ratio + c2_y * (1 - ratio));
}

size_t find_closest_color(const color &target, const vector<color> &colors)
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

class well
{
public:
    well(size_t x, size_t y, size_t size)
        : x(x), y(y), size(size)
    {
        splitted_areas.push_back(make_tuple(color{}, 0.0, size));
    }
    
    // 使用するのに十分な色の量があるかどうかを確認する
    bool has_enough_color() const
    {
        auto [current_color, amount, area_size] = splitted_areas.back();
        return amount >= 1.0 - 1e-6;
    }
    
    // 現在のインク量を取得する
    double get_current_amount() const
    {
        return get<1>(splitted_areas.back());
    }
    
    // 現在のエリアのサイズを取得する
    size_t get_area_size() const
    {
        return get<2>(splitted_areas.back());
    }

    // 2つ以上のエリアに分割されているかどうかを確認する
    bool is_split() const
    {
        return splitted_areas.size() > 1;
    }
    
    // 色を追加する
    void add_color(const color &c)
    {
        auto [current_color, amount, area_size] = splitted_areas.back();
        double ratio = amount / min(amount + 1.0, (double)area_size);
        color new_color = mix(current_color, c, ratio);
        splitted_areas.back() = make_tuple(new_color, min(amount + 1.0, (double)area_size), area_size);
    }
    
    // 現在の色を使用する
    color use_color()
    {
        auto& [current_color, amount, area_size] = splitted_areas.back();
        if (amount < 1.0 - 1e-6)
            throw runtime_error("Not enough color to use");
        
        amount = max(amount - 1.0, 0.0);
        return current_color;
    }
    
    // 色を取り除く
    void remove_color()
    {
        auto& [current_color, amount, area_size] = splitted_areas.back();
        amount = max(amount - 1.0, 0.0);
    }
    
    // 仮に色を追加した場合の新しい色を取得する
    color get_new_color(const color &c) const
    {
        auto [current_color, amount, area_size] = splitted_areas.back();
        double ratio = amount / min(amount + 1.0, (double)area_size);
        return mix(current_color, c, ratio);
    }
    
    // 仮に色を取り除いて色を追加した場合の新しい色を取得する
    color get_new_color_after_remove(const color &c) const
    {
        auto [current_color, amount, area_size] = splitted_areas.back();
        double use_amount = max(amount - 1.0, 0.0);
        double ratio = use_amount / min(use_amount + 1.0, (double)area_size);
        return mix(current_color, c, ratio);
    }

    // エリアを分割する
    void split_area(size_t new_size)
    {
        auto [current_color, amount, area_size] = splitted_areas.back();
        if (new_size >= area_size)
            return; // 分割できない場合は何もしない

        splitted_areas.pop_back();
        splitted_areas.push_back(make_tuple(current_color, amount * (area_size - new_size) / area_size, area_size - new_size));
        splitted_areas.push_back(make_tuple(current_color, amount * new_size / area_size, new_size));
    }

    // エリアをマージする
    void merge_area()
    {
        if (splitted_areas.size() < 2)
            return; // マージできるエリアがない場合は何もしない

        auto [color1, amount1, size1] = splitted_areas.back();
        splitted_areas.pop_back();
        auto [color2, amount2, size2] = splitted_areas.back();
        splitted_areas.pop_back();

        color new_color = mix(color1, color2, amount1 / (amount1 + amount2));
        double new_amount = amount1 + amount2;
        size_t new_size = size1 + size2;

        splitted_areas.push_back(make_tuple(new_color, new_amount, new_size));
    }

    // 仮にエリアを分割して色を追加した場合の新しい色を取得する
    color get_new_color_after_split(const color &c, size_t new_size) const
    {
        auto [current_color, amount, area_size] = splitted_areas.back();
        new_size = min(new_size, area_size); // 分割サイズがエリアサイズを超えないようにする

        double use_amount = amount * new_size / area_size;
        double ratio = use_amount / min(use_amount + 1.0, (double)new_size);
        color new_color = mix(current_color, c, ratio);
        return new_color;
    }

    // 仮に現在の色をすべて使った場合の色ごとのコストの平均を計算する
    double calculate_average_cost(double initial_cost,const vector<size_t>& color_indices, const vector<color> &target_colors, size_t begin_color_index) const
    {
        double total_cost = initial_cost;
        size_t color_count = 0;
        well copied_this = *this;
        
        for (size_t i = begin_color_index; i < color_indices.size(); ++i)
        {
            while (!copied_this.has_enough_color())
            {
                if (copied_this.is_split())
                {
                    copied_this.merge_area();
                }else
                {
                    // 計算終了
                    return total_cost / color_count;
                }
            }
            
            auto& target_color = target_colors[color_indices[i]];
            
            color used_color = copied_this.use_color();
            double error = calc_error(used_color, target_color);
            total_cost += error * 10000.0; // エラーをコストに変換
            color_count++;
        }
        
        return total_cost / color_count;
    }
    
private:
    size_t x, y, size;
    vector<tuple<color, double, size_t>> splitted_areas; // (color, amount, area size)
};

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
        }
        else if (type == 2)
        {
            cout << "2 " << i << " " << j << endl;
        }
        else if (type == 3)
        {
            cout << "3 " << i << " " << j << endl;
        }
        else if (type == 4)
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
            for (const auto &[c, m, y] : clusters[i])
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
        for (const auto &[c, m, y] : target_colors)
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
    for (size_t j = 0; j < N; ++j)
    {
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
    for (const auto &cluster : clusters)
    {
        if (!cluster.empty())
        {
            double sum_c = 0, sum_m = 0, sum_y = 0;
            for (const auto &[c, m, y] : cluster)
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
    double total_cost = 0.0;
    for (size_t cluster_i = 0; cluster_i < CLUSTER_SIZE; ++cluster_i)
    {
        auto &color_indices = color_indices_of_clusters[cluster_i];
        if (color_indices.empty())
            continue;

        size_t sell_pos_x = 0;
        size_t sell_pos_y = cluster_i;

        size_t color_needs = color_indices.size();

        size_t rest_available_ope_count = (T * color_indices.size()) / H;
        well current_well(sell_pos_x, sell_pos_y, 20);

        for (size_t i = 0; i < color_needs; ++i)
        {
            size_t rest_color_needs = color_needs - i;
            int64_t rest_available_ope_count_per_color = rest_available_ope_count / rest_color_needs;
            rest_available_ope_count -= rest_available_ope_count_per_color;

            while (true)
            {
                bool usable_current_color = current_well.has_enough_color();
                // 選択肢をすべて列挙してコストが最少の物を選ぶ
                // 1. 現在の色を使う use 0 ope
                // 2. 壁を追加せずに次の色を作る use 1 ope
                // 3. 壁を追加して次の色を作る use 2 ope
                // 4. 絵の具を消去して新しい色を作る use 2 ope
                // 5. 壁を無くして新しい色を作る use 1 ope
                // 6. 壁を無くして色を追加して新しい色を作る use 2 ope
                double cost1 = numeric_limits<double>::max();
                if (usable_current_color)
                {
                    cost1 = current_well.calculate_average_cost(0.0, color_indices, target_colors, i);
                }

                double cost2 = numeric_limits<double>::max();
                size_t add_color_index_without_wall = 0;
                if (rest_available_ope_count_per_color > 1 || !usable_current_color)
                {
                    for (size_t j = 0; j < K; ++j)
                    {
                        well well_for_simulation = current_well;
                        well_for_simulation.add_color(own_colors[j]);
                        double next_color_cost = well_for_simulation.calculate_average_cost(D, color_indices, target_colors, i);
                        
                        if (next_color_cost < cost2)
                        {
                            cost2 = next_color_cost;
                            add_color_index_without_wall = j;
                        }
                    }
                }

                double cost3 = numeric_limits<double>::max();
                size_t add_color_index_with_wall = 0;
                size_t splited_space_size = 0;
                
                size_t current_space_size = current_well.get_area_size();

                if (current_well.get_current_amount() >= 0.05 && (rest_available_ope_count_per_color > 2 || !usable_current_color))
                    for (size_t j = 1; j < current_space_size; ++j)
                    {
                        for (size_t k = 0; k < K; ++k)
                        {
                            well well_for_simulation = current_well;
                            well_for_simulation.split_area(j);
                            well_for_simulation.add_color(own_colors[k]);
                            double next_color_cost = well_for_simulation.calculate_average_cost(D, color_indices, target_colors, i);
                            
                            if (next_color_cost < cost3)
                            {
                                cost3 = next_color_cost;
                                add_color_index_with_wall = k;
                                splited_space_size = j;
                            }
                        }
                    }

                double cost4 = numeric_limits<double>::max();
                size_t add_color_index_with_delete = 0;
                if (rest_available_ope_count_per_color > 2 || !usable_current_color)
                {
                    for (size_t j = 0; j < K; ++j)
                    {
                        well well_for_simulation = current_well;
                        well_for_simulation.remove_color();
                        well_for_simulation.add_color(own_colors[j]);
                        double next_color_cost = well_for_simulation.calculate_average_cost(D, color_indices, target_colors, i);
                        
                        if (next_color_cost < cost4)
                        {
                            cost4 = next_color_cost;
                            add_color_index_with_delete = j;
                        }
                    }
                }

                double cost5 = numeric_limits<double>::max();
                size_t merge_count_min_cost = 0;
                if (current_well.is_split() && (rest_available_ope_count_per_color > 1 || !usable_current_color))
                {
                    well well_for_simulation = current_well;
                    size_t merge_count = 0;
                    while (well_for_simulation.is_split())
                    {
                        well_for_simulation.merge_area();
                        merge_count++;
                        double next_color_cost = well_for_simulation.calculate_average_cost(0, color_indices, target_colors, i);
                        if (next_color_cost < cost5)
                        {
                            cost5 = next_color_cost;
                            merge_count_min_cost = merge_count;
                        }
                    }
                }
                
                double cost6 = numeric_limits<double>::max();
                size_t merge_count_min_cost_with_add = 0;
                size_t add_color_index_without_wall_for_merge = 0;
                if (current_well.is_split() && (rest_available_ope_count_per_color > 2 || !usable_current_color))
                {
                    well well_for_simulation = current_well;
                    size_t merge_count = 0;
                    while (well_for_simulation.is_split())
                    {
                        well_for_simulation.merge_area();
                        merge_count++;
                        for (size_t j = 0; j < K; ++j)
                        {
                            well well_for_simulation_with_add = well_for_simulation;
                            well_for_simulation_with_add.add_color(own_colors[j]);
                            double next_color_cost = well_for_simulation_with_add.calculate_average_cost(D, color_indices, target_colors, i);
                            if (next_color_cost < cost6)
                            {
                                cost6 = next_color_cost;
                                merge_count_min_cost_with_add = merge_count;
                                add_color_index_without_wall_for_merge = j;
                            }
                        }
                    }
                }

                if (cost1 <= cost2 && cost1 <= cost3 && cost1 <= cost4 && cost1 <= cost5 && cost1 <= cost6)
                {
                    operations[cluster_i].emplace_back(2, sell_pos_x, sell_pos_y);
                    rest_available_ope_count_per_color--;
                    color used_color = current_well.use_color();
                    total_cost += calc_error(used_color, target_colors[color_indices[i]]) * 10000.0; // エラーをコストに変換
                    break;
                }

                if (cost2 <= cost3 && cost2 <= cost4 && cost2 <= cost5 && cost2 <= cost6)
                {
                    operations[cluster_i].emplace_back(1, sell_pos_x, sell_pos_y, add_color_index_without_wall);
                    rest_available_ope_count_per_color--;
                    current_well.add_color(own_colors[add_color_index_without_wall]);
                    total_cost += D;
                }
                else if (cost3 <= cost4 && cost3 <= cost5 && cost3 <= cost6)
                {
                    operations[cluster_i].emplace_back(4, sell_pos_x + splited_space_size - 1, sell_pos_y, sell_pos_x + splited_space_size, sell_pos_y);
                    operations[cluster_i].emplace_back(1, sell_pos_x, sell_pos_y, add_color_index_with_wall);
                    current_well.split_area(splited_space_size);
                    current_well.add_color(own_colors[add_color_index_with_wall]);
                    rest_available_ope_count_per_color -= 2;
                    total_cost += D;
                }
                else if (cost4 <= cost5 && cost4 <= cost6)
                {
                    operations[cluster_i].emplace_back(3, sell_pos_x, sell_pos_y);
                    operations[cluster_i].emplace_back(1, sell_pos_x, sell_pos_y, add_color_index_with_delete);
                    rest_available_ope_count_per_color -= 2;
                    current_well.remove_color();
                    current_well.add_color(own_colors[add_color_index_with_delete]);
                    total_cost += D;
                }
                else if (cost5 <= cost6)
                {
                    for (size_t j = 0; j < merge_count_min_cost; ++j)
                    {
                        size_t current_space_size = current_well.get_area_size();
                        operations[cluster_i].emplace_back(4, sell_pos_x + current_space_size - 1, sell_pos_y, sell_pos_x + current_space_size, sell_pos_y);
                        current_well.merge_area();
                        rest_available_ope_count_per_color--;
                    }
                }else
                {
                    for (size_t j = 0; j < merge_count_min_cost_with_add; ++j)
                    {
                        size_t current_space_size = current_well.get_area_size();
                        operations[cluster_i].emplace_back(4, sell_pos_x + current_space_size - 1, sell_pos_y, sell_pos_x + current_space_size, sell_pos_y);
                        current_well.merge_area();
                        rest_available_ope_count_per_color--;
                    }
                    
                    operations[cluster_i].emplace_back(1, sell_pos_x, sell_pos_y, add_color_index_without_wall_for_merge);
                    current_well.add_color(own_colors[add_color_index_without_wall_for_merge]);
                    total_cost += D;
                    rest_available_ope_count_per_color--;
                }
            }
        }
    }

    vector<size_t> operation_counts(CLUSTER_SIZE, 0);
    for (size_t i = 0; i < H; ++i)
    {
        size_t cluster_index = cluster_indices_of_colors[i];
        auto &opes = operations[cluster_index];
        auto &ope_i = operation_counts[cluster_index];
        while (ope_i < opes.size())
        {
            opes[ope_i].print();
            ope_i++;
            if (opes[ope_i - 1].type == 2)
                break;
        }
    }
    
    cout << "Total cost: " << total_cost << endl;
    return 0;
}