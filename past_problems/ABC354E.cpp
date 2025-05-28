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

bool get_winner(const vector<pair<uint64_t, uint64_t>>& cards, set<size_t> rest_index, bool turn_player, map<size_t, bool>& memo)
{
    if (rest_index.empty()) {
        return !turn_player;
    }
    
    size_t memo_index = 0;
    for (auto& index : rest_index) {
        memo_index |= (1ULL << index);
    }

    if (memo.contains(memo_index)) {
        return memo[memo_index];
    }
    
    for (auto it1 = rest_index.begin(); it1 != rest_index.end(); ++it1) {
        size_t i = *it1;
        for (auto it2 = next(it1); it2 != rest_index.end(); ++it2) {
            size_t j = *it2;
            if (cards[i].first == cards[j].first || cards[i].second == cards[j].second) {
                set<size_t> next_rest_index = rest_index;
                next_rest_index.erase(i);
                next_rest_index.erase(j);

                if (turn_player == get_winner(cards, next_rest_index, !turn_player, memo)) {
                    memo[memo_index] = turn_player;
                    return turn_player;
                }
            }
        }
    }
    
    memo[memo_index] = !turn_player;
    return !turn_player;
}

int main()
{
    uint64_t N;
    cin >> N;
    vector<pair<uint64_t, uint64_t>> cards;
    for (uint64_t i = 0; i < N; ++i) {
        uint64_t a, b;
        cin >> a >> b;
        cards.emplace_back(a, b);
    }
    
    set<size_t> rest_index;
    for (size_t i = 0; i < N; ++i) {
        rest_index.insert(i);
    }
    
    map<size_t, bool> memo;
    bool winner = get_winner(cards, rest_index, true, memo);
    if (winner) {
        cout << "Takahashi" << endl;
    } else {
        cout << "Aoki" << endl;
    }
    return 0;
}