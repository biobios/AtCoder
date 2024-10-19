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

            /*
            size_t from, to, other;
            vector<pair<uint64_t, size_t>> moves;

            if (H == 'L')
            {
                from = left;
                to = T;
                other = right;
            }
            else
            {
                from = right;
                to = T;
                other = left;
            }

            if (to < from)
            {
                if (to <= other && other < from)
                {

                    moves.push_back({from - to + other - to + 1 + c, (N + to - 1) % N});

                    if (to == other)
                    {
                        moves.push_back({N - from + to + 1 + c, to + 1});
                    }
                    else
                    {
                        moves.push_back({N - from + to + c, other});
                    }
                }
                else
                {
                    moves.push_back({from - to + c, other});
                    moves.push_back({N - from + to + (N + to - other) % N + 1 + c, (to + 1) % N});
                }
            }
            else if (from < to)
            {
                if (from < other && other <= to)
                {
                    moves.push_back({to - from + to - other + 1 + c, (to + 1) % N});

                    if (to == other)
                    {
                        moves.push_back({N - to + from + 1 + c, to - 1});
                    }
                    else
                    {
                        moves.push_back({N - to + from + c, other});
                    }
                }
                else
                {
                    moves.push_back({to - from + c, other});
                    moves.push_back({N - to + from + (N + other - to) % N + 1 + c, (to + N - 1) % N});
                }
            }
            else
            {
                moves.push_back({c, other});
            }

            if (H == 'L')
            {
                for (auto [cost, other] : moves)
                {
                    if (new_costs.contains({T, other}))
                    {
                        new_costs[{T, other}] = min(new_costs[{T, other}], cost);
                    }
                    else
                    {
                        new_costs[{T, other}] = cost;
                    }
                }
            }
            else if (H == 'R')
            {
                for (auto [cost, other] : moves)
                {
                    if (new_costs.contains({other, T}))
                    {
                        new_costs[{other, T}] = min(new_costs[{other, T}], cost);
                    }
                    else
                    {
                        new_costs[{other, T}] = cost;
                    }
                }
            }
            */
            /*
            if (H == 'L')
            {
                if (T < left)
                {
                    if (T <= right && right < left)
                    {
                        // (6)
                        if (new_costs.contains({T, (T + N - 1) % N}))
                            new_costs[{T, (T + N - 1) % N}] = min(new_costs[{T, (T + N - 1) % N}], left - T + right - T + 1 + c);
                        else
                            new_costs[{T, (T + N - 1) % N}] = left - T + right - T + 1 + c;

                        if (T == right)
                        {
                            // (5)
                            if (new_costs.contains({T, (T + 1) % N}))
                                new_costs[{T, (T + 1) % N}] = min(new_costs[{T, (T + 1) % N}], N - left + T + 1 + c);
                            else
                                new_costs[{T, (T + 1) % N}] = N - left + T + 1 + c;
                        }
                        else
                        {
                            // (1)
                            if (new_costs.contains({T, right}))
                                new_costs[{T, right}] = min(new_costs[{T, right}], N - left + T + c);
                            else
                                new_costs[{T, right}] = N - left + T + c;
                        }
                    }
                    else
                    {
                        // (2)
                        if (new_costs.contains({T, right}))
                            new_costs[{T, right}] = min(new_costs[{T, right}], left - T + c);
                        else
                            new_costs[{T, right}] = left - T + c;

                        // (4)
                        if (new_costs.contains({T, (T + 1) % N}))
                            new_costs[{T, (T + 1) % N}] = min(new_costs[{T, (T + 1) % N}], N - left + T + (N + T - right) % N + 1 + c);
                        else
                            new_costs[{T, (T + 1) % N}] = N - left + (N + T - right) % N + 1 + c;// この行がおかしい
                    }
                }
                else if (T > left)
                {
                    if (left < right && right <= T)
                    {
                        // (4)
                        if (new_costs.contains({T, (T + 1) % N}))
                            new_costs[{T, (T + 1) % N}] = min(new_costs[{T, (T + 1) % N}], T - left + T - right + 1 + c);
                        else
                            new_costs[{T, (T + 1) % N}] = T - left + T - right + 1 + c;

                        if (T == right)
                        {
                            // (6)
                            if (new_costs.contains({T, (N + T - 1) % N}))
                                new_costs[{T, (N + T - 1) % N}] = min(new_costs[{T, (N + T - 1) % N}], left + N - T + 1 + c);
                            else
                                new_costs[{T, (N + T - 1) % N}] = left + N - T + 1 + c;
                        }
                        else
                        {
                            // (1)
                            if (new_costs.contains({T, right}))
                                new_costs[{T, right}] = min(new_costs[{T, right}], left + N - T + c);
                            else
                                new_costs[{T, right}] = left + N - T + c;
                        }
                    }
                    else
                    {
                        // (2)
                        if (new_costs.contains({T, right}))
                            new_costs[{T, right}] = min(new_costs[{T, right}], T - left + c);
                        else
                            new_costs[{T, right}] = T - left + c;

                        // (6)
                        if (new_costs.contains({T, (T + N - 1) % N}))
                            new_costs[{T, (T + N - 1) % N}] = min(new_costs[{T, (T + N - 1) % N}], left + N - T + (N + right - T) % N + 1 + c);
                        else
                            new_costs[{T, (T + N - 1) % N}] = left + N - T + (N + right - T) % N + 1 + c;
                    }
                }
                else
                {
                    // (2)
                    if (new_costs.contains({left, right}))
                        new_costs[{left, right}] = min(new_costs[{left, right}], c);
                    else
                        new_costs[{left, right}] = c;
                }
            }
            else if (H == 'R')
            {
                if (T < right)
                {
                    if (T <= left && left < right)
                    {
                        if (new_costs.contains({(T + N - 1) % N, T}))
                            new_costs[{(T + N - 1) % N, T}] = min(new_costs[{(T + N - 1) % N, T}], right - T + left - T + 1 + c);
                        else
                            new_costs[{(T + N - 1) % N, T}] = right - T + left - T + 1 + c;

                        if (T == left)
                        {
                            if (new_costs.contains({(T + 1) % N, T}))
                                new_costs[{(T + 1) % N, T}] = min(new_costs[{(T + 1) % N, T}], N - right + T + 1 + c);
                            else
                                new_costs[{(T + 1) % N, T}] = N - right + T + 1 + c;
                        }
                        else
                        {
                            if (new_costs.contains({left, T}))
                                new_costs[{left, T}] = min(new_costs[{left, T}], N - right + T + c);
                            else
                                new_costs[{left, T}] = N - right + T + c;
                        }
                    }
                    else
                    {
                        if (new_costs.contains({left, T}))
                            new_costs[{left, T}] = min(new_costs[{left, T}], right - T + c);
                        else
                            new_costs[{left, T}] = right - T + c;

                        if (new_costs.contains({(T + 1) % N, T}))
                            new_costs[{(T + 1) % N, T}] = min(new_costs[{(T + 1) % N, T}], N - right + T + (N + T - left) % N + 1 + c);
                        else
                            new_costs[{(T + 1) % N, T}] = N - right + (N + T - left) % N + 1 + c; // この行がおかしい
                    }
                }
                else if (T > right)
                {
                    if (right < left && left <= T)
                    {
                        // (4)
                        if (new_costs.contains({(T + 1) % N, T}))
                            new_costs[{(T + 1) % N, T}] = min(new_costs[{(T + 1) % N, T}], T - right + T - left + 1 + c);
                        else
                            new_costs[{(T + 1) % N, T}] = T - right + T - left + 1 + c;

                        if (T == left)
                        {
                            // (3)
                            if (new_costs.contains({(N + T - 1) % N, T}))
                                new_costs[{(N + T - 1) % N, T}] = min(new_costs[{(N + T - 1) % N, T}], right + N - T + 1 + c);
                            else
                                new_costs[{(N + T - 1) % N, T}] = right + N - T + 1 + c;
                        }
                        else
                        {
                            // (1)
                            if (new_costs.contains({left, T}))
                                new_costs[{left, T}] = min(new_costs[{left, T}], right + N - T + c);
                            else
                                new_costs[{left, T}] = right + N - T + c;
                        }
                    }
                    else
                    {
                        // (2)
                        if (new_costs.contains({left, T}))
                            new_costs[{left, T}] = min(new_costs[{left, T}], T - right + c);
                        else
                            new_costs[{left, T}] = T - right + c;

                        // (3)
                        if (new_costs.contains({(T + N - 1) % N, T}))
                            new_costs[{(T + N - 1) % N, T}] = min(new_costs[{(T + N - 1) % N, T}], right + N - T + (N + left - T) % N + 1 + c);
                        else
                            new_costs[{(T + N - 1) % N, T}] = right + N - T + (N + left - T) % N + 1 + c;
                    }
                }
                else
                {
                    if (new_costs.contains({left, right}))
                        new_costs[{left, right}] = min(new_costs[{left, right}], c);
                    else
                        new_costs[{left, right}] = c;
                }
            }
            */
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