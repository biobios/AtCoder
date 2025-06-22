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
    uint64_t N;
    cin >> N;

    uint64_t sum_A = 0;
    uint64_t sum_C = 0;
    uint64_t sum_D = 0;
    for (uint64_t i = 0; i < N; ++i) {
        uint64_t A, B, C;
        cin >> A >> B >> C;

        sum_A += min(A, B);
        sum_C += min(C, B);
        sum_D += min(B, A + C);
    }
    
    cout << min({sum_A, sum_C, sum_D / 2}) << endl;
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