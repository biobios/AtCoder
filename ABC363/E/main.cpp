#include <iostream>
#include <vector>
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

    uint64_t H, W, Y;
    cin >> H >> W >> Y;

    vector<vector<uint64_t>> A(H, vector<uint64_t>(W));

    for (auto &a : A)
    {
        for (auto &aa : a)
        {
            cin >> aa;
            aa--;
        }
    }

    vector<vector<pair<uint64_t, uint64_t>>> Q(Y);

    for (size_t i = 0; i < H; i++)
    {
        uint64_t a = A[i][0];
        A[i][0] = -1ull;
        if (a < Y)
            Q[a].push_back({i, 0});

        a = A[i][W - 1];
        A[i][W - 1] = -1ull;
        if (a < Y)
            Q[a].push_back({i, W - 1});
    }

    for (size_t i = 0; i < W; i++)
    {
        uint64_t a = A[0][i];
        A[0][i] = -1ull;
        if (a < Y)
            Q[a].push_back({0, i});

        a = A[H - 1][i];
        A[H - 1][i] = -1ull;
        if (a < Y)
            Q[a].push_back({H - 1, i});
    }

    for (size_t i = 0; i < Y; i++)
    {
        for (size_t j = 0; j < Q[i].size(); j++)
        {
            auto [x, y] = Q[i][j];

            // 上下左右がi以下の場合はQiに追加
            // iより大きくYより小さい場合はQaに追加
            if (x > 0 && A[x - 1][y] < Y)
            {
                if (A[x - 1][y] <= i)
                    Q[i].push_back({x - 1, y});
                else
                    Q[A[x - 1][y]].push_back({x - 1, y});
                A[x - 1][y] = -1ull;
            }

            if (x < H - 1 && A[x + 1][y] < Y)
            {
                if (A[x + 1][y] <= i)
                    Q[i].push_back({x + 1, y});
                else
                    Q[A[x + 1][y]].push_back({x + 1, y});
                A[x + 1][y] = -1ull;
            }

            if (y > 0 && A[x][y - 1] < Y)
            {
                if (A[x][y - 1] <= i)
                    Q[i].push_back({x, y - 1});
                else
                    Q[A[x][y - 1]].push_back({x, y - 1});
                A[x][y - 1] = -1ull;
            }

            if (y < W - 1 && A[x][y + 1] < Y)
            {
                if (A[x][y + 1] <= i)
                    Q[i].push_back({x, y + 1});
                else
                    Q[A[x][y + 1]].push_back({x, y + 1});
                A[x][y + 1] = -1ull;
            }
        }
    }

    uint64_t result = H * W;
    for (size_t i = 0; i < Y; i++)
    {
        result -= Q[i].size();
        cout << result << endl;
    }

    return 0;
}