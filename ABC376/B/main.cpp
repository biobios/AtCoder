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

    size_t left = 0;
    size_t right = 1;

    uint64_t result = 0;

    for (size_t i = 0; i < Q; ++i)
    {
        char H;
        cin >> H;
        uint64_t T;
        cin >> T;
        T--;

        if (H == 'L')
        {
            if (T < left)
            {
                if (T < right && right < left)
                {
                    result += N - left + T;
                }
                else
                {
                    result += left - T;
                }
            }
            else if (T > left)
            {
                if (left < right && right < T)
                {
                    result += left + N - T;
                    left = T;
                }
                else
                {
                    result += T - left;
                }
            }

            left = T;
        }
        else if (H == 'R')
        {
            if (T < right)
            {
                if (T < left && left < right)
                {
                    result += N - right + T;
                }
                else
                {
                    result += right - T;
                }
            }
            else if (T > right)
            {
                if (right < left && left < T)
                {
                    result += right + N - T;
                    right = T;
                }
                else
                {
                    result += T - right;
                }
            }

            right = T;
        }
    }

    cout << result << endl;

    return 0;
}