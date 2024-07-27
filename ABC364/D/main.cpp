#include <iostream>
#include <vector>
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
    vector<int64_t> A(N);
    for (size_t i = 0; i < N; i++)
    {
        cin >> A[i];
    }

    sort(A.begin(), A.end());

    for (size_t i = 0; i < Q; i++)
    {
        int64_t b;
        size_t k;
        cin >> b >> k;

        auto f = [&](int64_t x)
        {
            return upper_bound(A.begin(), A.end(), b + x) - lower_bound(A.begin(), A.end(), b - x) >= k;
        };

        int64_t right = 1e9;
        int64_t left = -1;
        while (right - left > 1)
        {
            int64_t mid = (right + left) / 2;
            if (f(mid))
                right = mid;
            else
                left = mid;
        }

        cout << right << endl;
    }

    return 0;
}