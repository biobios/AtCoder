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
    uint64_t N, C;

    cin >> N >> C;

    uint64_t prev_get;
    uint64_t result = 1;
    cin >> prev_get;

    for (size_t i = 1; i < N; i++)
    {
        uint64_t get_time;
        cin >> get_time;

        if (prev_get + C <= get_time)
        {
            result++;
            prev_get = get_time;
        }
    }

    cout << result << endl;

    return 0;
}