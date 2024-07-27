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
    uint64_t N, X, Y;
    cin >> N >> X >> Y;
    vector<uint64_t> A(N);
    vector<uint64_t> B(N);
    for (size_t i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    for (size_t i = 0; i < N; i++)
    {
        cin >> B[i];
    }

    sort(A.rbegin(), A.rend());
    sort(B.rbegin(), B.rend());

    uint64_t sum_salty = 0;
    uint64_t sum_sweet = 0;

    for (size_t i = 0; i < N; i++)
    {
        sum_sweet += A[i];
        sum_salty += B[i];
        if (sum_sweet > X || sum_salty > Y)
        {
            cout << i + 1 << endl;
            return 0;
        }
    }

    cout << N << endl;

    return 0;
}