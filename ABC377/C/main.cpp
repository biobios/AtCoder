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

constexpr int64_t MOVEMENT[][2] = {{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}, {0, 0}};

int main()
{
    uint64_t N, M;
    cin >> N >> M;

    set<pair<size_t, size_t>> S;

    for (size_t i = 0; i < M; ++i)
    {
        uint64_t a, b;
        cin >> a >> b;
        a--;
        b--;

        for (int64_t j = 0; j < 9; ++j)
        {
            int64_t x = a + MOVEMENT[j][0];
            int64_t y = b + MOVEMENT[j][1];

            if (x >= 0 && x < (int64_t)N && y >= 0 && y < (int64_t)N)
            {
                S.insert({x, y});
            }
        }
    }

    cout << (N * N - S.size()) << endl;

    return 0;
}