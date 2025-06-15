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
    vector<uint64_t> A(N);
    for (uint64_t i = 0; i < N; ++i) {
        A[i] = i + 1;
    }
    
    size_t current_buffer_start = 0;
    for (uint64_t i = 0; i < Q; ++i) {
        uint64_t q_type;
        cin >> q_type;
        if (q_type == 1) {
            uint64_t p, x;
            cin >> p >> x;
            --p;

            A[(current_buffer_start + p) % N] = x;
        } else if (q_type == 2) {
            uint64_t p;
            cin >> p;
            --p;

            cout << A[(current_buffer_start + p) % N] << endl;
        } else if (q_type == 3) {
            uint64_t k;
            cin >> k;
            current_buffer_start = (current_buffer_start + k) % N;
        }
    }
    
    return 0;
}