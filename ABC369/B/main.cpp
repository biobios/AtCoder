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
    int64_t left = 0;
    int64_t right = 0;

    uint64_t result = 0;

    for (size_t i = 0; i < N; ++i)
    {
        int64_t A;
        char c;
        cin >> A >> c;
        if (c == 'R')
        {
            if (right == 0)
            {
                right = A;
                continue;
            }

            result += abs(A - right);
            right = A;
        }
        else if (c == 'L')
        {
            if (left == 0)
            {
                left = A;
                continue;
            }

            result += abs(A - left);
            left = A;
        }
    }

    cout << result << endl;

    return 0;
}