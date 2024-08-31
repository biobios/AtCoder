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

    vector<int64_t> A(N);

    for (size_t i = 0; i < N; ++i)
    {
        cin >> A[i];
    }

    if (N == 1)
    {
        cout << "1" << endl;
        return 0;
    }

    uint64_t result = 0;
    uint64_t l = 2;

    for (size_t i = 2; i < N; ++i)
    {
        if (A[i] - A[i - 1] == A[i - 1] - A[i - 2])
        {
            ++l;
        }
        else
        {
            result += l * (l + 1) / 2 - 1;
            l = 2;
        }
    }

    if (l > 0)
    {
        result += l * (l + 1) / 2;
    }

    cout << result << endl;

    return 0;
}