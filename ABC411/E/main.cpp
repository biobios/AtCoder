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

using namespace std;
using mint = atcoder::modint998244353;

int main()
{
    uint64_t N;
    cin >> N;
    
    vector<pair<uint64_t, uint8_t>> A;
    for (uint64_t i = 0; i < N; ++i) {
        vector<uint64_t> B(6);
        for (uint64_t j = 0; j < 6; ++j) {
            cin >> B[j];
        }
        sort(B.begin(), B.end());
        for (uint8_t j = 0; j < 6; ++j) {
            A.emplace_back(B[j], j);
        }
    }
    
    sort(A.begin(), A.end());
    
    mint P = 0;
    for (uint64_t i = 0; i < N * 6; ++i) {
        auto [A_j, j] = A[i];
        P += mint(A_j) * mint(i - j);
    }
    
    // Q = 6のN乗
    mint Q = mint(6).pow(N);
    
    // P / Q
    cout << (P / Q).val() << endl;
    return 0;
}