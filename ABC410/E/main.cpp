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
    uint64_t N, H, M;
    cin >> N >> H >> M;
    
    vector<uint64_t> A(H + 1);
    vector<uint64_t> B(M + 1);
    A[H] = M;
    B[M] = H;

    for (size_t i = 0; i < N; ++i) {
        uint64_t a, b;
        cin >> a >> b;

        bool won = false;
        vector<uint64_t> new_A(H + 1, 0);
        vector<uint64_t> new_B(M + 1, 0);
        for (uint64_t h = 0; h <= H; ++h) {
            if (A[h] >= b) {
                new_A[h] = max(new_A[h], A[h] - b);
                won = true;
            }
        }
        
        for (uint64_t m = 0; m <= M; ++m) {
            if (B[m] >= a) {
                new_B[m] = max(new_B[m], B[m] - a);
                won = true;
            }
        }
        
        for (uint64_t h = a; h <= H; ++h) {
            new_A[h - a] = max(new_A[h - a], A[h]);
        }
        
        for (uint64_t m = b; m <= M; ++m) {
            new_B[m - b] = max(new_B[m - b], B[m]);
        }
        A = new_A;
        B = new_B;
        if (!won) {
            cout << i << endl;
            return 0;
        }
    }
    
    cout << N << endl;

    return 0;
}