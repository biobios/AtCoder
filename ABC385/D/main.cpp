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
    uint64_t N, M;
    cin >> N >> M;

    int64_t S_x, S_y;
    cin >> S_x >> S_y;

    vector<pair<int64_t, int64_t>> houses(N);
    for (uint64_t i = 0; i < N; i++)
    {
        cin >> houses[i].first >> houses[i].second;
    }

    map<int64_t, vector<pair<int64_t, uint64_t>>> horizontal_path;
    map<int64_t, vector<pair<int64_t, uint64_t>>> vertical_path;

    for (size_t i = 0; i < M; ++i)
    {
        char D;
        uint64_t C;
        cin >> D >> C;

        if (D == 'U')
        {
            vertical_path[S_x].push_back(make_pair(S_y, C));
            S_y += C;
        }
        else if (D == 'D')
        {
            vertical_path[S_x].push_back(make_pair(S_y - C, C));
            S_y -= C;
        }
        else if (D == 'L')
        {
            horizontal_path[S_y].push_back(make_pair(S_x - C, C));
            S_x -= C;
        }
        else if (D == 'R')
        {
            horizontal_path[S_y].push_back(make_pair(S_x, C));
            S_x += C;
        }
    }

    uint64_t count = 0;

    for (auto [x, y] : houses)
    {
        bool is_reached = false;

        for (auto [y1, c1] : vertical_path[x])
        {
            if (y1 <= y && y <= static_cast<int64_t>(y1 + c1))
            {
                is_reached = true;
                break;
            }
        }

        if (is_reached)
        {
            count++;
            continue;
        }

        for (auto [x1, c1] : horizontal_path[y])
        {
            if (x1 <= x && x <= static_cast<int64_t>(x1 + c1))
            {
                is_reached = true;
                break;
            }
        }

        if (is_reached)
        {
            count++;
        }
    }

    cout << S_x << " " << S_y << " " << count << endl;

    return 0;
}