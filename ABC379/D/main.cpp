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
    uint64_t Q;
    cin >> Q;

    vector<int64_t> plants;
    int64_t date = 0;

    size_t harvested_index = 0;

    for (uint64_t i = 0; i < Q; ++i)
    {
        uint64_t t;
        cin >> t;

        if (t == 1)
        {
            plants.push_back(date);
        }
        else if (t == 2)
        {
            int64_t w;
            cin >> w;
            date += w;
        }
        else
        {
            int64_t h;
            cin >> h;

            auto harvested_range_end = upper_bound(plants.begin() + harvested_index, plants.end(), date - h);
            cout << (harvested_range_end - (plants.begin() + harvested_index)) << endl;
            harvested_index = harvested_range_end - plants.begin();
        }
    }

    return 0;
}