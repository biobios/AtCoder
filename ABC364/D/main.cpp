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

        auto it = lower_bound(A.begin(), A.end(), b);
        size_t index = it - A.begin();
        auto L = it;
        auto R = it;

        uint64_t result = abs(b - *it);
        for (size_t i = 0; i < k - 1; i++)
        {
            if (L == A.begin() || (R + 1 != A.end() && (b - *(L - 1) > (*(R + 1) - b))))
            {
                R++;
                result = *R - b;
            }
            else if (R + 1 == A.end() || (L != A.begin() && (b - *(L - 1) <= (*(R + 1) - b))))
            {
                L--;
                result = b - *L;
            }
        }

        // size_t left;
        // size_t right;
        // if (index < k / 2)
        // {
        //     left = 0;
        //     right = k - 1;
        // }
        // else if (N - index < (k - k / 2))
        // {
        //     left = N - k;
        //     right = N - 1;
        // }
        // else
        // {
        //     left = index - k / 2;
        //     right = index + (k - k / 2) - 1;
        // }

        // auto L = A.begin() + left;
        // auto R = A.begin() + right;

        // // if (it == A.end())
        // // {
        // //     cout << b - A[N - k] << endl;
        // //     continue;
        // // }

        // // auto L = A.begin();
        // // auto R = A.begin() + k - 1;

        // // while (R != A.end() && *R < b)
        // // {
        // //     L++;
        // //     R++;
        // // }

        // uint64_t result = max(b - *L, *R - b);

        // while (*L <= b && *R >= b)
        // {
        //     if (b - *L < *R - b && L > A.begin())
        //     {
        //         L--;
        //         R--;
        //         uint64_t def = max(b - *L, *R - b);
        //         if (def >= result)
        //             break;
        //         result = def;
        //     }
        //     else if (b - *L > *R - b && R + 1 < A.end())
        //     {
        //         L++;
        //         R++;
        //         uint64_t def = max(b - *L, *R - b);
        //         if (def >= result)
        //             break;
        //         result = def;
        //     }
        //     else
        //     {
        //         uint64_t def = max(b - *L, *R - b);
        //         if (def < result)
        //             result = def;
        //         break;
        //     }
        // }

        cout << result << endl;
    }

    return 0;
}