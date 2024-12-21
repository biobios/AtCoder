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

using namespace std;

int main()
{

    uint64_t H, W, X, Y;
    cin >> H >> W;
    cin >> X >> Y;

    vector<string> S(H);
    for (uint64_t i = 0; i < H; i++)
    {
        cin >> S[i];
    }

    string T;
    cin >> T;

    set<pair<uint64_t, uint64_t>> reached;
    reached.insert(make_pair(X - 1, Y - 1));

    uint64_t current_x, current_y;
    current_x = X - 1;
    current_y = Y - 1;

    for (uint64_t i = 0; i < T.size(); ++i)
    {
        auto t = T[i];
        if (t == 'U' && current_x > 0 && S[current_x - 1][current_y] != '#')
        {
            current_x--;
            reached.insert(make_pair(current_x, current_y));
        }
        else if (t == 'D' && current_x < H - 1 && S[current_x + 1][current_y] != '#')
        {
            current_x++;
            reached.insert(make_pair(current_x, current_y));
        }
        else if (t == 'L' && current_y > 0 && S[current_x][current_y - 1] != '#')
        {
            current_y--;
            reached.insert(make_pair(current_x, current_y));
        }
        else if (t == 'R' && current_y < W - 1 && S[current_x][current_y + 1] != '#')
        {
            current_y++;
            reached.insert(make_pair(current_x, current_y));
        }
    }

    uint64_t ans = 0;

    for (auto [x, y] : reached)
    {
        if (S[x][y] == '@')
        {
            ans++;
        }
    }

    cout << current_x + 1 << " " << current_y + 1 << " " << ans << endl;

    return 0;
}