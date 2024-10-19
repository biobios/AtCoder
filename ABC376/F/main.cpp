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

vector<pair<uint64_t, size_t>> num_move(size_t n, size_t from, size_t to, size_t other)
{
    vector<pair<uint64_t, size_t>> result;
    if (to != other)
    {
        if (min(from, to) < other && other < max(from, to))
            result.push_back({n - abs((int64_t)to - (int64_t)from), other}); //(1)
        else
            result.push_back({abs((int64_t)to - (int64_t)from), other}); //(2)
    }

    if (from < other)
    {
        if (from < to && to <= other)
            result.push_back({n + from - to + other - to + 1, to - 1}); //(3)
        if (to < from || other <= to)
            result.push_back({(to - from + n) % n + (to - other + n) % n + 1, (to + 1) % n}); //(4)
    }
    else
    {
        if (other <= to && to < from)
            result.push_back({n + to - from + to - other + 1, to + 1}); //(5)
        if (to <= other || from < to)
            result.push_back({(from + n - to) % n + (other + n - to) % n + 1, (to + n - 1) % n}); //(6)
    }

    return result;
}

int main()
{
    uint64_t N, Q;
    cin >> N >> Q;

    map<pair<size_t, size_t>, uint64_t> costs;

    costs[{0, 1}] = 0;

    for (size_t i = 0; i < Q; ++i)
    {
        char H;
        cin >> H;
        uint64_t T;
        cin >> T;
        T--;

        map<pair<size_t, size_t>, uint64_t> new_costs;
        for (auto [p, c] : costs)
        {
            auto [left, right] = p;

            if (H == 'L')
            {
                for (auto [cost, other] : num_move(N, left, T, right))
                {
                    if (new_costs.contains({T, other}))
                        new_costs[{T, other}] = min(new_costs[{T, other}], cost + c);
                    else
                        new_costs[{T, other}] = cost + c;
                }
            }
            else if (H == 'R')
            {
                for (auto [cost, other] : num_move(N, right, T, left))
                {
                    if (new_costs.contains({other, T}))
                        new_costs[{other, T}] = min(new_costs[{other, T}], cost + c);
                    else
                        new_costs[{other, T}] = cost + c;
                }
            }
        }

        costs = new_costs;
    }

    uint64_t result = 1e18;

    for (auto [p, c] : costs)
    {
        result = min(result, c);
    }

    cout << result << endl;

    return 0;
}