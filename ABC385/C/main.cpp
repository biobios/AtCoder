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

    vector<uint64_t> H(N);

    for (uint64_t i = 0; i < N; i++)
    {
        cin >> H[i];
    }

    uint64_t count_max = 1;
    for (uint64_t i = 1; i < N; i++)
    {
        for (size_t j = 0; j < i; j++)
        {

            uint64_t current_streak = 1;
            uint64_t current_height = H[j];

            for (size_t k = j + i; k < N; k += i)
            {
                if (current_height == H[k])
                {
                    current_streak++;
                }
                else
                {
                    if (current_streak > count_max)
                    {
                        count_max = current_streak;
                    }
                    current_streak = 1;
                    current_height = H[k];
                }
            }

            if (current_streak > count_max)
            {
                count_max = current_streak;
            }
        }
    }

    cout << count_max << endl;

    return 0;
}