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
    vector<pair<uint64_t, size_t>> A(N);

    for (size_t i = 0; i < N; ++i)
    {
        cin >> A[i].first;
        A[i].second = i;
    }

    sort(A.rbegin(), A.rend());

    cout << A[1].second + 1 << endl;

    return 0;
}