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

int main()
{
    uint64_t H, W, K;
    cin >> H >> W >> K;
    
    vector<pair<uint64_t, uint64_t>> goals(K);
    for (uint64_t i = 0; i < K; ++i) {
        uint64_t r, c;
        cin >> r >> c;
        goals[i] = {r - 1, c - 1};
    }
    
    vector<vector<uint64_t>> costs(H, vector<uint64_t>(W, UINT64_MAX));
    
    for (uint64_t i = 0; i < K; ++i) {
        auto [r, c] = goals[i];
        costs[r][c] = 0;
    }
    
    queue<tuple<uint64_t, uint64_t>> st;
    
    for (uint64_t i = 0; i < K; ++i) {
        auto [r, c] = goals[i];
        if (r + 1 < H && costs[r + 1][c] == UINT64_MAX) {
            st.push({r + 1, c});
        }
        if (r > 0 && costs[r - 1][c] == UINT64_MAX) {
            st.push({r - 1, c});
        }
        if (c + 1 < W && costs[r][c + 1] == UINT64_MAX) {
            st.push({r, c + 1});
        }
        if (c > 0 && costs[r][c - 1] == UINT64_MAX) {
            st.push({r, c - 1});
        }
    }
    
    while (!st.empty()) {
        // auto [r, c] = st.top();
        auto [r, c] = st.front();
        st.pop();
        array<uint64_t, 4> neighbors = {UINT64_MAX, UINT64_MAX, UINT64_MAX, UINT64_MAX};
        if (r + 1 < H) {
            neighbors[0] = costs[r + 1][c];
        }
        if (r > 0) {
            neighbors[1] = costs[r - 1][c];
        }
        if (c + 1 < W) {
            neighbors[2] = costs[r][c + 1];
        }
        if (c > 0) {
            neighbors[3] = costs[r][c - 1];
        }
        
        // 2番目に小さい値を探す
        uint64_t min_cost = UINT64_MAX;
        uint64_t second_min_cost = UINT64_MAX;
        for (const auto& cost : neighbors) {
            if (cost <= min_cost) {
                second_min_cost = min_cost;
                min_cost = cost;
            } else if (cost <= second_min_cost) {
                second_min_cost = cost;
            }
        }
        
        if (second_min_cost == UINT64_MAX) {
            continue; // すべての隣接セルが未到達の場合はスキップ
        }
        
        if (second_min_cost + 1 < costs[r][c]) {
            costs[r][c] = second_min_cost + 1;
            if (r + 1 < H && costs[r + 1][c] > second_min_cost + 2) {
                st.push({r + 1, c});
            }
            if (r > 0 && costs[r - 1][c] > second_min_cost + 2) {
                st.push({r - 1, c});
            }
            if (c + 1 < W && costs[r][c + 1] > second_min_cost + 2) {
                st.push({r, c + 1});
            }
            if (c > 0 && costs[r][c - 1] > second_min_cost + 2) {
                st.push({r, c - 1});
            }
        }
        
    }
    
    uint64_t result = 0;
    for (uint64_t i = 0; i < H; ++i) {
        for (uint64_t j = 0; j < W; ++j) {
            if (costs[i][j] != UINT64_MAX) {
                result += costs[i][j];
            }
        }
    }

    cout << result << endl;
    return 0;
}