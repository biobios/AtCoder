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
    uint64_t Q;
    cin >> Q;
    
    queue<pair<uint64_t, uint64_t>> q;
    for (size_t i = 0; i < Q; ++i) {
        uint64_t q_type;
        cin >> q_type;
        if (q_type == 1) {
            uint64_t c, x;
            cin >> c >> x;
            q.push({c, x});
        }else if (q_type == 2) {
            uint64_t k;
            cin >> k;
            
            uint64_t sum = 0;
            
            while (k > 0) {
                auto& [c, x] = q.front();
                if (c <= k) {
                    sum += c * x;
                    k -= c;
                    q.pop();
                }else {
                    sum += k * x;
                    c -= k;
                    k = 0;
                }
            }
            
            cout << sum << endl;
        }
    }
    
    return 0;
}