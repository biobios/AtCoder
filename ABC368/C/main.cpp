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

    vector<int64_t> H(N);

    for (uint64_t i = 0; i < N; ++i)
    {
        cin >> H[i];
    }

    uint64_t T = 0;

    for (uint64_t i = 0; i < N; ++i)
    {
        auto h = H[i];

        T += 3 * (h / 5);
        h %= 5;

        while (h > 0)
        {
            T++;
            if (T % 3 == 0)
            {
                h -= 3;
            }
            else
            {
                --h;
            }
        }
    }

    cout << T << endl;

    return 0;
}