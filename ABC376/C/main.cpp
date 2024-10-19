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

    vector<uint64_t> A(N);
    vector<uint64_t> B(N - 1);

    for (size_t i = 0; i < N; i++)
    {
        cin >> A[i];
    }

    for (size_t i = 0; i < N - 1; i++)
    {
        cin >> B[i];
    }

    sort(A.rbegin(), A.rend());
    sort(B.rbegin(), B.rend());

    uint64_t too_big = 0;

    for (size_t i = 0; i < N - 1; i++)
    {
        if (too_big != 0)
        {
            if (A[i] > B[i - 1])
            {
                cout << "-1" << endl;
                return 0;
            }
        }
        else
        {
            if (A[i] > B[i])
            {
                too_big = A[i];
            }
        }
    }

    if (too_big != 0 && A[N - 1] > B[N - 2])
    {
        cout << "-1" << endl;
        return 0;
    }

    if (too_big == 0)
        too_big = A[N - 1];

    cout << too_big << endl;

    return 0;
}