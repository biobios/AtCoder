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

    for (uint64_t i = 0; i < N; ++i)
    {
        cin >> A[i];
    }

    uint64_t ope_count = 0;

    sort(A.rbegin(), A.rend());

    while (A[1] > 0)
    {
        A[0]--;
        A[1]--;
        ope_count++;

        sort(A.rbegin(), A.rend());
    }

    cout << ope_count << endl;

    return 0;
}