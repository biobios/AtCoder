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
    string T;
    cin >> T;

    vector<string> S(N);
    for (size_t i = 0; i < N; i++)
    {
        cin >> S[i];
    }

    map<uint64_t, uint64_t> front_count;
    map<uint64_t, uint64_t> back_count;

    for (auto &&s : S)
    {
        {
            auto it = s.begin();
            auto end = s.end();
            uint64_t count = 0;
            for (auto &&t : T)
            {
                while (it != end && *it != t)
                {
                    ++it;
                }
                if (it == end)
                {
                    break;
                }
                ++it;
                ++count;
            }

            ++front_count[count];
        }

        {
            auto it = s.rbegin();
            auto end = s.rend();
            uint64_t count = 0;
            for (size_t i = T.size(); i > 0; --i)
            {
                auto &&t = T[i - 1];
                while (it != end && *it != t)
                {
                    ++it;
                }
                if (it == end)
                {
                    break;
                }
                ++it;
                ++count;
            }

            ++back_count[count];
        }
    }

    uint64_t result = 0;

    uint64_t current_sum = 0;
    auto it = back_count.rbegin();
    auto end = back_count.rend();

    for (auto &&[count, front] : front_count)
    {
        while (it != end && it->first + count >= T.size())
        {
            current_sum += it->second;
            ++it;
        }

        result += front * current_sum;
    }

    cout << result << endl;

    return 0;
}