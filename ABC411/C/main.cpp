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
    uint64_t N, Q;
    cin >> N >> Q;
    set<pair<int64_t, int64_t>> S;
    
    for (uint64_t i = 0; i < Q; ++i) {
        int64_t A;
        cin >> A;
        A--;
        if (S.empty()) {
            S.insert({A, A});
            cout << S.size() << endl;
            continue;
        }

        auto next = S.upper_bound({A, N});
        if (next == S.begin()) {
            if (next->first == A + 1) {
                pair<int64_t, int64_t> newPair = {A, next->second};
                S.erase(next);
                S.insert(newPair);
            }else {
                S.insert({A, A});
            }
            cout << S.size() << endl;
            continue;
        }
        
        auto prev_it = prev(next);
        pair<int64_t, int64_t> current_range = {A, A};
        if (prev_it->first <= A && A <= prev_it->second) {
            pair<int64_t, int64_t> newPair1 = {prev_it->first, A - 1};
            pair<int64_t, int64_t> newPair2 = {A + 1, prev_it->second};
            S.erase(prev_it);
            if (newPair1.first <= newPair1.second) {
                S.insert(newPair1);
            }
            
            if (newPair2.first <= newPair2.second) {
                S.insert(newPair2);
            }
            cout << S.size() << endl;
            continue;
        }
        
        if (prev_it->second == A - 1) {
            current_range.first = prev_it->first;
            S.erase(prev_it);
        }
        
        if (next != S.end() && next->first == A + 1) {
            current_range.second = next->second;
            S.erase(next);
        }
        
        S.insert(current_range);
        
        cout << S.size() << endl;
    }
}