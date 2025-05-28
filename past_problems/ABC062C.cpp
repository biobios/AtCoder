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
    uint64_t H, W;
    cin >> H >> W;
    
    uint64_t current_H = H;
    uint64_t current_W = W;

    uint64_t min_diff = -1ull;

    uint64_t piece_size[3];
    // 横に切る(切り捨て)
    current_H = H - (H / 3);
    piece_size[0] = (H / 3) * W;
    
    // 縦に切る
    piece_size[1] = (W / 2) * current_H;
    piece_size[2] = (W - (W / 2)) * current_H;
    
    uint64_t max_piece_size = max({piece_size[0], piece_size[1], piece_size[2]});
    uint64_t min_piece_size = min({piece_size[0], piece_size[1], piece_size[2]});
    if (max_piece_size - min_piece_size < min_diff) {
        min_diff = max_piece_size - min_piece_size;
    }
    // 横に切る
    piece_size[1] = (current_H / 2) * W;
    piece_size[2] = (current_H - (current_H / 2)) * W;
    max_piece_size = max({piece_size[0], piece_size[1], piece_size[2]});
    min_piece_size = min({piece_size[0], piece_size[1], piece_size[2]});
    if (max_piece_size - min_piece_size < min_diff) {
        min_diff = max_piece_size - min_piece_size;
    }

    // 横に切る(切り上げ)
    current_H = H - ((H + 2) / 3);
    piece_size[0] = ((H + 2) / 3) * W;

    // 縦に切る
    piece_size[1] = (W / 2) * current_H;
    piece_size[2] = (W - (W / 2)) * current_H;
    max_piece_size = max({piece_size[0], piece_size[1], piece_size[2]});
    min_piece_size = min({piece_size[0], piece_size[1], piece_size[2]});
    if (max_piece_size - min_piece_size < min_diff) {
        min_diff = max_piece_size - min_piece_size;
    }
    // 横に切る
    piece_size[1] = (current_H / 2) * W;
    piece_size[2] = (current_H - (current_H / 2)) * W;
    max_piece_size = max({piece_size[0], piece_size[1], piece_size[2]});
    min_piece_size = min({piece_size[0], piece_size[1], piece_size[2]});
    if (max_piece_size - min_piece_size < min_diff) {
        min_diff = max_piece_size - min_piece_size;
    }

    // 縦に切る(切り捨て)
    current_W = W - (W / 3);
    piece_size[0] = H * (W / 3);
    // 横に切る
    piece_size[1] = (H / 2) * current_W;
    piece_size[2] = (H - (H / 2)) * current_W;
    max_piece_size = max({piece_size[0], piece_size[1], piece_size[2]});
    min_piece_size = min({piece_size[0], piece_size[1], piece_size[2]});
    if (max_piece_size - min_piece_size < min_diff) {
        min_diff = max_piece_size - min_piece_size;
    }
    // 縦に切る
    piece_size[1] = (current_W / 2) * H;
    piece_size[2] = (current_W - (current_W / 2)) * H;
    max_piece_size = max({piece_size[0], piece_size[1], piece_size[2]});
    min_piece_size = min({piece_size[0], piece_size[1], piece_size[2]});
    if (max_piece_size - min_piece_size < min_diff) {
        min_diff = max_piece_size - min_piece_size;
    }
    // 縦に切る(切り上げ)
    current_W = W - ((W + 2) / 3);
    piece_size[0] = H * ((W + 2) / 3);
    // 横に切る
    piece_size[1] = (H / 2) * current_W;
    piece_size[2] = (H - (H / 2)) * current_W;
    max_piece_size = max({piece_size[0], piece_size[1], piece_size[2]});
    min_piece_size = min({piece_size[0], piece_size[1], piece_size[2]});
    if (max_piece_size - min_piece_size < min_diff) {
        min_diff = max_piece_size - min_piece_size;
    }
    // 縦に切る
    piece_size[1] = (current_W / 2) * H;
    piece_size[2] = (current_W - (current_W / 2)) * H;
    max_piece_size = max({piece_size[0], piece_size[1], piece_size[2]});
    min_piece_size = min({piece_size[0], piece_size[1], piece_size[2]});
    if (max_piece_size - min_piece_size < min_diff) {
        min_diff = max_piece_size - min_piece_size;
    }
    cout << min_diff << endl;
    return 0;
}