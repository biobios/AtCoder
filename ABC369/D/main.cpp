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
    uint64_t N;
    cin >> N;

    uint64_t odd = 0;
    uint64_t even = 0;

    cin >> odd;

    for (size_t i = 1; i < N; ++i)
    {
        uint64_t A;
        cin >> A;

        auto next_odd = even + A;
        auto next_even = odd + A * 2;

        if (odd < next_odd)
        {
            odd = next_odd;
        }

        if (even < next_even)
        {
            even = next_even;
        }
    }

    cout << max(odd, even) << endl;

    return 0;
}