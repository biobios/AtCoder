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
    uint64_t N, X;
    cin >> N >> X;

    vector<tuple<uint64_t, uint64_t, uint64_t, uint64_t>> machines(N);

    for (size_t i = 0; i < N; ++i)
    {
        uint64_t A, B, C, D;
        cin >> A >> B >> C >> D;

        machines[i] = make_tuple(A, B, C, D);
    }

    // 二分探索
    int64_t left = 0;
    int64_t right = 1e9 + 1;

    // 達成不可能な最小の処理能力を求める

    while (right - left > 1)
    {
        uint64_t middle = (left + right) / 2;

        bool possible = true;
        int64_t current = X;

        for (auto [A, B, C, D] : machines)
        {
            uint64_t min_cost = -1ull;

            for (size_t i = 0; i <= C; ++i)
            {
                int64_t needs = middle;
                uint64_t cost = i * B;

                needs -= i * A;
                if (needs > 0)
                    cost += (needs + C - 1) / C * D;

                min_cost = min(min_cost, cost);
            }

            for (size_t i = 0; i <= A; ++i)
            {
                int64_t needs = middle;
                uint64_t cost = i * D;

                needs -= i * C;
                if (needs > 0)
                    cost += (needs + A - 1) / A * B;

                min_cost = min(min_cost, cost);
            }

            current -= min_cost;

            if (current < 0)
            {
                possible = false;
                break;
            }
        }

        if (possible)
        {
            left = middle;
        }
        else
        {
            right = middle;
        }
    }

    cout << left << endl;

    return 0;
}