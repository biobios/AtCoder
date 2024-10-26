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

    vector<pair<uint64_t, uint64_t>> Ranges(N);

    for (size_t i = 0; i < N; ++i)
    {
        uint64_t l, r;
        cin >> l >> r;
        Ranges[i] = {l, r};
    }

    sort(Ranges.begin(), Ranges.end());

    set<pair<uint64_t, size_t>> d;
    set<size_t> to_delete;
    auto it = Ranges.begin();
    while (it != Ranges.end())
    {
        auto [l, r] = *it;
        auto more_it = lower_bound(d.begin(), d.end(), make_pair<uint64_t, size_t>((uint64_t)r, (size_t)0));
        auto copy_it = more_it;
        while (more_it != d.end())
        {
            to_delete.insert(more_it->second);
            more_it++;
        }
        d.erase(copy_it, d.end());
        d.insert({r, it - Ranges.begin()});
        it++;
    }

    auto r_it = to_delete.rbegin();
    while (r_it != to_delete.rend())
    {
        Ranges.erase(Ranges.begin() + *r_it);
        r_it++;
    }

    uint64_t count = 0;
    uint64_t prev_left = 0;

    for (size_t i = 1; i <= M; ++i)
    {
        auto it = lower_bound(Ranges.begin(), Ranges.end(), make_pair<uint64_t, uint64_t>((uint64_t)i, 0));
        if (it == Ranges.end())
            break;
        auto [l, r] = *it;
        count += (l - prev_left) * (M - r + 1);
        prev_left = l;
        i = l;
    }

    cout << (M * (M + 1) / 2 - count) << endl;

    return 0;
}