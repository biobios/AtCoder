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

    vector<string> S(N);

    uint64_t max_size = 0;

    for (size_t i = 0; i < N; i++)
    {
        cin >> S[i];
        max_size = max(max_size, S[i].size());
    }

    uint64_t current_space_count = 0;

    for (size_t i = 0; i < max_size; i++)
    {
        current_space_count = 0;
        for (size_t j = N; j > 0; j--)
        {
            if (S[j - 1].size() > i)
            {
                for (size_t k = 0; k < current_space_count; k++)
                {
                    cout << "*";
                }
                current_space_count = 0;
                cout << S[j - 1][i];
            }
            else
            {
                current_space_count++;
            }
        }
        cout << endl;
    }

    return 0;
}