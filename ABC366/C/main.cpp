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

    map<uint64_t, size_t> value_count;
    uint64_t current_kind_count = 0;

    for (size_t i = 0; i < Q; i++)
    {
        uint64_t q_type;
        cin >> q_type;

        if (q_type == 1)
        {
            uint64_t x;
            cin >> x;
            value_count[x]++;
            if (value_count[x] == 1)
            {
                current_kind_count++;
            }
        }
        else if (q_type == 2)
        {
            uint64_t x;
            cin >> x;
            value_count[x]--;
            if (value_count[x] == 0)
            {
                current_kind_count--;
            }
        }
        else if (q_type == 3)
        {
            cout << current_kind_count << endl;
        }
    }

    return 0;
}