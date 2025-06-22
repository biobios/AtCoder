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
    
    vector<pair<uint64_t, uint64_t>> A;
    uint64_t max_min = 0;
    for (uint64_t i = 0; i < N; ++i) {
        uint64_t min_val = UINT64_MAX;
        for (uint64_t j = 0; j < 6; ++j) {
            uint64_t B;
            cin >> B;
            A.emplace_back(B, i);
            if (B < min_val) {
                min_val = B;
            }
        }
        
        if (min_val > max_min) {
            max_min = min_val;
        }
    }
    
    sort(A.begin(), A.end());
    
    if (A.back().first == max_min) {
        cout << mint(max_min).val() << endl;
        return 0;
    }
    
    vector<uint8_t> B(N, 0);
    
    size_t i = 0;
    for (; i < A.size(); ++i) {
        auto [b, idx] = A[i];
        if (b > max_min) {
            break;
        }
        
        B[idx] += 1;
    }
    
    mint all_product = 1;
    for (uint64_t i = 0; i < N; ++i) {
        all_product *= B[i];
    }
    
    mint ExpectedValue = (A[i].first - max_min) * all_product;
    for (; i < A.size() - 1; ++i) {
        auto [b, idx] = A[i];
        all_product /= B[idx];
        B[idx] += 1;
        all_product *= B[idx];

        if (A[i + 1].first == b) {
            continue;
        }
        
        ExpectedValue += (A[i + 1].first - b) * all_product;
    }

    cout << (A.back().first - (ExpectedValue / mint(6).pow(N))).val() << endl;
    
    return 0;
}