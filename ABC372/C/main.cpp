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

    string S;
    cin >> S;

    uint64_t ABC_count = 0;

    const string ABC = "ABC";

    for (size_t i = 0; i < N - 2; ++i)
    {
        if (S[i] == ABC[0] && S[i + 1] == ABC[1] && S[i + 2] == ABC[2])
        {
            ABC_count++;
        }
    }

    for (size_t i = 0; i < Q; ++i)
    {
        size_t exchange_index;
        char exchange_char;

        cin >> exchange_index >> exchange_char;
        exchange_index--;

        size_t check_start_index = exchange_index - 2;
        size_t check_end_index = exchange_index;

        if (exchange_index < 2)
            check_start_index = 0;
        if (exchange_index > N - 3)
            check_end_index = N - 3;

        bool is_ABC_before = false;
        for (size_t j = check_start_index; j <= check_end_index; ++j)
        {
            if (S[j] == ABC[0] && S[j + 1] == ABC[1] && S[j + 2] == ABC[2])
            {
                is_ABC_before = true;
                break;
            }
        }

        S[exchange_index] = exchange_char;

        bool is_ABC_after = false;
        for (size_t j = check_start_index; j <= check_end_index; ++j)
        {
            if (S[j] == ABC[0] && S[j + 1] == ABC[1] && S[j + 2] == ABC[2])
            {
                is_ABC_after = true;
                break;
            }
        }

        if (is_ABC_before && !is_ABC_after)
        {
            ABC_count--;
        }
        else if (!is_ABC_before && is_ABC_after)
        {
            ABC_count++;
        }

        cout << ABC_count << endl;
    }

    return 0;
}