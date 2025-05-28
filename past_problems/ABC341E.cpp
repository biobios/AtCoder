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
    string S;
    cin >> S;
    set<size_t> continuous_set;

    for (size_t i = 1; i < N; ++i) {
        if (S[i] == S[i - 1]) {
            continuous_set.insert(i);
        }
    }
    
    for (size_t i = 0; i < Q; ++i) {
        uint64_t type, L, R;
        cin >> type >> L >> R;
        
        if (type == 1) {
            if (L > 1) {
                if (continuous_set.contains(L - 1)) {
                    continuous_set.erase(L - 1);
                }else{
                    continuous_set.insert(L - 1);
                }
            }
            
            if (R < N) {
                if (continuous_set.contains(R)) {
                    continuous_set.erase(R);
                }else{
                    continuous_set.insert(R);
                }
            }
        }else{
            auto it1 = continuous_set.lower_bound(L);
            auto it2 = continuous_set.lower_bound(R);
            if (it1 == it2) {
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
        }
    }
    
    return 0;

}