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
    uint64_t N;
    cin >> N;

    vector<uint64_t> A(N, 0);

    for (auto &a : A)
    {
        cin >> a;
        a--;
    }

    vector<uint64_t> B(N, 0);

    for (auto &b : B)
    {
        cin >> b;
    }

    vector<uint64_t> C(N);

    uint64_t result = 0;

    for (size_t i = 0; i < N; i++)
    {

        if (C[A[i]] == 0)
        {
            C[A[i]] = B[i];
            continue;
        }

        if (C[A[i]] > B[i])
        {
            result += B[i];
        }
        else
        {
            result += C[A[i]];
            C[A[i]] = B[i];
        }
    }

    cout << result << endl;

    return 0;
}