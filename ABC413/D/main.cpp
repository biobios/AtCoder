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

    vector<int64_t> A(N);
    bool has_minus = false;
    bool has_plus = false;
    for (uint64_t i = 0; i < N; ++i) {
        cin >> A[i];
        if (A[i] < 0) {
            has_minus = true;
        } else {
            has_plus = true;
        }
    }
    
    if (N == 2) {
        cout << "Yes" << endl;
        return;
    }

    sort(A.begin(), A.end(), [](int64_t a, int64_t b) {
        return abs(a) < abs(b);
    });
    
    // 公比が1,-1のとき
    if (abs(A[0]) == abs(A[1])) {
        bool same_value = true;
        for (uint64_t i = 1; i < N; ++i) {
            if (abs(A[i]) != abs(A[0])) {
                same_value = false;
                break;
            }
        }
        
        if (!same_value) {
            cout << "No" << endl;
            return;
        }
        
        if (!has_minus || !has_plus) {
            cout << "Yes" << endl;
            return;
        }
        
        uint64_t plus_count = 0;
        for (uint64_t i = 0; i < N; ++i) {
            if (A[i] > 0) {
                plus_count++;
            }
        }
        if (N - plus_count == plus_count || N - plus_count == plus_count + 1 || N - plus_count == plus_count - 1) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
        return;
    }
    
    // 公比の絶対値が1より大きいとき
    int64_t first = A[0];
    int64_t second = A[1];
    
    for (uint64_t i = 2; i < N; ++i) {
        auto n = A[i-1];
        auto n_p_1 = A[i];
        if (n * second != n_p_1 * first) {
            cout << "No" << endl;
            return;
        }
    }
    
    cout << "Yes" << endl;
    return;
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