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
    uint64_t N, M;
    cin >> N >> M;

    vector<uint64_t> A(N);
    for (size_t i = 0; i < N; ++i)
    {
        cin >> A[i];
    }

    sort(A.begin(), A.end());

    vector<uint64_t> com(N + 1);
    for (size_t i = 0; i < N; ++i)
    {
        com[i + 1] = com[i] + A[i];
    }

    if (com.back() <= M)
    {
        cout << "infinite" << endl;
        return 0;
    }

    uint64_t left = 0;
    uint64_t right = 1e9;
    while (right - left > 1)
    {
        uint64_t mid = (left + right) / 2;
        auto it = upper_bound(A.begin(), A.end(), mid);
        size_t index = distance(A.begin(), it);
        uint64_t sum = com[index] + mid * (N - index);
        if (sum > M)
        {
            right = mid;
        }
        else
        {
            left = mid;
        }
    }

    cout << left << endl;

    return 0;
}