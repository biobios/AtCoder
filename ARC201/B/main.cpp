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

void solve()
{
    uint64_t N, W;
    cin >> N >> W;
    
    vector<pair<uint64_t, uint64_t>> items(N);
    for (uint64_t i = 0; i < N; ++i) {
        uint64_t w, v;
        cin >> w >> v;
        
        items[i] = make_pair(w, v);
    }
    
    auto compare_func = [](const auto& a, const auto& b) {
        if (get<0>(a) != get<0>(b)) {
            return get<0>(a) > get<0>(b);
        }
        
        return get<1>(a) < get<1>(b);
    };
    
    sort(items.begin(), items.end(), compare_func);
    
    uint64_t result = 0;
    
    for (uint64_t i = 0; i <= 64; ++i) {
        if (W % 2 != 0) {
            if (items.back().first == i) {
                result += items.back().second;
                items.pop_back();
            }
            W -= 1;
            if (W == 0) {
                break;
            }
        }
        
        vector<pair<uint64_t, uint64_t>> merged_items;
        while (!items.empty()) {
            if (items.back().first != i)
                break;
            
            auto item1 = items.back();
            items.pop_back();

            if (items.empty() || items.back().first != i) {
                item1.first += 1;
                merged_items.push_back(item1);
                break;
            }
            
            auto item2 = items.back();
            items.pop_back();
            
            merged_items.push_back(make_pair(item1.first + 1, item1.second + item2.second));
        }
        
        W /= 2;
        
        items.insert(items.end(), merged_items.begin(), merged_items.end());
        sort(items.begin(), items.end(), compare_func);
    }
    
    cout << result << endl;
}

int main()
{
    uint64_t T;
    cin >> T;

    for (uint64_t i = 0; i < T; ++i) {
        solve();
    }

    return 0;
}