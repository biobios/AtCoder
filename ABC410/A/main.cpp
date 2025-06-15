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
    uint64_t N;
    cin >> N;
    vector<uint64_t> A(N);
    for (uint64_t i = 0; i < N; ++i) {
        cin >> A[i];
    }
    uint64_t K;
    cin >> K;

    uint64_t ans = 0;
    for (auto a : A) {
        if (a >= K)
            ++ans;
    }
    
    cout << ans << endl;

    return 0;
}