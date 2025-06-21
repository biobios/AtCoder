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
    
    vector<tuple<uint64_t, uint64_t, string>> queries(Q);
    for (uint64_t i = 0; i < Q; ++i) {
        uint64_t A, B;
        string C;
        cin >> A >> B;
        if (A == 2) {
            cin >> C;
        }
        queries[i] = make_tuple(A, B, C);
    }
    
    vector<string_view> result;
    uint64_t current_index = 0;
    size_t i;
    for (i = Q; i > 0; --i) {
        if (get<0>(queries[i - 1]) == 3) {
            current_index = get<1>(queries[i - 1]);
            break;
        }
    }

    if (current_index == 0) {
        cout << "" << endl;
        return 0;
    }
    
    for (i = i - 1; i > 0; --i) {
        size_t index = i - 1;
        const auto& [A, B, C] = queries[index];
        if (A == 1 && B == current_index) {
            for (; i > 0; --i) {
                if (get<0>(queries[i - 1]) == 3) {
                    current_index = get<1>(queries[i - 1]);
                    break;
                }
            }
            if (i == 0) {
                // 逆順に出力
                for (auto it = result.rbegin(); it != result.rend(); ++it) {
                    cout << *it;
                }
                cout << endl;
                return 0;
            }
        } else if (A == 2 && B == current_index) {
            result.push_back(get<2>(queries[index]));
        }
    }
    
    // 逆順に出力
    for (auto it = result.rbegin(); it != result.rend(); ++it) {
        cout << *it;
    }
    cout << endl;
    return 0;
}