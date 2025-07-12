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

#include "atcoder/all"

using modint = atcoder::modint998244353;

using namespace std;

int main()
{
    uint64_t N;
    cin >> N;
    
    modint ans = 0;
    
    for (uint64_t b = 2; b < N; ++b) {
        for (uint64_t n = 1; n < N; ++n) {
            uint64_t num = n * b;
            uint64_t a_max = num + (num - 1);
            a_max = min(a_max, N);
            ans += (a_max - num);
        }
    }
    
    cout << ans.val() << endl;
    return 0;
}