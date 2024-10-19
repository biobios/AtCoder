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
                if (T < left)
                {
                    if (T <= right && right < left)
                    {
                        if (new_costs.contains({T, (T + N - 1) % N}))
                            new_costs[{T, (T + N - 1) % N}] = min(new_costs[{T, (T + N - 1) % N}], left - T + right - T + 1 + c);
                        else
                            new_costs[{T, (T + N - 1) % N}] = left - T + right - T + 1 + c;

                        if (T == right)
                        {
                            if (new_costs.contains({T, (T + 1) % N}))
                                new_costs[{T, (T + 1) % N}] = min(new_costs[{T, (T + 1) % N}], N - left + T + 1 + c);
                            else
                                new_costs[{T, (T + 1) % N}] = N - left + T + 1 + c;
                        }
                        else
                        {
                            if (new_costs.contains({T, right}))
                                new_costs[{T, right}] = min(new_costs[{T, right}], N - left + T + c);
                            else
                                new_costs[{T, right}] = N - left + T + c;
                        }
                    }
                    else
                    {
                        if (new_costs.contains({T, right}))
                            new_costs[{T, right}] = min(new_costs[{T, right}], left - T + c);
                        else
                            new_costs[{T, right}] = left - T + c;

                        if (new_costs.contains({T, (T + 1) % N}))
                            new_costs[{T, (T + 1) % N}] = min(new_costs[{T, (T + 1) % N}], N - left + T + (N + T - right) % N + 1 + c);
                        else
                            new_costs[{T, (T + 1) % N}] = N - left + (N + T - right) % N + 1 + c;
                    }
                }
                else if (T > left)
                {
                    if (left < right && right <= T)
                    {
                        if (new_costs.contains({T, (T + 1) % N}))
                            new_costs[{T, (T + 1) % N}] = min(new_costs[{T, (T + 1) % N}], T - left + T - right + 1 + c);
                        else
                            new_costs[{T, (T + 1) % N}] = T - left + T - right + 1 + c;

                        if (T == right)
                        {
                            if (new_costs.contains({T, (N + T - 1) % N}))
                                new_costs[{T, (N + T - 1) % N}] = min(new_costs[{T, (N + T - 1) % N}], left + N - T + 1 + c);
                            else
                                new_costs[{T, (N + T - 1) % N}] = left + N - T + 1 + c;
                        }
                        else
                        {
                            if (new_costs.contains({T, right}))
                                new_costs[{T, right}] = min(new_costs[{T, right}], left + N - T + c);
                            else
                                new_costs[{T, right}] = left + N - T + c;
                        }
                    }
                    else
                    {
                        if (new_costs.contains({T, right}))
                            new_costs[{T, right}] = min(new_costs[{T, right}], T - left + c);
                        else
                            new_costs[{T, right}] = T - left + c;

                        if (new_costs.contains({T, (T + N - 1) % N}))
                            new_costs[{T, (T + N - 1) % N}] = min(new_costs[{T, (T + N - 1) % N}], left + N - T + (N + right - T) % N + 1 + c);
                        else
                            new_costs[{T, (T + N - 1) % N}] = left + N - T + (N + right - T) % N + 1 + c;
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
                            new_costs[{(T + 1) % N, T}] = N - right + (N + T - left) % N + 1 + c;
                    }
                }
                else if (T > right)
                {
                    if (right < left && left <= T)
                    {
                        if (new_costs.contains({(T + 1) % N, T}))
                            new_costs[{(T + 1) % N, T}] = min(new_costs[{(T + 1) % N, T}], T - right + T - left + 1 + c);
                        else
                            new_costs[{(T + 1) % N, T}] = T - right + T - left + 1 + c;

                        if (T == left)
                        {
                            if (new_costs.contains({(N + T - 1) % N, T}))
                                new_costs[{(N + T - 1) % N, T}] = min(new_costs[{(N + T - 1) % N, T}], right + N - T + 1 + c);
                            else
                                new_costs[{(N + T - 1) % N, T}] = right + N - T + 1 + c;
                        }
                        else
                        {
                            if (new_costs.contains({left, T}))
                                new_costs[{left, T}] = min(new_costs[{left, T}], right + N - T + c);
                            else
                                new_costs[{left, T}] = right + N - T + c;
                        }
                    }
                    else
                    {
                        if (new_costs.contains({left, T}))
                            new_costs[{left, T}] = min(new_costs[{left, T}], T - right + c);
                        else
                            new_costs[{left, T}] = T - right + c;

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