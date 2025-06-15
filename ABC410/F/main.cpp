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

void process()
{
    uint64_t H, W;
    cin >> H >> W;
    vector<string> S(H);
    for (uint64_t i = 0; i < H; ++i) {
        cin >> S[i];
    }

    vector<vector<uint64_t>> sum(H + 1, vector<uint64_t>(W + 1, 0));

    for (uint64_t i = 1; i <= H; ++i) {
        for (uint64_t j = 0; j < W; ++j) {
            sum[i][j + 1] = sum[i][j] + (S[i - 1][j] == '#');
        }
    }
    
    for (uint64_t j = 0; j <= W; ++j) {
        for (uint64_t i = 0; i < H; ++i) {
            sum[i + 1][j] += sum[i][j];
        }
    }
    
    uint64_t ans = 0;
    
    for (uint64_t w = 1; w <= W; ++w) {
        for (uint64_t h = 1; h <= H; ++h) {
            if ((w * h) % 2 != 0) {
                continue;
            }
            uint64_t half = (w * h) / 2;
            for (uint64_t i = 0; i + h <= H; ++i) {
                for (uint64_t j = 0; j + w <= W; ++j) {
                    if (sum[i + h][j + w] - sum[i + h][j] - sum[i][j + w] + sum[i][j] == half) {
                        ++ans;
                    }
                }
            }
        }
    }
    
    cout << ans << endl;
}

int main()
{
    uint64_t T;
    cin >> T;
    
    for (uint64_t i = 0; i < T; ++i) {
        process();
    }
    return 0;
}